#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupwindow.h"
#include "UnitCalc.h"
#include "calc/CFunction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_.start(1000/DetectSettings::instance().real_time_rate()); // 每100m秒更新一次
    connect(&timer_, &QTimer::timeout, this, &MainWindow::updateData);
    connect(&timer_draw_total_, &QTimer::timeout, this, &MainWindow::drawFileView);
    manager_ptr_ = new SerialPortManager(this);
    data_manager_ptr_ = new DataManager(this);
    setup_win_ptr_  = new SetupWindow();
    calibrate_view_ = new CalibrateView();
    if(setup_win_ptr_ && manager_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::setSerialParam,manager_ptr_,&SerialPortManager::getSerialParam,Qt::AutoConnection);
    }
    if(data_manager_ptr_)
    {
        connect(manager_ptr_,&SerialPortManager::SendData,data_manager_ptr_,&DataManager::DataHandle,Qt::QueuedConnection);
    }

    if(ui->widget_real_chat_view)
    {
        chartview_ptr_ = new RealTimeChartView(ui->widget_real_chat_view);
        chartview_ptr_->createChartView();
//        ui->widget_real_chat_view->installEventFilter(this);
    }
    if(chartview_ptr_ && manager_ptr_)
    {
       connect(manager_ptr_,&SerialPortManager::clearRealTimeSerial,chartview_ptr_,&RealTimeChartView::resetSerials,Qt::QueuedConnection);
    }
    if(ui->widget_upright)
    {
        source_view_ptr_ = new SourceView(ui->widget_upright);
        source_view_ptr_->createChartView();
    }


    if(chartview_ptr_ && setup_win_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::uplinePlus, chartview_ptr_, &RealTimeChartView::on_uplinePlus,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::uplineDe, chartview_ptr_, &RealTimeChartView::on_uplineDe,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::uplineMoveto, chartview_ptr_, &RealTimeChartView::on_uplineMoveto,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::uplineReset, chartview_ptr_, &RealTimeChartView::on_uplineReset,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::downlinePlus, chartview_ptr_, &RealTimeChartView::on_downlinePlus,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::downlineDe, chartview_ptr_, &RealTimeChartView::on_downlineDe,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::downlineMoveto, chartview_ptr_, &RealTimeChartView::on_downlineMoveto,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::downlineReset, chartview_ptr_, &RealTimeChartView::on_downlineReset,Qt::AutoConnection);
    }

    for(auto& sensitive : DetectSettings::instance().sensitivity_list())
    {
      ui->comboBox->addItem(QString::number(sensitive));
    }
    list_draw_src_data_.clear();
}

MainWindow::~MainWindow()
{
    if(thread_calc_ptr_ && thread_calc_ptr_->joinable())
    {
      is_calc_start_ = false;
      is_calc_thread_start_ = false;
      thread_calc_ptr_->join();
    }
    if(manager_ptr_)
    {
        delete manager_ptr_;
    }
    if(data_manager_ptr_)
    {
        delete data_manager_ptr_;
    }
    if(chartview_ptr_)
    {
        delete chartview_ptr_;
    }
    if(source_view_ptr_)
    {
        delete source_view_ptr_;
    }
    if(setup_win_ptr_)
    {
        delete setup_win_ptr_;
    }
    delete ui;
}
//bool MainWindow::eventFilter(QObject *watched, QEvent *event)
//{
//    if (watched == ui->widget_real_chat_view && event->type() == QEvent::Paint)
//    {
//        chartview_ptr_->chart_view_->update();
//    }
//    return QWidget::eventFilter(watched, event);
//}

// 后台线程计算结果
void MainWindow::drawImageViewThread()
{
    is_calc_thread_start_ = true;
    while(is_calc_thread_start_)
    {
        if(is_calc_start_)
        {
            qDebug()<<">>> start drawImageViewThread <<<<"<<QDateTime::currentDateTime();

            qDebug()<<">>>> new drawImageViewThread finished.<<<<<"<<QDateTime::currentDateTime();
            is_calc_start_ = false;
            //            std::unique_lock<std::mutex> lock(wait_mutex_);
            //            wait_event_.wait(lock,[]{return true;});
//            do
//            {
//                QThread::msleep(50);
//            }while(is_draw_file_runing_);
//            is_draw_file_runing_ = false;
            action_state_ = E_ACTION_STOP;
            setPushButtonEnable();
        }
        QThread::msleep(100);
    }
    qDebug()<<"calc thread exit.";
}

void MainWindow::updateData()
{
    static int serial_state = E_SERIAL_CLOSE;
    QVector<ChinnelData> draw_list = manager_ptr_->getDrawData();

    if(chartview_ptr_ && draw_list.size() && action_state_ == E_ACTION_ST)
    {
        for(int i = 0; i < CH_NUM; i++)
        {
            chartview_ptr_->updateChinnelView(draw_list,i,is_chinnel_on_[i]);
        }
        chartview_ptr_->setChinnelRange(draw_list.size());
    }
    if(source_view_ptr_ && draw_list.size())
    {
        source_view_ptr_->updateChinnelView(draw_list);
        source_view_ptr_->setViewChinnelRange();
    }
    if(manager_ptr_ && serial_state != manager_ptr_->getHeartbeatState())
    {
        serial_state = manager_ptr_->getHeartbeatState();
        onSerialState(serial_state);
    }
}

void MainWindow::setPushButtonEnable()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_SerialSetup->setEnabled(true);
    switch (action_state_)
    {
    case E_ACTION_ST: // 开始采集
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_SerialSetup->setEnabled(false);
        break;
    }
    case E_ACTION_STOP:  // 停止采集
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_SerialSetup->setEnabled(true);
        break;
    }
    case E_ACTION_DEAL_DATA:// 数据处理
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_SerialSetup->setEnabled(false);
    }
    case E_ACTION_REVIEW: // 预览数据
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_SerialSetup->setEnabled(false);
        break;
    }
    case E_ACTION_SAVEAS: // 数据保存
    {
        break;
    }
    case E_ACTION_CTRL_SERIAL: // 串口操作
    {
        break;
    }
    default:
        break;
    }
}
// 开始采集 和 结束采集
void MainWindow::on_pushButton_clicked()
{
    if(manager_ptr_)
    {
        if(!manager_ptr_->isPortOpened())
        {
            QMessageBox::warning(this, "Error", "串口未连接");
            return;
        }
    }
    if(action_state_ == E_ACTION_DEAL_DATA)
    {
        QMessageBox::warning(this, "Error", "process is on data handle!");
        return;
    }
    if(action_state_ == E_ACTION_ST)
    {
        // 停止采集数据
        action_state_ = E_ACTION_STOP;
        manager_ptr_->saveDataToExcelFile();
        manager_ptr_->setSerialPause(true);
        manager_ptr_->getSrcListData(list_draw_src_data_);
        ui->pushButton->setText("开始");
        setPushButtonEnable();
    }
    else
    {
        // 开始采集
        action_state_ = E_ACTION_ST;
        list_draw_src_data_.clear();
        manager_ptr_->clearSrcListData();
        chartview_ptr_->resetSerials();
        source_view_ptr_->resetSerials();
        manager_ptr_->setSerialPause(false);
        ui->pushButton->setText("停止");
        setPushButtonEnable();
    }
}

// 数据默认保存在程序路径下 data文件夹，并以时间戳保存,另存数据
void MainWindow::on_pushButton_2_clicked()
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(ui->lineEdit->text() == ""||ui->lineEdit_2->text() == "")
    {

        QMessageBox::warning(this, "warning", "请设置保存标签或扫查长度!");
        return;
    }
    if(list_draw_src_data_.size() <= 0)
    {
        QMessageBox::information(this,"info:","没有可保存的数据");
        return;
    }
    if(data_manager_ptr_)
    {
        qDebug()<<"save as label:"<<ui->lineEdit->text()<<" len:"<<ui->lineEdit_2->text();
        if(data_manager_ptr_->saveDataToFile(ui->comboBox->currentText().toDouble(),ui->lineEdit->text(),ui->lineEdit_2->text().toDouble(), list_draw_src_data_))
        {
            QMessageBox::information(this,"info:","保存成功");
        }
        else
        {
           QMessageBox::information(this,"info:","保存失败");
        }
    }
}

// 数据处理
void MainWindow::on_pushButton_3_clicked()
{
    sensitivity_ = QString(ui->comboBox->currentText()).toDouble();
    scan_length_ = QString(ui->lineEdit_2->text()).toDouble();
    if(QString(ui->lineEdit_2->text()) == "" || QString(ui->comboBox->currentText()) == "")
    {
        QMessageBox::warning(this, "Error", "扫查长度和灵敏度未设置!");
        return;
    }
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(list_draw_src_data_.size() > 0)
    {
//        if(chartview_ptr_)
//        {
//            chartview_ptr_->resetSerials();
//            count_size_blk_ = 0;
//            timer_draw_total_.start(SLEEP_TIMER_ON_DRAW);
//        }
//        if(source_view_ptr_)
//        {
//            source_view_ptr_->resetSerials();
//        }
        if(!thread_calc_ptr_)
        {
            thread_calc_ptr_ = std::make_shared<std::thread>(&MainWindow::drawImageViewThread,this);
        }
        if(thread_calc_ptr_)
        {
            action_state_ = E_ACTION_DEAL_DATA;
            setPushButtonEnable();
            is_calc_start_ = true;
        }
    }

}

// 数据预览
void MainWindow::on_pushButton_4_clicked()
{
//    sensitivity_ = QString(ui->comboBox->currentText()).toDouble();
//    scan_length_ = QString(ui->lineEdit_2->text()).toDouble();
//    if(QString(ui->lineEdit_2->text()) == "" || QString(ui->comboBox->currentText()) == "")
//    {
//        QMessageBox::warning(this, "Error", "扫查长度或灵敏度未设置!");
//        return;
//    }
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    QString filePath = QFileDialog::getOpenFileName(this, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (!filePath.isEmpty())
    {
        qDebug()<<"execl "<< filePath <<" opened \n";
        qDebug()<<"start open"<<QDateTime::currentDateTime();
        list_draw_src_data_.clear();
        QString file_label = "";
        double sensitivity = 0.0;
        double scan_length = 0.0;
        QXlsxExcelHelper::getInstance().readDataFromExcel(sensitivity, file_label, scan_length,list_draw_src_data_,filePath);
        scan_length_ = scan_length;
        sensitivity_ = sensitivity;
//        ui->lineEdit->setText(file_label);
//        ui->lineEdit_2->setText(QString::number(scan_length));
        qDebug()<<"read file ok."<<QDateTime::currentDateTime();
        if(chartview_ptr_)
        {
            if(source_view_ptr_)
            {
                source_view_ptr_->resetSerials();
            }
            chartview_ptr_->resetSerials();
            count_size_blk_ = 0;
            timer_draw_total_.start(SLEEP_TIMER_ON_DRAW);
            if(!thread_calc_ptr_)
            {
                thread_calc_ptr_ = std::make_shared<std::thread>(&MainWindow::drawImageViewThread,this);
            }
            if(thread_calc_ptr_)
            {
                action_state_ = E_ACTION_REVIEW;
                setPushButtonEnable();
                is_calc_start_ = true;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file selected.");
    }
}
// 选择框
void MainWindow::on_pushButton_5_clicked()
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(chartview_ptr_)
    {
        QString curr = ui->pushButton_5->text();
        if(curr == QString("特征区域"))
        {
            chartview_ptr_->setSelectSwitch(true);
            ui->pushButton_5->setText("取消");
        }
        else if(curr == QString("取消"))
        {
            chartview_ptr_->setSelectSwitch(false);
            ui->pushButton_5->setText("特征区域");
        }
    }
}

void MainWindow::drawFileView()
{
    const int copy_size = 500;
    QVector<ChinnelData> draw_list;
    if((count_size_blk_+1)*copy_size > list_draw_src_data_.size())
    {
        draw_list = list_draw_src_data_.mid(count_size_blk_*copy_size);
        timer_draw_total_.stop();
        chartview_ptr_->updateChinnelView(draw_list);
        chartview_ptr_->setViewChinnelRange();
        //if(action_state_ == E_ACTION_REVIEW)
        {
            source_view_ptr_->updateButterflyView(draw_list);
            source_view_ptr_->setViewChinnelRange();
        }
        qDebug()<<"draw file view finished."<<QDateTime::currentDateTime();
    }
    else
    {
        draw_list = list_draw_src_data_.mid(count_size_blk_*copy_size,copy_size);
        chartview_ptr_->updateChinnelView(draw_list);
        //if(action_state_ == E_ACTION_REVIEW)
        {
            source_view_ptr_->updateButterflyView(draw_list);
            source_view_ptr_->setViewChinnelRange();
        }
    }
//    ui->widget_real_total_view->repaint();
    count_size_blk_++;
}

void MainWindow::on_pushButton_SerialSetup_clicked()
{
    if(manager_ptr_)
    {
        QVector<QString> list;
        manager_ptr_->listPorts(list);
        int conn_action = (manager_ptr_->isPortOpened()==true ? E_SERIAL_CLOSE:E_SERIAL_CONNECT);
        setup_win_ptr_->setPortList(list,conn_action);
        setup_win_ptr_->setCurrentIndex(0);
        setup_win_ptr_->show();
    }
}

void MainWindow::onSerialState(int state)
{
    if(state == E_SERIAL_CONNECT)
    {
        ui->pushButton_connect_state->setIcon(QIcon(":/source/serial_connect.png"));
    }
    else
    {
        ui->pushButton_connect_state->setIcon(QIcon(":/source/serial_close.png"));
    }
}

// 保存文件的标签值变化触发读标签
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(data_manager_ptr_)
    {
        qDebug()<<"save as label:"<<ui->lineEdit->text();
//        data_manager_ptr_->setLabel(ui->lineEdit->text());
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    qDebug()<<"ch_1 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[0] = true;
    }
    else
    {
        is_chinnel_on_[0] = false;
    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    qDebug()<<"ch_2 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[1] = true;
    }
    else
    {
        is_chinnel_on_[1] = false;
    }
}

void MainWindow::on_checkBox_upline_stateChanged(int arg1)
{
    if(chartview_ptr_)
    {
        if(arg1 > 0)
        {
            chartview_ptr_->setUpline(true);
        }
        else
        {
            chartview_ptr_->setUpline(false);
        }
    }
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(chartview_ptr_)
    {
        if(arg1 > 0)
        {
            chartview_ptr_->setDownline(true);
        }
        else
        {
            chartview_ptr_->setDownline(false);
        }
    }
}


void MainWindow::on_action_serialSetup_triggered()
{
    if(manager_ptr_)
    {
        QVector<QString> list;
        manager_ptr_->listPorts(list);
        int conn_action = (manager_ptr_->isPortOpened()==true ? E_SERIAL_CLOSE:E_SERIAL_CONNECT);
        setup_win_ptr_->setPortList(list,conn_action);
        setup_win_ptr_->setCurrentIndex(0);
        setup_win_ptr_->showNormal();
    }
}


void MainWindow::on_action_thresholdSetup_triggered()
{
    if(setup_win_ptr_)
    {
        setup_win_ptr_->setCurrentIndex(1);
        setup_win_ptr_->showNormal();
    }
}


void MainWindow::on_action_outside_triggered()
{
    if(calibrate_view_)
    {
        calibrate_view_->setCurrentIndex(0);
        calibrate_view_->showNormal();
    }
}


void MainWindow::on_action_inside_triggered()
{
    if(calibrate_view_)
    {
        calibrate_view_->setCurrentIndex(1);
        calibrate_view_->showNormal();
    }
}


void MainWindow::on_action_filesave_triggered()
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(ui->lineEdit->text() == ""||ui->lineEdit_2->text() == "")
    {

        QMessageBox::warning(this, "warning", "请设置保存标签或扫查长度!");
        return;
    }
    if(list_draw_src_data_.size() <= 0)
    {
        QMessageBox::information(this,"info:","没有可保存的数据");
        return;
    }
    // 创建文件对话框
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Save File", // 初始目录
        "detect_source.xlsx", // 默认文件名
        "Text Files (*.xlsx);;All Files (*)"); // 文件过滤器

    if (!fileName.isEmpty())
    {
        data_manager_ptr_->saveDataToFile(ui->comboBox->currentText().toDouble(),ui->lineEdit->text(),\
                                            ui->lineEdit_2->text().toDouble(), list_draw_src_data_,fileName);
    }
}

