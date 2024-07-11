#include "calibrateview.h"
#include "ui_calibrateview.h"

#include <QMessageBox>
CalibrateView::CalibrateView(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CalibrateView)
{
    ui->setupUi(this);
//    ui->lineEdit_outside_addnum->setInputMask("000000");
//    ui->lineEdit_width_set->setInputMask("000000");
//    ui->lineEdit_deep_set->setInputMask("000000");

//    ui->lineEdit_inside_add_num->setInputMask("000000");
//    ui->lineEdit_inside_write->setInputMask("000000");
    cfg_detection_list_.clear();
    ui->comboBox_inside_list->clear();
    ui->comboBox_inside_del->clear();
    ui->comboBox_outside_list->clear();
    ui->comboBox_outside_del->clear();
//    cfg_detection_list_ 读取配置参数
    for(int i = 0; i < 5; i++)
    {
        DetectDeclaerParam param;
        param.label = QString("缺陷%1").arg(i+1);
        param.depth = i+1;
        param.length = i*10+1;
        param.dete_type = EMDETECTION_TYPE::E_DETECTION_OUTER;
        cfg_detection_list_[param.label] = param;
        ui->comboBox_outside_list->addItem(param.label);
        ui->comboBox_outside_del->addItem(param.label);
    }
    for(int i = 0; i < 5; i++)
    {
        DetectDeclaerParam param;
        param.label = QString("缺陷%1").arg(i+6);
        param.equivalent = i+1;
        param.dete_type = EMDETECTION_TYPE::E_DETECTION_INNER;
        cfg_detection_list_[param.label] = param;
        ui->comboBox_inside_list->addItem(param.label);
        ui->comboBox_inside_del->addItem(param.label);
    }
}

CalibrateView::~CalibrateView()
{
    delete ui;
}

void CalibrateView::on_comboBox_outside_list_currentIndexChanged(int index)
{
    QString label = ui->comboBox_outside_list->currentText();
    auto it = cfg_detection_list_.find(label);
    if(it != cfg_detection_list_.end())
    {
        ui->lineEdit_deep_read->setText(QString::number(it->depth));
        ui->lineEdit_width_read->setText(QString::number(it->length));
    }
}

void CalibrateView::on_pushButton_outside_add_clicked()
{
    DetectDeclaerParam param;
    param.label   = ui->lineEdit_outside_addnum->text();
    if(!param.label.contains("缺陷"))
    {
        param.label   = QString("缺陷") + ui->lineEdit_outside_addnum->text();
    }
    param.depth   = ui->lineEdit_deep_set->text().toDouble();
    param.length  = ui->lineEdit_width_set->text().toDouble();
    param.dete_type = EMDETECTION_TYPE::E_DETECTION_OUTER;

    cfg_detection_list_[param.label] = param;
    ui->comboBox_outside_list->addItem(param.label);
    ui->comboBox_outside_del->addItem(param.label);
    QMessageBox::information(this,"info","添加成功");
}


void CalibrateView::on_pushButton_outside_del_clicked()
{
    QString label = ui->comboBox_outside_del->currentText();
    auto it = cfg_detection_list_.find(label);
    if(it != cfg_detection_list_.end())
    {
        cfg_detection_list_.erase(it);
        ui->comboBox_outside_del->removeItem(ui->comboBox_outside_del->currentIndex());
        ui->comboBox_outside_list->clear();
        for(auto& item : cfg_detection_list_)
        {
            if(item.dete_type == EMDETECTION_TYPE::E_DETECTION_OUTER && item.label != label)
            {
                ui->comboBox_outside_list->addItem(item.label);
            }
        }
        QMessageBox::information(this,"info","删除成功");
    }
}


void CalibrateView::on_comboBox_inside_list_currentIndexChanged(int index)
{
    QString label = ui->comboBox_inside_list->currentText();
    auto it = cfg_detection_list_.find(label);
    if(it != cfg_detection_list_.end())
    {
        ui->lineEdit_inside_read->setText(QString::number(it->equivalent));
    }
}


void CalibrateView::on_pushButton_inside_add_clicked()
{
    DetectDeclaerParam param;
    param.label   = ui->lineEdit_inside_add_num->text();
    if(!param.label.contains("缺陷"))
    {
        param.label   = QString("缺陷") + ui->lineEdit_inside_add_num->text();
    }
    param.equivalent = ui->lineEdit_inside_write->text().toDouble();
    param.dete_type  = EMDETECTION_TYPE::E_DETECTION_INNER;

    cfg_detection_list_[param.label] = param;
    ui->comboBox_inside_list->addItem(param.label);
    ui->comboBox_inside_del->addItem(param.label);
    QMessageBox::information(this,"info","添加成功");
}


void CalibrateView::on_pushButton_inside_del_clicked()
{
    QString label = ui->comboBox_inside_del->currentText();
    auto it = cfg_detection_list_.find(label);
    if(it != cfg_detection_list_.end())
    {
        cfg_detection_list_.erase(it);
        ui->comboBox_inside_del->removeItem(ui->comboBox_inside_del->currentIndex());
        ui->comboBox_inside_list->clear();
        for(auto& item : cfg_detection_list_)
        {
            if(item.dete_type == EMDETECTION_TYPE::E_DETECTION_INNER && item.label != label)
            {
                ui->comboBox_inside_list->addItem(item.label);
            }
        }
        QMessageBox::information(this,"info","删除成功");
    }
}

