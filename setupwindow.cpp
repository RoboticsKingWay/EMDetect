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

void SetupWindow::setPortList(QVector<QString>& list)
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
}

void SetupWindow::on_pushButton_clicked()
{
    QString port    = ui->comboBox->currentText();
    int borate  = ui->comboBox_2->currentText().toInt();
    int databit  = ui->comboBox_3->currentText().toInt();
    int stopbit = ui->comboBox_4->currentText().toDouble();

    SerialParam param;
    param.port = port;
    param.borate = borate;
    param.databit = databit;
    param.stopbit = stopbit;
    emit setSerialParam(param);
    this->hide();
}

