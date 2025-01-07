#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupwindow.h"
#include "UnitCalc.h"

#include <functional>

int static current_channel_id = 0; // 切换为两个图像显示，用于区分哪个实时图的特征区域被选中
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
        chartview_ptr_ = new RealTimeChartView(0,ui->widget_real_chat_view);
        chartview_ptr_->createChartView();
        connect(chartview_ptr_,&RealTimeChartView::rect_Data,this,&MainWindow::on_getRectPoints);
        //        ui->widget_real_chat_view->installEventFilter(this);
    }
    if(ui->widget_real_chat_view_2)
    {
        chartview_ptr_2_ = new RealTimeChartView(1,ui->widget_real_chat_view_2);
        chartview_ptr_2_->createChartView();
        connect(chartview_ptr_2_,&RealTimeChartView::rect_Data,this,&MainWindow::on_getRectPoints);
    }
    if(setup_win_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::autoDirectFit ,this,&MainWindow::on_auto_FitDirect,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::manve_Fit ,this,&MainWindow::on_manve_Fit,Qt::AutoConnection);
        connect(setup_win_ptr_,&SetupWindow::butterfly_filter ,this,&MainWindow::on_butterfly_Filter,Qt::AutoConnection);
    }

    if(setup_win_ptr_ && manager_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::setSerialParam,manager_ptr_,&SerialPortManager::getSerialParam,Qt::AutoConnection);
    }
    if(calibrate_view_ && chartview_ptr_)
    {
        std::function<void(QVector<QPointF>&)> getDetectRectData_Func = std::bind(&RealTimeChartView::getDetectRectData,chartview_ptr_,std::placeholders::_1);
        calibrate_view_->initView(/*getDetectRectData_Func*/);
        // 标定结果显示到主界面
        connect(calibrate_view_,&CalibrateView::update_inside_detection_list,this,&MainWindow::on_update_inside_detection_list,Qt::AutoConnection);
        connect(calibrate_view_,&CalibrateView::update_outside_detection_list,this,&MainWindow::on_update_outside_detection_list,Qt::AutoConnection);
        connect(calibrate_view_,&CalibrateView::update_function_result,this,&MainWindow::on_update_function_result,Qt::AutoConnection);
    }
    if(data_manager_ptr_)
    {
        connect(manager_ptr_,&SerialPortManager::SendData,data_manager_ptr_,&DataManager::DataHandle,Qt::QueuedConnection);
    }
    if(chartview_ptr_ && chartview_ptr_2_ && manager_ptr_)
    {
       connect(manager_ptr_,&SerialPortManager::clearRealTimeSerial,chartview_ptr_,&RealTimeChartView::resetSerials,Qt::QueuedConnection);
       connect(manager_ptr_,&SerialPortManager::clearRealTimeSerial,chartview_ptr_2_,&RealTimeChartView::resetSerials,Qt::QueuedConnection);
    }

    if(chartview_ptr_ && setup_win_ptr_)
    {//弃用功能
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
    // ui->checkBox_3->hide();
    // ui->checkBox_upline->hide();
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
        manager_ptr_ = nullptr;
    }
    if(data_manager_ptr_)
    {
        delete data_manager_ptr_;
        data_manager_ptr_ = nullptr;
    }
    if(chartview_ptr_)
    {
        delete chartview_ptr_;
        chartview_ptr_ = nullptr;
    }
    if(chartview_ptr_2_)
    {
        delete chartview_ptr_2_;
        chartview_ptr_2_ = nullptr;
    }
    if(source_view_ptr_)
    {
        delete source_view_ptr_;
        source_view_ptr_ = nullptr;
    }
    if(setup_win_ptr_)
    {
        delete setup_win_ptr_;
        setup_win_ptr_ = nullptr;
    }
    if(mag_widget_ptr_)
    {
        delete mag_widget_ptr_;
        mag_widget_ptr_ = nullptr;
    }
    if(calibrate_view_)
    {
        delete calibrate_view_;
        calibrate_view_ = nullptr;
    }
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(setup_win_ptr_)
    {
        setup_win_ptr_->close();
    }
    if(calibrate_view_)
    {
        calibrate_view_->close();
    }
    if(mag_widget_ptr_)
    {
        mag_widget_ptr_->close();
    }
    event->accept();

    // 如果你想要阻止窗口关闭，可以调用以下代码：
    // event->ignore();
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
        // 1、获取选中区域的扫描数据
        double scan_length  = ui->lineEdit_scan_length->text().toDouble();
        if(action_state_ == E_ACTION_REVIEW)
        {//预览数据时
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
        {//选中区域计算点太少
            is_calc_start_ = false;
            setPushButtonEnable(E_ACTION_STOP);
            return;
        }
        qDebug()<<">>> start data handle <<<<"<<QDateTime::currentDateTime();

        // 2、计算选择区域内极值---当前幅值
        QPointF max(0,0),min(0,0);
        calcMaxMinPoint(rect_data_list_, max, min);

        if(ui->comboBox->currentText() == "外部缺陷")
        {
            // 3、读取标定结果
            std::pair<double,double> standar_param = calibrate_view_->getStandarParam();
            // 外部缺陷
            double y = max.y() - min.y(); // 缺陷幅值
            y_max_am_ = y;
            double a = standar_param.first;
            double b = standar_param.second;
            double x = (y - b) / a; // 缺陷宽深比
            double rect_points  = rect_data_list_.size();//std::abs(max.x() - min.x()); // 选中数据点数
            double total_points = list_draw_src_data_.size(); // 所有扫描点数
            double detec_length = scan_length * rect_points / total_points; // 缺陷的宽度
            ui->label_detection_xy->setText(QString::number(x));
            ui->label_detection_fuzhi->setText(QString::number(y));
            ui->label_detection_length->setText(QString::number(detec_length));
        }
        else
        {
            // 内部缺陷
            QMap<QString,InsideDetectParam>& list = calibrate_view_->getInsideAmplitudeList();
            auto it = list.find(ui->comboBox_2->currentText());
            if(it != list.end())
            {
                double db = 10 * std::log10((max.y() - min.y()) / it->equivalent);
                ui->label_db_equal->setText(QString::number(db));
                ui->label_detection_fuzhi->setText(QString::number(y_max_am_));
            }
        }

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
    QVector<ChinnelData> draw_list  = manager_ptr_->getDrawData();
//    QVector<ChinnelData> draw_list;
    //if(src_list.size() > 0)
    {
        //SeekExtremeValue(src_list, draw_list);
    }
    if(chartview_ptr_ && draw_list.size() && action_state_ == E_ACTION_ST)
    {
        chartview_ptr_->updateChinnelView(draw_list);
        chartview_ptr_->setChinnelRange();
    }
    if(chartview_ptr_2_ && draw_list.size() && action_state_ == E_ACTION_ST)
    {
        chartview_ptr_2_->updateChinnelView(draw_list);
        chartview_ptr_2_->setChinnelRange();
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
//    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_detect_area2->setEnabled(true);
    action_state_ = state;
    switch (action_state_)
    {
    case E_ACTION_ST: // 开始采集
    {
//        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_detect_area2->setEnabled(false);
        break;
    }
    case E_ACTION_STOP:  // 停止采集
    {
//        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_detect_area2->setEnabled(true);
        break;
    }
    case E_ACTION_DEAL_DATA:// 数据处理
    {
        ui->pushButton->setEnabled(false);
//        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_detect_area2->setEnabled(false);
    }
    case E_ACTION_REVIEW: // 预览数据
    {
        ui->pushButton->setEnabled(false);
//        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_detect_area2->setEnabled(false);
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
    case E_ACTION_DETECT_RECT: //选择特征区域
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        if(current_channel_id == 0)
        {
            ui->pushButton_detect_area2->setEnabled(false);
        }
        else
        {
            ui->pushButton_5->setEnabled(false);
        }
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
        // 获取一次采集过程中的所有数据，如果数据量超过设置的阈值5000则需要从保存的文件中进行数据分析
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
        chartview_ptr_2_->resetSerials();
        source_view_ptr_->resetSerials();
        manager_ptr_->setSerialPause(false);
        ui->pushButton->setText("停止");
        setPushButtonEnable(E_ACTION_ST);
    }
}

// 数据默认保存在程序路径下 data文件夹，并以时间戳保存,另存数据
void MainWindow::on_pushButton_2_clicked()
{
    /*
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
    */
}

void MainWindow::on_getRectPoints(int channel_id)
{
    int start = 0, end = 0;
    if(channel_id == 0)
    {
        start = chartview_ptr_->getDetectRect().left();
        end   = chartview_ptr_->getDetectRect().right();
    }
    else
    {
        start = chartview_ptr_2_->getDetectRect().left();
        end   = chartview_ptr_2_->getDetectRect().right();
    }
    if(list_draw_src_data_.size() < 2)
    {
        return;
    }
    current_channel_id = channel_id;
    // 边界处理
    start = std::max(start,list_draw_src_data_[0].index);
    end   = std::min(end,list_draw_src_data_.size());
    if(end > start)
    {
        // 获取到当前特征区域的数据
        rect_data_list_.clear();
        for(int i = start; i < end; i++)
        {
            QPointF point;
            point.setX(list_draw_src_data_[i].index);
            point.setY(list_draw_src_data_[i].mag_data.data[channel_id]);
            rect_data_list_.append(point);
        }
        // 如果是标定获取特征区域，则通知标定捕获特征区域数据
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
    on_getRectPoints(current_channel_id);
    if(rect_data_list_.size() <= 4)
    {
        QMessageBox::warning(this, "warning", "请先选择一个特征区域");
        return;
    }
    if(list_draw_src_data_.size() > 0)
    {
        if(!thread_calc_ptr_)
        {//new thread
            thread_calc_ptr_ = std::make_shared<std::thread>(&MainWindow::drawImageViewThread,this);
        }
        else
        {// thread 存在则启动,进入数据处理状态
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
//        ui->lineEdit->setText(file_label);
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
            action_state_ = E_ACTION_REVIEW;
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
        current_channel_id = 0;
        chartview_ptr_2_->resetSelectRect();
        QString curr = ui->pushButton_5->text();
        if(curr == QString("特征区域1"))
        {
            chartview_ptr_->setSelectSwitch(true);
            ui->pushButton_5->setText("取消");
            setPushButtonEnable(E_ACTION_DETECT_RECT);
        }
        else if(curr == QString("取消"))
        {
            chartview_ptr_->setSelectSwitch(false);
            ui->pushButton_5->setText("特征区域1");
            setPushButtonEnable(E_ACTION_STOP);
        }
    }
}
void MainWindow::on_pushButton_detect_area2_clicked()
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(chartview_ptr_2_)
    {
        current_channel_id = 1;
        chartview_ptr_->resetSelectRect();
        QString curr = ui->pushButton_detect_area2->text();
        if(curr == QString("特征区域2"))
        {
            chartview_ptr_2_->setSelectSwitch(true);
            ui->pushButton_detect_area2->setText("取消");
            setPushButtonEnable(E_ACTION_DETECT_RECT);
        }
        else if(curr == QString("取消"))
        {
            chartview_ptr_2_->setSelectSwitch(false);
            ui->pushButton_detect_area2->setText("特征区域2");
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

        chartview_ptr_2_->updateChinnelView(draw_list);
        chartview_ptr_2_->setViewChinnelRange();

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
        chartview_ptr_2_->updateChinnelView(draw_list);
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
//文件另存为
void MainWindow::on_action_filesave_triggered()
{
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }

    if(/*ui->lineEdit->text() == ""||*/ui->lineEdit_scan_length->text() == "")
    {

        QMessageBox::warning(this, "warning", "请设置保存数据的扫查长度!");
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
        bool ret = data_manager_ptr_->saveDataToFile(sensitivity_, "save_file"/*ui->lineEdit->text()*/,\
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

void MainWindow::on_action_filter_triggered()
{
    if(setup_win_ptr_)
    {
        setup_win_ptr_->setCurrentIndex(3);
        setup_win_ptr_->showNormal();
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

void MainWindow::on_butterfly_Filter(int more,int less,int axes)
{
    if(source_view_ptr_)
    {
        source_view_ptr_->on_FilterView(more, less, axes);
    }
}


void MainWindow::on_update_inside_detection_list(QMap<QString,InsideDetectParam>& inside_list)
{
    ui->comboBox_2->clear();
    for(auto& it : inside_list)
        ui->comboBox_2->addItem(it.label);
}

void MainWindow::on_update_function_result(std::pair<double, double>& result_param)
{
    QString text = QString("y = %1x + %2").arg(result_param.first,0,'f',2).arg(result_param.second,0,'f',2);
    ui->label_standar_function->setText(text);
}

void MainWindow::on_update_outside_detection_list(QMap<QString,OutsideDetectParam>& out_list)
{

}

// 内部缺陷当量匹配
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    QMap<QString,InsideDetectParam>& list = calibrate_view_->getInsideAmplitudeList();
    auto it = list.find(ui->comboBox_2->currentText());
    if(it != list.end() && y_max_am_ > 1)
    {
        double db = 10 * std::log10(y_max_am_ / it->equivalent);
        ui->label_db_equal->setText(QString::number(db));
        ui->label_detection_fuzhi->setText(QString::number(y_max_am_));
    }
}

// 磁激励设置功能
void MainWindow::on_action_magstimulate_triggered()
{
#ifdef magstimulate_enable
    if(!mag_widget_ptr_)
    {
        mag_widget_ptr_ = new Widget();
    }
    mag_widget_ptr_->showNormal();
#endif
}
