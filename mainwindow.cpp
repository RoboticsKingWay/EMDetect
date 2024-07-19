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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 调用基类的 resizeEvent 函数，确保正确处理窗口大小变化事件
    QMainWindow::resizeEvent(event);

    // 获取窗口的新大小
    //QSize newSize = event->size();
    //    int top = ui->widget_down->geometry().top();
    //    int width = ui->widget_down->geometry().width();
//    ui->widget_tab_1->setGeometry(0, 0, ui->tab_1->width(), ui->tab_1->height());
//    ui->widget_tab_2->setGeometry(0, 0, ui->tab_2->width(), ui->tab_2->height());
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
//    if (watched == ui->label_image && event->type() == QEvent::Paint)
//    {
//        draw_Depth_Image();
//    }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter thePainter(this);
//    ui->widget_tab_1->setGeometry(0, 0, ui->tab_1->width(), ui->tab_1->height());
//    ui->widget_tab_2->setGeometry(0, 0, ui->tab_2->width(), ui->tab_2->height());
    event->accept();
}

void MainWindow::draw_Depth_Image()
{
//    int width  = ui->label_image->width();
//    int height = ui->label_image->height();
//    QImage image;
//    if(mutex_image_.tryLock(100))
//    {
//        image = bit_map_;
//        mutex_image_.unlock();
//    }
//    else
//    {
//        qDebug()<<"draw_Depth_Image lock fialed.";
//    }
//    ui->label_image->setPixmap(QPixmap::fromImage(image));
//    qDebug()<<"image w_h:"<<image.width()<<" "<<image.height();
//    QPainter painter(ui->label_image);
//    if(painter.isActive())
//    {
//       painter.drawImage(0, 0, image);
//    }
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
    // update time
    // 获取当前日期和时间
//    QDateTime currentDateTime = QDateTime::currentDateTime();

//    int year = currentDateTime.date().year();
//    int month = currentDateTime.date().month();
//    int day = currentDateTime.date().day();
//    // 获取时间的时、分、秒
//    int hour = currentDateTime.time().hour();
//    int minute = currentDateTime.time().minute();
//    int second = currentDateTime.time().second();
//    QString datetime = QString::asprintf("%04d.%02d.%02d %02d:%02d:%02d",
//                                         year, month, day, hour, minute, second);
//    ui->label_5->setText(datetime);
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
        if(chartview_ptr_)
        {
            chartview_ptr_->resetSerials();
            count_size_blk_ = 0;
            timer_draw_total_.start(SLEEP_TIMER_ON_DRAW);
        }
        if(source_view_ptr_)
        {
            source_view_ptr_->resetSerials();
        }
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
            action_state_ = E_ACTION_STOP;
            setPushButtonEnable();
        }
        QThread::msleep(100);
    }
    qDebug()<<"calc thread exit.";
}

// 设置绘图颜色列表
void MainWindow::getImageColor()
{
    double MY_IMG_BLUE[64]  =  { 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double MY_IMG_GREEN[64] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double MY_IMG_RED[64]   =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5 };
    yellowGradient_.clear();
    for(int i = 0; i < 64; i++)
    {
        yellowGradient_.append(QColor::fromRgb(MY_IMG_RED[i]*255, MY_IMG_GREEN[i]*255, MY_IMG_BLUE[i]*255, 255));//255固定不透明
    }
    for (const QColor &color : yellowGradient_)
    {
        qDebug() << "main_image_view: Yellow gradient color: RGB(" << color.red() << color.green() << color.blue() << ")";
    }
}

// 点云绘制
void MainWindow::drawImage(bool is_update)
{
//    width_ = ui->label_image->width();
//    height_ = ui->label_image->height();

    QImage bit_map = QImage(width_, height_, QImage::Format_ARGB32);
    bit_map.fill(Qt::white); // Fill the bitmap with blue color
    if(draw_image_data_.size() <= 0 || draw_image_data_[0].size() <= 0)
    {
        return;
    }
    if(is_update)
    {

        QPainter painter(&bit_map);
//            painter.begin(ui->label_image);
        picContour(painter,is_update);
        if(mutex_image_.tryLock(100))
        {
            bit_map_ = bit_map;
            mutex_image_.unlock();
//            ui->label_image->repaint();
//            ui->label_image->update();
//            painter.end();
            QImageWriter imageWriter("saved_src_image.png");
            imageWriter.setFormat("png");  // 设置图像格式
            // 写入图像
            bool success = imageWriter.write(bit_map);
            // 检查是否有错误
            if (!success)
            {
                qDebug() << "Failed to save image:" << imageWriter.errorString();
            }
            else
            {
                qDebug() << "Image saved successfully!";
            }
        }
        else
        {
            qDebug()<<"set draw image lock fialed.";
        }
    }
}

void MainWindow::picContour(QPainter& painter,bool is_update)
{
    double x0 = 0.025;
    double y0 = 0.025;
    double W = 0.95;
    double H = 0.90;
    float x = (float)(this->width_ * x0);
    float y = (float)(this->height_ * y0);
    float width = (float)(this->width_ * W);
    float height = (float)(this->height_ * H);
    //Contourf(g, 2 * 40, (original_num - 1) * 5, FreadData, (original_num - 1) * 5, 2 * 40);
    //Contourf(g, 2, original_num, FreadData, original_num, 2);

    Contourf(2 * 40, draw_image_data_[0].size(), draw_image_data_[0].size(), 2 * 40,painter);

    QPen pen = QColor(0,0,0);
    pen.setWidth(1);
    painter.setFont(QFont("Arial", 6));
    painter.setPen(pen);
    //        g.DrawRectangle(blackPen, x, y, width, height);
    float x1, x2, y1, y2;
    //画X方向刻度
    for (int k = 0; k <= 10; k++)
    {
        x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
        y1 = (float)(this->height_ * y0);
        x2 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
        y2 = (float)(this->height_ * (y0 + 0.02));
        painter.drawLine(x1, y1, x2, y2);


        x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
        y1 = (float)(this->height_ * (x0 + H));
        x2 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
        y2 = (float)(this->height_ * (x0 + H - 0.02));
        painter.drawLine(x1, y1, x2, y2);


        x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
        y1 = (float)(this->height_ * (y0 + H + 0.02)) - 3;
        painter.drawText(x1 + 1, y1+10, QString::number(k * scan_length_ / 10));
    }
    //画Y方向刻度
    int b;
    for (int k = 1; k <= 2; k++)
    {
        b = k;
        x1 = (float)(this->width_ * x0);
        y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        x2 = (float)(this->width_ * (x0 + 0.005));
        y2 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        painter.drawLine(x1, y1, x2, y2);

        x1 = (float)(this->width_ * (x0 + W));
        y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        x2 = (float)(this->width_ * (x0 + W - 0.005));
        y2 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        painter.drawLine(x1, y1, x2, y2);

        x1 = (float)(this->width_ * (x0 - 0.02)) - 7;
//        y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        y1 = (float)(this->height_ * (1 - (y0 + k * H / 3) - 0.05));
        //g.DrawString((k * widthOfPiece / 5).ToString("0"), font, brush, x1, y1);
        painter.drawText(x1+3, y1,QString("CH")+QString::number(k));
    }
}

void MainWindow::Contourf(long intM, long intN, double Xmax, double Ymax,QPainter& painter)
{
    //  Contourf(g, 2, original_num, FreadData, original_num, 2);

    int p;
    double picDX,picDY;
    double x0 = 0.025;
    double y0 = 0.025;
    double W = 0.95;
    double H = 0.90;
    double CurrentX = 0;
    double CurrentY = 0;
    double DDX = 0;
    double DDY = 0;

    //画彩图
    picDX = W / Xmax;
    picDY = H / Ymax;
    if(DDX < 1)
    {
        DDX = 2;
    }
    if(DDY < 1)
    {
        DDY = 2;
    }

    for (long i = 0; i < intM; i++)
    {
        for (long j = 0; j < intN; j++)
        {
            CurrentX = (double)(width_ * (x0 + j * picDX));
            // CurrentY = (float)(this->height_ * (1 - (y0 + 0.0625 + i * picDY)));
            CurrentY = (double)(height_ * (0.925 - i * picDY));
//            DDX = (double)(bit_map_.width() * picDX);
//            DDY = (double)(bit_map_.height() * picDY);

            p = (int)((draw_image_data_[i][j] - min_data_) * 63 / (max_data_ - min_data_));
            if (j > intN - 80)//彩图去右边图像。    //DynamicpicContour（）的代码是j>intN-50   intN是数据点数
            {
                p = 0;
            }
            if(p < 0 || p > 64)
            {
                p = 0;
            }

            QBrush brush = QBrush(yellowGradient_[p]);
            painter.fillRect(CurrentX, CurrentY, DDX, DDY,brush);
        }
    }
}

// 检测结果计算
void MainWindow::calcDetectData()
{
    CFunction calc_fun;
    double max = 0.,min = 0.;
    std::vector<std::vector<double>> src_data = std::vector<std::vector<double>>(CH_NUM,std::vector<double>(list_draw_src_data_.size(),0));
    std::vector<std::vector<double>> data = std::vector<std::vector<double>>(2,std::vector<double>(list_draw_src_data_.size(),0));
    std::vector<std::vector<double>> result = std::vector<std::vector<double>>(2 * 40,std::vector<double>((list_draw_src_data_.size() -1) * 5, 0));
    for(int i = 0; i < CH_NUM; i++)
    {

        for(int j = 0; j < list_draw_src_data_.size(); j++)
        {
            src_data[i][j] = list_draw_src_data_[j].mag_data.data[i];
        }
    }
    if(src_data.size() <= 0 || src_data[0].size() <= 0)
    {
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 2; j < src_data[0].size(); j++)
        {
            data[i][j] = (-3 * src_data[i][j - 2] + 12 * src_data[i][j - 1] + 17 * src_data[i][j] + 12 * src_data[i][j + 1] - 3 * src_data[i][j + 2]) / 35;
        }
    }
    calc_fun.Function(data, 2, data[0].size());
    calc_fun.defect(sensitivity_,result);
    calc_fun.calcMaxAndMin(result,min_data_,min_data_);
    draw_image_data_.clear();
    draw_image_data_ = result;
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
//            if(source_view_ptr_)
//            {
//                source_view_ptr_->resetSerials();
//            }
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
//            source_view_ptr_->darwChinnelView(list_draw_src_data_);
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file selected.");
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
//        source_view_ptr_->updateChinnelView(draw_list);
//        source_view_ptr_->setViewChinnelRange();
        qDebug()<<"draw file view finished."<<QDateTime::currentDateTime();
    }
    else
    {
        draw_list = list_draw_src_data_.mid(count_size_blk_*copy_size,copy_size);
//        chartview_ptr_->updateChinnelView(draw_list);
        source_view_ptr_->updateChinnelView(draw_list);
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

