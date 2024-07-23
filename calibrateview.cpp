#include "calibrateview.h"
#include "ui_calibrateview.h"
#include "UnitCalc.h"
#include "DetectSettings.h"

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
        param.equivalent = i*2+1;
        param.dete_type = EMDETECTION_TYPE::E_DETECTION_OUTER;
        cfg_detection_list_[param.label] = param;
        ui->comboBox_outside_list->addItem(param.label);
        ui->comboBox_outside_del->addItem(param.label);
    }

    for(int i = 0; i < 5; i++)
    {
        DetectDeclaerParam param;
        param.label = QString("缺陷%1").arg(i+6);
        param.equivalent = i*2+1;
        param.dete_type = EMDETECTION_TYPE::E_DETECTION_INNER;
        cfg_detection_list_[param.label] = param;
        ui->comboBox_inside_list->addItem(param.label);
        ui->comboBox_inside_del->addItem(param.label);
    }
    result_param_.first   = DetectSettings::instance().fitted_param_a();
    result_param_.second  = DetectSettings::instance().fitted_param_b();
    QString text = QString("y = %1x + %2").arg(result_param_.first).arg(result_param_.second);
    ui->lineEdit_stand_result->setText(text);
    ui->lineEdit_stand_result_label->setText(DetectSettings::instance().detect_profile());
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
        ui->label_outside_depth_read->setText(QString::number(it->depth));
        ui->label_outside_width_read->setText(QString::number(it->length));
        ui->label_outside_db_read->setText(QString::number(it->equivalent));
    }
    else
    {
        ui->label_outside_depth_read->setText("");
        ui->label_outside_width_read->setText("");
        ui->label_outside_db_read->setText("");
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
    param.equivalent  = ui->lineEdit_outside_db_set->text().toDouble();
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
        ui->label_inside_db_read->setText(QString::number(it->equivalent));
    }
    else
        ui->label_inside_db_read->setText("");
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


void CalibrateView::on_pushButton_outside_stand_clicked()
{
    std::vector<std::pair<double, double>> points;
    for(auto& item : cfg_detection_list_)
    {
        if(item.dete_type == EMDETECTION_TYPE::E_DETECTION_OUTER)
        {
            std::pair<double, double> point;
            point.first   = item.depth/item.length;
            point.second  = item.equivalent;
            points.push_back(point);
        }
    }
    result_param_ = leastSquares(points);
    QString text = QString("y = %1x + %2").arg(result_param_.first,0,'f',3).arg(result_param_.second,0,'f',3);
    ui->lineEdit_stand_result->setText(text);
}

void CalibrateView::on_pushButton_inside_stand_clicked()
{

}

void CalibrateView::on_pushButton_outside_stand_save_clicked()
{
    QString label = ui->lineEdit_stand_result_label->text();
    DetectSettings::instance().setDetectParam(result_param_.first,result_param_.second, label);
    DetectSettings::instance().saveSetting();
}

void CalibrateView::on_pushButton_inside_stand_save_clicked()
{

}

