#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupwindow.h"
#include "UnitCalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_.start(100); // 每秒更新一次
    connect(&timer_, &QTimer::timeout, this, &MainWindow::updateData);
    manager_ptr_ = new SerialPortManager(this);
    data_manager_ptr_ = new DataManager(this);
    if(manager_ptr_)
    {
        QVector<QString> list;
        manager_ptr_->listPorts(list);
        if(list.size())
        {
            manager_ptr_->connectSerial(list[0]);
        }
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
    }

    if(ui->widget_real_total_view)
    {
        source_view_ptr_ = new SourceView(ui->widget_real_total_view);
        source_view_ptr_->createChartView();
    }
    if(ui->widget_real_chinnel_view)
    {
//        gradient_view_ptr_ = new GradientView(ui->widget_real_chinnel_view);
//        gradient_view_ptr_->createChartView();
    }
    if(ui->widget_image_view)
    {
        //
        //image_view_ptr_ = new ImageView(ui->widget_image_view);
        //ui->widget_image_view->installEventFilter(this);
        //ui->widget_image_view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }
    if(image_view_ptr_ == nullptr)
    {
        image_view_ptr_ = new ImageView(ui->label_image);
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
    if(image_view_ptr_)
    {
        delete image_view_ptr_;
    }
    if(setup_win_ptr_)
    {
        delete setup_win_ptr_;
    }
    if(gradient_view_ptr_)
    {
        delete gradient_view_ptr_;
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
    // 调整组件大小以适应新的窗口大小
    //    ui->widget_up->setGeometry()
    //ui->tabWidget->setGeometry(0, 0, newSize.width()-20, newSize.height()-200);
    ui->widget_tab_1->setGeometry(0, 0, ui->tab_1->width(), ui->tab_1->height());
    ui->widget_tab_2->setGeometry(0, 0, ui->tab_2->width(), ui->tab_2->height());
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widget_image_view && event->type() == QEvent::Paint)
    {
        //draw_Depth_Image();
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
    if(image_view_ptr_)
    {
        image_view_ptr_->updateImage(ui->label_image->width(),ui->label_image->height());
    }
    event->accept();
}

int MainWindow::magnetic_Convert_Depth()
{
    return 0;
}

void MainWindow::draw_Depth_Image()
{
    int width  = ui->widget_image_view->width() - 10;
    int height = ui->widget_image_view->height() -10;

    QImage image(width, height, QImage::Format_ARGB32);
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            image.setPixel(x, y, qRgba(0, 0, 255, 128)); // 蓝色半透明
        }
    }

    QPainter painter(ui->widget_image_view);
    painter.drawImage(0, 0, image);

//    QPixmap pixmap(width,height);
//    QPainter painter(ui->widget_image_view);
//    QBrush brush(QColor(0, 0, 255,)); // 绿色
//    painter.setBrush(brush);//(Qt::blue);
//    QRect rect(5, 5, width, height);
//    painter.drawPixmap(rect,pixmap);

//    QImage test_image(width,height,QImage::Format_RGB32);
//    QImage* image_ptr = &test_image;//new QImage(width,height,QImage::Format_RGB32); //  &test_image;
//    QPainter painter(image_ptr);
//    painter.setBrush(Qt::blue);
//    painter.fillRect(0, 0, width, height, Qt::blue);
//    for(int w = 0; w < width; w++)
//    {

//    }


//    QRgb *scanLine = reinterpret_cast<QRgb *>(image_ptr->bits());
//    for (int y = 0; y < height; ++y)
//    {
//        for (int x = 0; x < width; ++x)
//        {
//            // 示例：根据像素位置计算灰度值
//            int pixelValue = (x + y) % 256;
//            scanLine[y * width + x] = qRgb(pixelValue, pixelValue, 255 - pixelValue);
//        }
//    }


    // 填充不同颜色的区域

//    painter.setBrush(Qt::blue);
//    painter.fillRect(100, 0, 100, 100, Qt::blue);

//    QPainter label_painter(ui->widget_image_view);
//    label_painter.drawImage(0,0,*image_ptr);
}

void MainWindow::updateData()
{
    static int count_points = 0;

    QVector<ChinnelData> draw_list = manager_ptr_->getDrawData();

    if(chartview_ptr_ && draw_list.size() && action_state_ == E_ACTION_ST)
    {
       //chartview_ptr_->updateView(draw_list);
        for(int i = 0; i < CH_NUM; i++)
        {
            chartview_ptr_->updateChinnelView(draw_list,i,is_chinnel_on_[i]);
        }
        chartview_ptr_->setChinnelRange();
        source_view_ptr_->updateChinnelView(draw_list);
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
    if(action_state_ == E_ACTION_ST)
    {
        action_state_ = E_ACTION_STOP;
        manager_ptr_->setSerialPause(true);
        ui->pushButton->setText("开始");
    }
    else
    {
        action_state_ = E_ACTION_ST;
        source_view_ptr_->resetSerials();
        manager_ptr_->setSerialPause(false);
        ui->pushButton->setText("停止");
    }
}

// 数据处理
void MainWindow::on_pushButton_3_clicked()
{
    list_draw_src_data_.clear();
    manager_ptr_->getSrcListData(list_draw_src_data_);
    if(list_draw_src_data_.size() && action_state_ == E_ACTION_STOP)
    {
        const double sensitivity = QString(ui->lineEdit_2->text()).toDouble();
        const double scan_length = QString(ui->lineEdit_2->text()).toDouble();
        if(QString(ui->lineEdit_2->text()) == "" || QString(ui->lineEdit_2->text()) == "")
        {
            QMessageBox::warning(this, "Error", "Scan length or sensitivity is empty!");
            return;
        }
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
    }
}

//数据预览
std::shared_ptr<std::thread> thread_ptr_ = nullptr;
void MainWindow::on_pushButton_4_clicked()
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
            source_view_ptr_->darwChinnelView(draw_list);

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

void MainWindow::onOpenExcelClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Excel File", "", "Excel Files (*.xlsx)");
    if (!filePath.isEmpty())
    {
        QVector<ChinnelData> draw_list;
        QXlsxExcelHelper::getInstance().readDataFromExcel(draw_list,filePath);
        source_view_ptr_->updateChinnelView(draw_list);
        source_view_ptr_->setChinnelRange();
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file selected.");
    }
}

void MainWindow::on_action_save_triggered()
{

}


void MainWindow::on_action_saveas_triggered()
{

}

void MainWindow::on_action_serial_triggered()
{
    if(setup_win_ptr_ == nullptr)
    {
        setup_win_ptr_  = new SetupWindow();
    }

    setup_win_ptr_->show();
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

