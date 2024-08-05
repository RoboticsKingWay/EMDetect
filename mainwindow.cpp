#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupwindow.h"
#include "UnitCalc.h"

#include <functional>

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
    if(ui->widget_upright)
    {
        source_view_ptr_ = new SourceView(ui->widget_upright);
        source_view_ptr_->createChartView();
    }
    if(ui->widget_real_chat_view)
    {
        chartview_ptr_ = new RealTimeChartView(ui->widget_real_chat_view);
        chartview_ptr_->createChartView();
        connect(chartview_ptr_,&RealTimeChartView::rect_Data,this,&MainWindow::on_getRectPoints);
        //        ui->widget_real_chat_view->installEventFilter(this);
    }
    if(setup_win_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::autoDirectFit ,this,&MainWindow::on_auto_FitDirect,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::manve_Fit ,this,&MainWindow::on_manve_Fit,Qt::AutoConnection);
    }

    if(setup_win_ptr_ && manager_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::setSerialParam,manager_ptr_,&SerialPortManager::getSerialParam,Qt::AutoConnection);
    }
    if(calibrate_view_ && chartview_ptr_)
    {
        std::function<void(QVector<QPointF>&)> getDetectRectData_Func = std::bind(&RealTimeChartView::getDetectRectData,chartview_ptr_,std::placeholders::_1);
        calibrate_view_->initView(/*getDetectRectData_Func*/);
//        connect(chartview_ptr_,&RealTimeChartView::rectData, calibrate_view_, &CalibrateView::on_GetRectData);
    }
    if(data_manager_ptr_)
    {
        connect(manager_ptr_,&SerialPortManager::SendData,data_manager_ptr_,&DataManager::DataHandle,Qt::QueuedConnection);
    }
    if(chartview_ptr_ && manager_ptr_)
    {
       connect(manager_ptr_,&SerialPortManager::clearRealTimeSerial,chartview_ptr_,&RealTimeChartView::resetSerials,Qt::QueuedConnection);
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
      //ui->comboBox->addItem(QString::number(sensitive));
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
    if(calibrate_view_)
    {
        delete calibrate_view_;
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

void MainWindow::runThread()
{
    if(is_calc_start_)
    {
        double scan_length  = ui->lineEdit_scan_length->text().toDouble();
        if(action_state_ == E_ACTION_REVIEW)
        {
            rect_data_list_.clear();
            for(int i = 0; i < list_draw_src_data_.size(); i++)
            {
                rect_data_list_.append(QPointF(list_draw_src_data_[i].index,list_draw_src_data_[i].mag_data.data[0]));
            }
            scan_length = scan_length_;
        }
        else
        {
//            chartview_ptr_->getDetectRectData(rect_data_list_);
//            on_getRectPoints();
        }
        if(rect_data_list_.size() < 4)
        {
            is_calc_start_ = false;
            setPushButtonEnable(E_ACTION_STOP);
            return;
        }
        qDebug()<<">>> start data handle <<<<"<<QDateTime::currentDateTime();
        //            QVector<QPointF> upline = chartview_ptr_->getThresholdUpline();
        //            QVector<QPointF> downline = chartview_ptr_->getThresholdDownline();
        //            if(upline.size() <= 0 || downline.size() <= 0)
        //            {
        //                break;
        //            }
        //            int up   = upline[0].y();
        //            int down = downline[0].y();

        std::pair<double,double> standar_param = calibrate_view_->getStandarParam();
        QString text_standar = QString("y = %1x + %2").arg(standar_param.first,0,'f',3).arg(standar_param.second,0,'f',3);
        ui->label_standar_function->setText(text_standar);

        QPointF max(0,0),min(0,0);
        calcMaxMinPoint(rect_data_list_, max, min);
        double y = max.y() - min.y();
        double a = standar_param.first;
        double b = standar_param.second;
        double x = (y - b) / a;
        double rect_points  = std::abs(max.x() - min.x());
        double total_points = list_draw_src_data_.size();
//        double scan_length  = ui->lineEdit_scan_length->text().toDouble();
        double detec_length = scan_length * rect_points / total_points;
        double db           = 10 * std::log10((max.y() - min.y()) / calibrate_view_->getAmplitude());
        ui->label_detection_x_scale->setText(QString::number(x));
        ui->label_detection_y->setText(QString::number(y));
        ui->label_detection_length->setText(QString::number(detec_length));
        ui->label_db_eq->setText(QString::number(db));

        //            std::vector<QPoint> chinnel_1_data;
        //            std::vector<QPoint> chinnel_2_data;
        //            for(int i = 0; i < list_draw_src_data_.size(); i++)
        //            {
        //                QPoint point;
        //                int dis_1 = list_draw_src_data_[i].mag_data.data[0] - up;
        //                int dis_2 = list_draw_src_data_[i].mag_data.data[0] - down;
        //                if(dis_1 > 0 || dis_2 < 0)
        //                {
        //                    point.setX(list_draw_src_data_[i].index);
        //                    point.setY(list_draw_src_data_[i].mag_data.data[0]);
        //                    chinnel_1_data.push_back(point);
        //                }
        //            }

        qDebug()<<">>>> new data handle finished.<<<<<"<<QDateTime::currentDateTime();

        is_calc_start_ = false;
        setPushButtonEnable(E_ACTION_STOP);
    }
}
// 后台线程计算结果
void MainWindow::drawImageViewThread()
{
    is_calc_thread_start_ = true;
    while(is_calc_thread_start_)
    {
        runThread();
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
        chartview_ptr_->updateChinnelView(draw_list);
        chartview_ptr_->setChinnelRange();
    }
    if(draw_list.size())
    {
        source_view_ptr_->updateChinnelView(draw_list);
        source_view_ptr_->setViewChinnelRange();
    }
    if(manager_ptr_ && serial_state != manager_ptr_->getHeartbeatState())
    {
        serial_state = manager_ptr_->getHeartbeatState();
        onSerialState(serial_state);
    }
//    qDebug()<<QDateTime::currentDateTime()<<"size:"<<draw_list.size();
}

void MainWindow::setPushButtonEnable(int state)
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
//    ui->pushButton_SerialSetup->setEnabled(true);x
    action_state_ = state;
    switch (action_state_)
    {
    case E_ACTION_ST: // 开始采集
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
//        ui->pushButton_SerialSetup->setEnabled(false);
        break;
    }
    case E_ACTION_STOP:  // 停止采集
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
//        ui->pushButton_SerialSetup->setEnabled(true);
        break;
    }
    case E_ACTION_DEAL_DATA:// 数据处理
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
//        ui->pushButton_SerialSetup->setEnabled(false);
    }
    case E_ACTION_REVIEW: // 预览数据
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
//        ui->pushButton_SerialSetup->setEnabled(false);
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
    case E_ACTION_DETECT_RECT:
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
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
        manager_ptr_->saveDataToExcelFile();
        manager_ptr_->setSerialPause(true);
        manager_ptr_->getSrcListData(list_draw_src_data_);
        ui->pushButton->setText("开始");
        setPushButtonEnable(E_ACTION_STOP);
    }
    else
    {
        // 开始采集
        list_draw_src_data_.clear();
        manager_ptr_->clearSrcListData();
        chartview_ptr_->resetSerials();
        source_view_ptr_->resetSerials();
        manager_ptr_->setSerialPause(false);
        ui->pushButton->setText("停止");
        setPushButtonEnable(E_ACTION_ST);
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
    if(ui->lineEdit->text() == ""||ui->lineEdit_scan_length->text() == "")
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
        qDebug()<<"save as label:"<<ui->lineEdit->text()<<" len:"<<ui->lineEdit_scan_length->text();
        if(data_manager_ptr_->saveDataToFile(sensitivity_ ,ui->lineEdit->text(),ui->lineEdit_scan_length->text().toDouble(), list_draw_src_data_))
        {
            QMessageBox::information(this,"info:","保存成功");
        }
        else
        {
           QMessageBox::information(this,"info:","保存失败");
        }
    }
}

void MainWindow::on_getRectPoints()
{
    int start = chartview_ptr_->getDetectRect().left();
    int end   = chartview_ptr_->getDetectRect().right();
    if(list_draw_src_data_.size() < 2)
    {
        return;
    }
    start = std::max(start,list_draw_src_data_[0].index);
    end   = std::min(end,list_draw_src_data_.size());
    if(end > start)
    {
        rect_data_list_.clear();
        for(int i = start; i < end; i++)
        {
            QPointF point;
            point.setX(list_draw_src_data_[i].index);
            point.setY(list_draw_src_data_[i].mag_data.data[0]);
            rect_data_list_.append(point);
        }
        calibrate_view_->on_GetRectData(rect_data_list_);
    }
}
// 数据处理
void MainWindow::on_pushButton_3_clicked()
{
//    sensitivity_ = QString(ui->comboBox->currentText()).toDouble();
    scan_length_ = QString(ui->lineEdit_scan_length->text()).toDouble();
    if(QString(ui->lineEdit_scan_length->text()) == "")
    {
        QMessageBox::warning(this, "Error", "扫查长度未设置!");
        return;
    }
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    on_getRectPoints();
    if(rect_data_list_.size() <= 4)
    {
        QMessageBox::warning(this, "warning", "请先选择一个特征区域");
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
            setPushButtonEnable(E_ACTION_DEAL_DATA);
            is_calc_start_ = true;
        }
    }

}

// 数据预览
void MainWindow::on_pushButton_4_clicked()
{
//    sensitivity_ = QString(ui->comboBox->currentText()).toDouble();
//    scan_length_ = QString(ui->lineEdit_scan_length->text()).toDouble();
//    if(QString(ui->lineEdit_scan_length->text()) == "" || QString(ui->comboBox->currentText()) == "")
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
        ui->lineEdit->setText(file_label);
        ui->lineEdit_scan_length->setText(QString::number(scan_length));
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
//            if(!thread_calc_ptr_)
//            {
//                thread_calc_ptr_ = std::make_shared<std::thread>(&MainWindow::drawImageViewThread,this);
//            }
//            if(thread_calc_ptr_)
//            {
                action_state_ = E_ACTION_REVIEW;
//                setPushButtonEnable();
//                is_calc_start_ = true;
//            }
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
            setPushButtonEnable(E_ACTION_DETECT_RECT);
        }
        else if(curr == QString("取消"))
        {
            chartview_ptr_->setSelectSwitch(false);
            ui->pushButton_5->setText("特征区域");
            setPushButtonEnable(E_ACTION_STOP);
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

//void MainWindow::on_pushButton_SerialSetup_clicked()
//{
//    if(manager_ptr_)
//    {
//        QVector<QString> list;
//        manager_ptr_->listPorts(list);
//        int conn_action = (manager_ptr_->isPortOpened()==true ? E_SERIAL_CLOSE:E_SERIAL_CONNECT);
//        setup_win_ptr_->setPortList(list,conn_action);
//        setup_win_ptr_->setCurrentIndex(0);
//        setup_win_ptr_->show();
//    }
//}

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
    if(chartview_ptr_)
    {
        if(arg1 > 0)
        {
            chartview_ptr_->setChinnelVisible(0, true);
        }
        else
        {
            chartview_ptr_->setChinnelVisible(0, false);
        }
    }
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    qDebug()<<"ch_2 arg1="<<arg1;
    if(chartview_ptr_)
    {
        if(arg1 > 0)
        {
            chartview_ptr_->setChinnelVisible(1,true);
        }
        else
        {
            chartview_ptr_->setChinnelVisible(1,false);
        }
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

void MainWindow::on_action_fit_circle_triggered()
{
    if(setup_win_ptr_)
    {
        setup_win_ptr_->setCurrentIndex(2);
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

    if(ui->lineEdit->text() == ""||ui->lineEdit_scan_length->text() == "")
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
        bool ret = data_manager_ptr_->saveDataToFile(sensitivity_, ui->lineEdit->text(),\
                                            ui->lineEdit_scan_length->text().toDouble(), list_draw_src_data_,fileName);
        if(ret)
        {
            QMessageBox::warning(this, "info", "文件另存成功!");
        }
        else
        {
            QMessageBox::warning(this, "info", "文件另存失败!");
        }
    }
}


void MainWindow::on_action_fileperview_triggered()
{
    on_pushButton_4_clicked();
}

void MainWindow::on_auto_FitDirect(double rad)
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(list_draw_src_data_.size() <= 0)
    {
        QMessageBox::warning(this, "warning", "请先采集若干拟合点!");
        return;
    }
    if(source_view_ptr_)
    {
        QPointF center;
        std::vector<QPointF> points;
        for(auto& item : list_draw_src_data_)
        {
            points.push_back(QPointF(item.mag_data.data[1],item.mag_data.data[0]));
        }
        center = calculatePointsCenter(points);
        qDebug()<<"fit center:"<<center <<" rad:"<<rad;
//        center = calculateCenter(points);
//        rad    = calculateRadius(center, points);
        source_view_ptr_->newCircle(center, rad);
    }
}

void MainWindow::on_manve_Fit(QPointF center, double rad)
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(source_view_ptr_)
    {
        source_view_ptr_->newCircle(center, rad);
    }
}


void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

}


void MainWindow::on_pushButton_filter_clicked()
{
    if(chartview_ptr_)
    {
//        chartview_ptr_.get
    }
}

