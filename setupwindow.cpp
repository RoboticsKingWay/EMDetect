#include "setupwindow.h"
#include "ui_setupwindow.h"

SetupWindow::SetupWindow(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SetupWindow)
{
    ui->setupUi(this);
}

SetupWindow::~SetupWindow()
{
    delete ui;
}

//void SetupWindow::setupCurrentIndex(int index)
//{
//    switch (index)
//    {
//    case 0:
//        ui->tab_setup_serial->showNormal();
//        break;
//    case 1:
//        ui->tab_setup_threshold->showNormal();
//        break;
//    case 2:
//        ui->tab_setup_ip->showNormal();
//        break;
//    default:
//        break;
//    }
//    this->setCurrentIndex()
//    this->showNormal();
//}

void SetupWindow::setPortList(QVector<QString>& list,int action)
{
//    for(int i = 0; i < ui->comboBox->count(); i++)
//    {
//        ui->comboBox->removeItem(i);
//    }
    ui->comboBox->clear();
    for(int j = 0; j < list.size(); j++)
    {
        ui->comboBox->addItem(list[j]);
    }
    if(action == E_SERIAL_CONNECT)
    {
        ui->pushButton_sure->setText("连接");
    }
    else
    {
        ui->pushButton_sure->setText("关闭");
    }
}

void SetupWindow::on_pushButton_sure_clicked()
{
    QString port    = ui->comboBox->currentText();
    int borate  = ui->comboBox_2->currentText().toInt();
    int databit  = ui->comboBox_3->currentText().toInt();
    int stopbit = ui->comboBox_4->currentText().toDouble();
    QString action = ui->pushButton_sure->text();


    SerialParam param;
    param.port = port;
    param.borate = borate;
    param.databit = databit;
    param.stopbit = stopbit;
    if(action == QString("连接"))
    {
        param.action = E_SERIAL_CONNECT;
    }
    else
    {
        param.action = E_SERIAL_CLOSE;
    }
    emit setSerialParam(param);
    this->hide();
}

void SetupWindow::on_pushButton_cancel_clicked()
{
    this->hide();
}

void SetupWindow::on_pushButton_uplineplus_clicked()
{
    emit uplinePlus();
}

void SetupWindow::on_pushButton_uplinede_clicked()
{
    emit uplineDe();
}

void SetupWindow::on_pushButton_uplinesure_clicked()
{
    emit uplineMoveto(ui->lineEdit_uplineto->text().toDouble());
}

void SetupWindow::on_pushButton_uplinereset_clicked()
{
    emit uplineReset();
}


void SetupWindow::on_pushButton_downlineplus_clicked()
{
    emit downlinePlus();
}


void SetupWindow::on_pushButton_downlinede_clicked()
{
    emit downlineDe();
}


void SetupWindow::on_pushButton_downlinesure_clicked()
{
   emit downlineMoveto(ui->lineEdit_downlineto->text().toDouble());
}


void SetupWindow::on_pushButton_downlinereset_clicked()
{
    emit downlineReset();
}

