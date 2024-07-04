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
    timer_.start(100); // 每100m秒更新一次
    connect(&timer_, &QTimer::timeout, this, &MainWindow::updateData);
    connect(&timer_draw_total_, &QTimer::timeout, this, &MainWindow::drawFileView);
    manager_ptr_ = new SerialPortManager(this);
    data_manager_ptr_ = new DataManager(this);
    setup_win_ptr_  = new SetupWindow();
    if(setup_win_ptr_ && manager_ptr_)
    {
        connect(setup_win_ptr_,&SetupWindow::setSerialParam,manager_ptr_,&SerialPortManager::getSerialParam,Qt::AutoConnection);
    }
    if(data_manager_ptr_)
    {
        connect(manager_ptr_,&SerialPortManager::SendData,data_manager_ptr_,&DataManager::DataHandle,Qt::QueuedConnection);
    }
//    QWidget* page = ui->tabWidget->widget(0);
    if(ui->widget_real_chat_view)
    {
        chartview_ptr_ = new RealTimeChartView(ui->widget_real_chat_view);
        chartview_ptr_->createChartView();
        chartview_ptr_->setParentLayout(ui->widget_real_chat_view);
    }

    if(ui->widget_real_total_view)
    {
        source_view_ptr_ = new SourceView(ui->widget_real_total_view);
        source_view_ptr_->createChartView();
    }
    if(ui->widget_image_view && ui->label_image)
    {
        ui->label_image->resize(ui->widget_image_view->size());
//        ui->label_image->setPixmap(QPixmap::fromImage(image).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_image->setAlignment(Qt::AlignCenter);
        bit_map_ = QImage(ui->label_image->width(), ui->label_image->height(), QImage::Format_ARGB32);
        ui->label_image->setPixmap(QPixmap::fromImage(bit_map_).scaled(ui->widget_image_view->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        bit_map_.fill(Qt::blue);
        getImageColor();
        //image_view_ptr_ = new ImageView(ui->widget_image_view);
      ui->label_image->installEventFilter(this);
        //ui->widget_image_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
    if(image_view_new_ptr_ == nullptr)
    {
        //image_view_new_ptr_ = new ImageViewNew(ui->label_image);
    }
    list_draw_src_data_.clear();
}

MainWindow::~MainWindow()
{
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
    if(image_view_new_ptr_)
    {
        delete image_view_new_ptr_;
    }
    if(setup_win_ptr_)
    {
        delete setup_win_ptr_;
    }
//    if(gradient_view_ptr_)
//    {
//        delete gradient_view_ptr_;
//    }
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
    // 调整组件大小以适应新的窗口大小
    //    ui->widget_up->setGeometry()
    //ui->tabWidget->setGeometry(0, 0, newSize.width()-20, newSize.height()-200);
    ui->widget_tab_1->setGeometry(0, 0, ui->tab_1->width(), ui->tab_1->height());
    ui->widget_tab_2->setGeometry(0, 0, ui->tab_2->width(), ui->tab_2->height());
    ui->label_image->setGeometry(0, 0, ui->widget_image_view->width(), ui->widget_image_view->height());
    is_image_view_resize_ = true;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->label_image && event->type() == QEvent::Paint)
    {
        draw_Depth_Image();
    }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter thePainter(this);
    //draw_Depth_Image();
    //image_view_ptr_->draw_Depth_Image();
    ui->widget_tab_1->setGeometry(0, 0, ui->tab_1->width(), ui->tab_1->height());
    ui->widget_tab_2->setGeometry(0, 0, ui->tab_2->width(), ui->tab_2->height());
    if(image_view_new_ptr_ && is_image_view_resize_)
    {
//        image_view_ptr_->updateImage();
//        image_view_new_ptr_->updateImage(ui->label_image->width(),ui->label_image->height());
//        is_image_view_resize_ = false;
    }
    event->accept();
}

void MainWindow::draw_Depth_Image()
{
    int width  = ui->label_image->width();
    int height = ui->label_image->height();
    QImage image;
    if(mutex_image_.tryLock(100))
    {
        image = bit_map_;
        mutex_image_.unlock();
    }
//    image.scaledToHeight(height);
//    image.scaledToWidth(width);
    ui->label_image->setPixmap(QPixmap::fromImage(image).scaled(ui->label_image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    QImageWriter imageWriter("saved_XXX_image.png");
//    imageWriter.setFormat("png");  // 设置图像格式

//    // 写入图像
//    bool success = imageWriter.write(image);

//    // 检查是否有错误
//    if (!success) {
//        qDebug() << "Failed to save image:" << imageWriter.errorString();
//    } else {
//        qDebug() << "Image saved successfully!";
//    }
    QPainter painter(ui->label_image);
    if(painter.isActive())
    {
       painter.drawImage(0, 0, image);
    }

}

void MainWindow::updateData()
{
//    qDebug()<<QDateTime::currentDateTime();

    QVector<ChinnelData> draw_list = manager_ptr_->getDrawData();

    if(chartview_ptr_ && draw_list.size() && action_state_ == E_ACTION_ST)
    {
//        chartview_ptr_->setCurrentPointCount(draw_list[0].index);
        for(int i = 0; i < CH_NUM; i++)
        {
            chartview_ptr_->updateChinnelView(draw_list,i,is_chinnel_on_[i]);
        }
        chartview_ptr_->setChinnelRange();
    }
    // update time
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    int year = currentDateTime.date().year();
    int month = currentDateTime.date().month();
    int day = currentDateTime.date().day();
    // 获取时间的时、分、秒
    int hour = currentDateTime.time().hour();
    int minute = currentDateTime.time().minute();
    int second = currentDateTime.time().second();
    QString datetime = QString::asprintf("%04d.%02d.%02d %02d:%02d:%02d",
                                         year, month, day, hour, minute, second);
    ui->label_5->setText(datetime);
}

// 开始采集 和 结束采集
void MainWindow::on_pushButton_clicked()
{
    if(manager_ptr_)
    {
        if(!manager_ptr_->isPortOpened())
        {
            QMessageBox::warning(this, "Error", "serial port is not opened!");
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
        action_state_ = E_ACTION_STOP;
        manager_ptr_->setSerialPause(true);
        manager_ptr_->getSrcListData(list_draw_src_data_);
        ui->pushButton->setText("开始");
    }
    else
    {
        action_state_ = E_ACTION_ST;
        list_draw_src_data_.clear();
        manager_ptr_->clearSrcListData();
        chartview_ptr_->resetSerials();
//        source_view_ptr_->resetSerials();
        manager_ptr_->setSerialPause(false);
        ui->pushButton->setText("停止");
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
    if(ui->lineEdit->text() == "")
    {

        QMessageBox::warning(this, "warning", "请设置保存标签!");
        return;
    }
    if(list_draw_src_data_.size() <= 0)
    {
        QMessageBox::information(this,"info:","没有可保存的数据");
        return;
    }
    if(data_manager_ptr_)
    {
        qDebug()<<"save as label:"<<ui->lineEdit->text();
        if(data_manager_ptr_->saveDataToFile(ui->lineEdit->text(), list_draw_src_data_))
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
    sensitivity_ = QString(ui->lineEdit_3->text()).toDouble();
    scan_length_ = QString(ui->lineEdit_2->text()).toDouble();
    if(QString(ui->lineEdit_2->text()) == "" || QString(ui->lineEdit_3->text()) == "")
    {
        QMessageBox::warning(this, "Error", "Scan length or sensitivity is empty!");
        return;
    }
    if(action_state_ == E_ACTION_ST)
    {
        QMessageBox::warning(this, "warning", "请先停止采集操作!");
        return;
    }
    if(list_draw_src_data_.size() > 0)
    {
        if(source_view_ptr_)
        {
            qDebug()<<"new timer_draw_total_ start ";
            source_view_ptr_->resetSerials();
            count_size_blk_ = 0;
            timer_draw_total_.start(200);
            // source_view_ptr_->darwChinnelView(list_draw_src_data_);
        }
        qDebug()<<"new drawImageViewThread ";
        std::thread* calc_thread_ptr = new std::thread(&MainWindow::drawImageViewThread,this);
        calc_thread_ptr->detach();
    }

}

void MainWindow::drawImageViewThread()
{
    calcDetectData();
    drawImage(true);
    qDebug()<<"new drawImageViewThread finished.";
}

void MainWindow::getImageColor()
{
    double MY_IMG_BLUE[64]  =  { 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double MY_IMG_GREEN[64] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    double MY_IMG_RED[64]   =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5 };
    yellowGradient_.clear();
    for(int i = 0; i < 64; i++)
    {
        yellowGradient_.append(QColor(MY_IMG_BLUE[i]*255, MY_IMG_GREEN[i]*255, MY_IMG_RED[i]*255));
    }

    for (const QColor &color : yellowGradient_)
    {
        qDebug() << "main_image_view: Yellow gradient color: RGB(" << color.red() << color.green() << color.blue() << ")";
    }
}

void MainWindow::drawImage(bool is_update)
{
    width_ = ui->label_image->width();
    height_ = ui->label_image->height();

    QImage bit_map = QImage(width_, height_, QImage::Format_ARGB32);
    bit_map.fill(Qt::blue); // Fill the bitmap with blue color

    if(draw_image_data_.size() <= 0 || draw_image_data_[0].size() <= 0)
    {
        return;
    }
    if(is_update)
    {
        QPainter painter(&bit_map);
        picContour(painter,is_update);
        ui->label_image->update();
        if(mutex_image_.tryLock(100))
        {
            bit_map_ = bit_map;
            mutex_image_.unlock();
            QImageWriter imageWriter("saved_src_image.png");
            imageWriter.setFormat("png");  // 设置图像格式

            // 写入图像
            bool success = imageWriter.write(bit_map);

            // 检查是否有错误
            if (!success) {
                qDebug() << "Failed to save image:" << imageWriter.errorString();
            } else {
                qDebug() << "Image saved successfully!";
            }
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
        painter.drawText(x1, y1, QString::number(k * scan_length_ / 10));
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
        y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
        //g.DrawString((k * widthOfPiece / 5).ToString("0"), font, brush, x1, y1);
        painter.drawText(x1, y1,QString("CH")+QString::number(k));
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
        DDX = 1;
    }
    if(DDY < 1)
    {
        DDY = 1;
    }
    QBrush brush;
    for (long i = 0; i < intM; i++)
    {
        for (long j = 0; j < intN; j++)
        {
            CurrentX = (double)(bit_map_.width() * (x0 + j * picDX));
            // CurrentY = (float)(this->height_ * (1 - (y0 + 0.0625 + i * picDY)));
            CurrentY = (double)(bit_map_.height() * (0.925 - i * picDY));
//            DDX = (double)(bit_map_.width() * picDX);
//            DDY = (double)(bit_map_.height() * picDY);

            p = (int)((draw_image_data_[i][j] - min_data_) * 63 / (max_data_ - min_data_));
            if (j > intN - 80)//彩图去右边图像。    //DynamicpicContour（）的代码是j>intN-50   intN是数据点数
            {
                p = 0;
            }
            if(p < 0 || p > 64)
            {
//                qDebug()<<" color index out of range p = "<<p;
                p = 0;
            }

            brush.setColor(yellowGradient_[p]);
            painter.fillRect(CurrentX, CurrentY, DDX, DDY,brush);
        }
    }
}

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

void MainWindow::drawImageViewNew()
{
    calcDetectData();
    image_view_new_ptr_->setGradientToDistance(max_data_,min_data_);
    image_view_new_ptr_->setScanLength(scan_length_);
    image_view_new_ptr_->picContour(draw_image_data_,false);
    image_view_new_ptr_->showNormal();
}

void MainWindow::drawImageView()
{
    list_draw_src_data_.clear();
    manager_ptr_->getSrcListData(list_draw_src_data_);
    if(list_draw_src_data_.size() && action_state_ == E_ACTION_STOP)
    {

        const double sensitivity = QString(ui->lineEdit_3->text()).toDouble();
        const double scan_length = QString(ui->lineEdit_2->text()).toDouble();
        if(QString(ui->lineEdit_3->text()) == "" || QString(ui->lineEdit_2->text()) == "")
        {
            QMessageBox::warning(this, "Error", "Scan length or sensitivity is empty!");
            return;
        }
        action_state_ = E_ACTION_DEAL_DATA;
        std::vector<std::vector<int>> lists_src  = std::vector<std::vector<int>>(CH_NUM,std::vector<int>(list_draw_src_data_.size(),0));
        std::vector<std::vector<int>> lists_diff = std::vector<std::vector<int>>(CH_NUM,std::vector<int>(list_draw_src_data_.size(),0));;

        double array_avrage[CH_NUM];
        double array_standar[CH_NUM];
        ScanThreshold array_thresh[CH_NUM];

        for(int i = 0; i < CH_NUM; i++)
        {
            for(int j = 0; j < list_draw_src_data_.size(); j++)
            {
                lists_src[i][j] = list_draw_src_data_[j].mag_data.data[i];
            }
        }
        // 自差分处理
        for(int i = 0; i < CH_NUM; i++)
        {
            centralDifference(lists_src[i],lists_diff[i]);
        }
        // 求均值
        for(int i = 0; i < CH_NUM; i++)
        {
            array_avrage[i] = calAverage(lists_diff[i]);
        }
        // 求标准差
        for(int i = 0; i < CH_NUM; i++)
        {
            array_standar[i] = calculateStandardDeviation(lists_diff[i]);
        }
        // 求阈值线

        for(int i = 0; i < CH_NUM; i++)
        {
            array_thresh[i].ch_num = i+1;
            calcThreshold(array_avrage[i], array_standar[i], sensitivity, array_thresh[i].upline, array_thresh[i].downline);
            qDebug()<<"CH_"<<array_thresh[i].ch_num<<" :"<<array_thresh[i].upline<<" ~ "<<array_thresh[i].downline<<"\n";

            //            calcThreshold(array_avrage[3+i], array_standar[3+i], sensitivity, array_thresh[i].Q3, array_thresh[i].Q4);
            //            qDebug()<<"calcThreshold_"<<array_thresh[3+1].ch_num_2<<" :"<<array_thresh[i].Q3<<" ~ "<<array_thresh[i].Q4<<"\n";
        }
        //todo 判断差分数据在阈值线内

        // 求差分数据的极大极小值
        int max,min;
        calcMaxAndMin(lists_diff,max,min);
        image_view_ptr_->setGradientToDistance(max,min);
        image_view_ptr_->setScanLength(scan_length);
        image_view_ptr_->drawImage(lists_diff);
        image_view_ptr_->showNormal();
        action_state_ = E_ACTION_STOP;
    }
}

//数据预览
void MainWindow::onOpenExcelClicked()
{
    if(action_state_ == E_ACTION_STOP)
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Open Excel File", "", "Excel Files (*.xlsx)");
        if (!filePath.isEmpty())
        {
            qDebug()<<"execl "<< filePath <<" opened \n";
//            return;
//            thread_ptr_ = std::make_shared<std::thread>(std::thread([=,this](){
//            qDebug() << "Thread started";

            this->ui->pushButton->setEnabled(false);

            QVector<ChinnelData> draw_list;
            QXlsxExcelHelper::getInstance().readDataFromExcel(draw_list,filePath);
//            source_view_ptr_->darwChinnelView(draw_list);

            this->ui->pushButton->setEnabled(true);

//            qDebug() << "Thread finished";
//            }));
//            std::shared_ptr<QThread> thread = std::make_shared<QThread>(QThread());
//            this->moveToThread(thread);
//            QObject::connect(thread, &QThread::started, [=,this]() {
//                qDebug() << "Thread started";

//                this->ui->pushButton->setEnabled(false);

//                QVector<ChinnelData> draw_list;
//                QXlsxExcelHelper::getInstance().readDataFromExcel(draw_list,filePath);
//                source_view_ptr_->darwChinnelView(draw_list);

//                this->ui->pushButton->setEnabled(true);

//                qDebug() << "Thread finished";
//            });
//            thread->start();
//            QObject::connect(thread, &QThread::finished, [=,this]() {
//                qDebug() << "Thread finished signal received";
//            });
        }
        else
        {
            QMessageBox::warning(this, "Error", "No file selected.");
        }
    }
}

// 数据预览
void MainWindow::on_pushButton_4_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (!filePath.isEmpty())
    {
        qDebug()<<"execl "<< filePath <<" opened \n";
        qDebug()<<"start open"<<QDateTime::currentDateTime();
        list_draw_src_data_.clear();
        QXlsxExcelHelper::getInstance().readDataFromExcel(list_draw_src_data_,filePath);
        qDebug()<<"read file ok."<<QDateTime::currentDateTime();
        if(source_view_ptr_)
        {
            source_view_ptr_->resetSerials();
            count_size_blk_ = 0;
            timer_draw_total_.start(100);
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
        source_view_ptr_->updateChinnelView(draw_list);
        source_view_ptr_->setChinnelRange();
        qDebug()<<"draw file view finished."<<QDateTime::currentDateTime();
    }
    else
    {
        draw_list = list_draw_src_data_.mid(count_size_blk_*copy_size,copy_size);
        source_view_ptr_->updateChinnelView(draw_list);
    }
    ui->widget_real_total_view->repaint();
    count_size_blk_++;
}

void MainWindow::on_action_save_triggered()
{

}


void MainWindow::on_action_saveas_triggered()
{

}

void MainWindow::on_action_serial_triggered()
{
    if(manager_ptr_)
    {
        QVector<QString> list;
        manager_ptr_->listPorts(list);
        setup_win_ptr_->setPortList(list);
        setup_win_ptr_->show();

//        if(list.size())
//        {
//            manager_ptr_->connectSerial(list[0]);
//        }
    }
}

void MainWindow::on_action_setup_other_triggered()
{

}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    qDebug()<<"page index="<<index;


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

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    qDebug()<<"ch_3 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[2] = true;
    }
    else
    {
        is_chinnel_on_[2] = false;
    }
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    qDebug()<<"ch_4 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[3] = true;
    }
    else
    {
        is_chinnel_on_[3] = false;
    }
}


void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    qDebug()<<"ch_5 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[4] = true;
    }
    else
    {
        is_chinnel_on_[4] = false;
    }
}


void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    qDebug()<<"ch_6 arg1="<<arg1;
    if(arg1 > 0)
    {
        is_chinnel_on_[5] = true;
    }
    else
    {
        is_chinnel_on_[5] = false;
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(data_manager_ptr_)
    {
        qDebug()<<"save as label:"<<ui->lineEdit->text();
        data_manager_ptr_->setLabel(ui->lineEdit->text());
    }
}

