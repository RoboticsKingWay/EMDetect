#include "calibrateview.h"
#include "ui_calibrateview.h"
#include "UnitCalc.h"
#include "DetectSettings.h"
#include <QFileDialog>

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
    cfg_detection_outside_list_.clear();
    cfg_detection_inside_list_.clear();
    ui->comboBox_inside_list->clear();
    ui->comboBox_inside_del->clear();
    ui->comboBox_outside_list->clear();
    ui->comboBox_outside_del->clear();
//    cfg_detection_list_ 读取配置参数
//    for(int i = 0; i < 5; i++)
//    {
//        DetectDeclaerParam param;
//        param.label = QString("缺陷%1").arg(i+1);
//        param.depth = i+1;
//        param.length = i*10+1;
//        param.equivalent = i*2+1;
//        param.dete_type = EMDETECTION_TYPE::E_DETECTION_OUTER;
//        cfg_detection_list_[param.label] = param;
//        ui->comboBox_outside_list->addItem(param.label);
//        ui->comboBox_outside_del->addItem(param.label);
//    }

//    for(int i = 0; i < 5; i++)
//    {
//        DetectDeclaerParam param;
//        param.label = QString("缺陷%1").arg(i+6);
//        param.equivalent = i*2+1;
//        param.dete_type = EMDETECTION_TYPE::E_DETECTION_INNER;
//        cfg_detection_list_[param.label] = param;
//        ui->comboBox_inside_list->addItem(param.label);
//        ui->comboBox_inside_del->addItem(param.label);
//    }
//    result_param_.first   = DetectSettings::instance().fitted_param_a();
//    result_param_.second  = DetectSettings::instance().fitted_param_b();
//    QString text = QString("y = %1x + %2").arg(result_param_.first).arg(result_param_.second);
//    ui->lineEdit_stand_result->setText(text);
//    ui->lineEdit_stand_result_label->setText(DetectSettings::instance().detect_profile());
}

CalibrateView::~CalibrateView()
{
    delete ui;
}

void CalibrateView::initView(/*std::function<void(QVector<QPointF>&)> getDetectRectData_Func*/)
{
//    getDetectRectData_Func_ = getDetectRectData_Func;
    result_param_.first   = DetectSettings::instance().fitted_param_a();
    result_param_.second  = DetectSettings::instance().fitted_param_b();
    QString text = QString("y = %1x + %2").arg(result_param_.first).arg(result_param_.second);
    ui->lineEdit_stand_result->setText(text);
//    ui->lineEdit_stand_result_label->setText(DetectSettings::instance().detect_profile());
}

QVector<double> extractFloatsFromBracedString(const QString &input)
{
    if (input.isEmpty() || input.length() < 4)
    {
        return QVector<double>{};
    }
    // 检查首字符和尾字符是否都是双引号
    QVector<double> results;
    QStringList parts = input.split(',', QString::SkipEmptyParts);
    for (const QString &part : parts)
    {
        // 去除空白字符
        QString cleanedPart = part.trimmed();

        // 提取浮点数
        bool ok;
        double number = cleanedPart.toDouble(&ok);

        if (ok)
        {
            // 如果转换成功，添加到结果列表
            results.append(number);
        }
        else
        {
            // 转换失败，打印错误消息
            qDebug() << "Failed to convert to double:" << cleanedPart;
        }
    }
    return results;
}

QVector<QString> extractStringFromBracedString(const QString &input)
{
    if (input.isEmpty() || input.length() < 4)
    {
        return QVector<QString>{};
    }
    // 检查首字符和尾字符是否都是双引号
    QVector<QString> results;
    QStringList parts = input.split(',', QString::SkipEmptyParts);
    for (const QString &part : parts)
    {
        // 去除空白字符
        QString cleanedPart = part.trimmed();
        results.append(cleanedPart);
    }
    return results;
}

bool CalibrateView::importSetting(QString dir,bool isOutside)
{
//    QString config_dir = QDir::currentPath() + "//config//detect.ini";
    QString config_dir = dir;
    if(!QFile::exists(config_dir))
    {
        QMessageBox::critical(nullptr, "Error", "配置文件 detect.ini 不存在!");
        return false;
    }
    QSettings settings(config_dir, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("utf-8")); // 解决乱码
    try
    {
        if(isOutside)
        {
            QString tag = settings.value("outside/tag","304钢").toString();

            QString detects = settings.value("outside/detectList","").toString();
            QVector<QString> detectList = extractStringFromBracedString(detects);

            QString detectAmplitudes = settings.value("outside/detectAmplitudeList","").toString();
            QVector<double> detectAmplitudeList = extractFloatsFromBracedString(detectAmplitudes);

            QString widths = settings.value("outside/widthList","").toString();
            QVector<double> widthList = extractFloatsFromBracedString(widths);

            QString depths = settings.value("outside/depthList","").toString();
            QVector<double> depthList = extractFloatsFromBracedString(depths);

            result_param_.first = settings.value("outside/fitted_param_a","").toDouble();
            result_param_.second = settings.value("outside/fitted_param_b","").toDouble();
            if((detectList.size() == detectAmplitudeList.size()) && detectList.size() != 0)
            {
                cfg_detection_outside_list_.clear();
                ui->comboBox_outside_list->clear();
                ui->comboBox_outside_del->clear();
                for(int i = 0; i < detectList.size(); i++)
                {
                    OutsideDetectParam param;
                    param.label = detectList[i];
                    param.depth = depthList[i];
                    param.length = widthList[i];
                    param.equivalent = detectAmplitudeList[i];
                    cfg_detection_outside_list_[detectList[i]] = param;
                    ui->comboBox_outside_list->addItem(param.label);
                    ui->comboBox_outside_del->addItem(param.label);
                }
                on_comboBox_outside_list_currentIndexChanged(0);
                QString text = QString("y = %1x + %2").arg(result_param_.first,0,'f',2).arg(result_param_.second,0,'f',2);
                ui->lineEdit_stand_result->setText(text);
                update_function_result(result_param_);
                update_outside_detection_list(cfg_detection_outside_list_);
                return true;
            }
        }
        else
        {

            QString tag = settings.value("inside/tag","304钢").toString();
            QString detects = settings.value("outside/detectList","").toString();
            QVector<QString> detectList = extractStringFromBracedString(detects);

            QString detectAmplitudes = settings.value("outside/detectAmplitudeList","").toString();
            QVector<double> detectAmplitudeList = extractFloatsFromBracedString(detectAmplitudes);
            if(detectList.size() == detectAmplitudeList.size())
            {
                cfg_detection_inside_list_.clear();
                ui->comboBox_inside_list->clear();
                ui->comboBox_inside_del->clear();
                for(int i = 0; i < detectList.size(); i++)
                {
                    InsideDetectParam param;
                    param.label = detectList[i];
                    param.equivalent = detectAmplitudeList[i];
                    cfg_detection_inside_list_[detectList[i]] = param;
                    ui->comboBox_inside_list->addItem(param.label);
                    ui->comboBox_inside_del->addItem(param.label);
                }
                on_comboBox_inside_list_currentIndexChanged(0);
                update_inside_detection_list(cfg_detection_inside_list_);
                return true;
            }
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "read calibration.ini error: " << e.what();
        QMessageBox::critical(nullptr, "config Error", QString(e.what()));
        return false;
    }
    return false;
}

bool CalibrateView::saveSetting(QString dir,bool isOutside)
{
    QString config_dir = dir;
    if(QFile::exists(config_dir))
    {
        //QMessageBox::critical(nullptr, "Error", "保存文件已经存在，保存失败!");
        //return false;
    }
    QSettings settings(config_dir, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));
    bool isBegin = true;
    if(isOutside)
    {
        QString tag;
        QString detectList;
        QString detectAmplitudeList;
        QString widthList;
        QString depthList;
        for(auto& param : cfg_detection_outside_list_)
        {
            if(!isBegin)
            {
                detectList += ',';
                detectList += param.label;

                detectAmplitudeList += ',';
                detectAmplitudeList += QString::number(param.equivalent);

                widthList += ',';
                widthList += QString::number(param.length);

                depthList += ',';
                depthList += QString::number(param.depth);
            }
            else
            {
                detectList += param.label;
                detectAmplitudeList += QString::number(param.equivalent);
                widthList += QString::number(param.length);
                depthList += QString::number(param.depth);
                isBegin = false;
            }
        }
//        detectList.append('"');
//        detectAmplitudeList += '"';
//        widthList += '"';
//        depthList += '"';
        try
        {
            settings.setValue("outside/tag",tag);
            settings.setValue("outside/detectList",detectList);
            settings.setValue("outside/detectAmplitudeList",detectAmplitudeList);
            settings.setValue("outside/widthList",widthList);
            settings.setValue("outside/depthList",depthList);

            settings.setValue("outside/fitted_param_a",result_param_.first);
            settings.setValue("outside/fitted_param_b",result_param_.second);
            settings.sync();
        }
        catch (const std::exception &e)
        {
            qDebug() << "write calibration.ini outside cfg: " << e.what();
            QMessageBox::critical(nullptr, "config Error", QString(e.what()));
            return false;
        }
    }
    else
    {
        QString tag;
        QString detectList;
        QString detectAmplitudeList;
        for(auto& param : cfg_detection_inside_list_)
        {
            if(!isBegin)
            {
                detectList += ',';
                detectList += param.label;

                detectAmplitudeList += ',';
                detectAmplitudeList += QString::number(param.equivalent);

            }
            else
            {
                detectList += param.label;
                detectAmplitudeList += QString::number(param.equivalent);
                isBegin = false;
            }
        }
//        detectList.append('"');
//        detectAmplitudeList += '"';
        try
        {
            settings.setValue("inside/tag",tag);
            settings.setValue("inside/detectList",detectList);
            settings.setValue("inside/detectAmplitudeList",detectAmplitudeList);
            settings.sync();
        }
        catch (const std::exception &e)
        {
            qDebug() << "write calibration.ini inside cfg error: " << e.what();
            QMessageBox::critical(nullptr, "config Error", QString(e.what()));
            return false;
        }
    }

    return true;
}


void CalibrateView::on_GetRectData(QVector<QPointF>& points)
{
    if(this->isVisible())
    {
        std::vector<int> data;
        for(auto& point : points)
        {
            data.push_back(point.y());
        }
        int max,min;
        calcMaxMin(data,max,min);
        QString text = QString::number(max - min);
        if(this->currentIndex() == 1)
        {
            ui->lineEdit_inside_write->setText(text);
        }
        else
        {
            ui->lineEdit_outside_db_set->setText(text);
        }
    }
}

void CalibrateView::on_comboBox_outside_list_currentIndexChanged(int index)
{
    QString label = ui->comboBox_outside_list->currentText();
    auto it = cfg_detection_outside_list_.find(label);
    if(it != cfg_detection_outside_list_.end())
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
    OutsideDetectParam param;
    param.label   = ui->lineEdit_outside_addnum->text();
    if(!param.label.contains("缺陷"))
    {
        param.label   = QString("缺陷") + ui->lineEdit_outside_addnum->text();
    }
    if(cfg_detection_outside_list_.find(param.label) == cfg_detection_outside_list_.end())
    {
        param.depth   = ui->lineEdit_deep_set->text().toDouble();
        param.length  = ui->lineEdit_width_set->text().toDouble();
        param.equivalent  = ui->lineEdit_outside_db_set->text().toDouble();
    //    param.dete_type = EMDETECTION_TYPE::E_DETECTION_OUTER;

        cfg_detection_outside_list_[param.label] = param;
        ui->comboBox_outside_list->addItem(param.label);
        ui->comboBox_outside_del->addItem(param.label);
        update_outside_detection_list(cfg_detection_outside_list_);
        QMessageBox::information(this,"info","添加成功");
    }
    else
    {
        QMessageBox::information(this,"info","不要重复添加缺陷信息");
    }
}

void CalibrateView::on_pushButton_outside_del_clicked()
{
    QString label = ui->comboBox_outside_del->currentText();
    auto it = cfg_detection_outside_list_.find(label);
    if(it != cfg_detection_outside_list_.end())
    {
        cfg_detection_outside_list_.erase(it);
        ui->comboBox_outside_del->removeItem(ui->comboBox_outside_del->currentIndex());
        ui->comboBox_outside_list->clear();
        for(auto& item : cfg_detection_outside_list_)
        {
            if(item.label != label)
            {
                ui->comboBox_outside_list->addItem(item.label);
            }
        }
        update_outside_detection_list(cfg_detection_outside_list_);
        QMessageBox::information(this,"info","删除成功");
    }
}

void CalibrateView::on_pushButton_outside_stand_clicked()
{
    std::vector<std::pair<double, double>> points;
    for(auto& item : cfg_detection_outside_list_)
    {
//        if(item.dete_type == EMDETECTION_TYPE::E_DETECTION_OUTER)
        {
            std::pair<double, double> point;
            point.first   = item.depth/item.length;
            point.second  = item.equivalent;
            points.push_back(point);
        }
    }
    if(leastSquares(points, result_param_))
    {
        QString text = QString("y = %1x + %2").arg(result_param_.first,0,'f',2).arg(result_param_.second,0,'f',2);
        ui->lineEdit_stand_result->setText(text);
        update_function_result(result_param_);
    }

}

void CalibrateView::on_pushButton_outside_stand_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt)(*.ini);;Ini Files (*.*)"));
    if (!fileName.isEmpty())
    {
        if (saveSetting(fileName,true))
        {
            QMessageBox::information(this, tr("Save File"), tr("File saved successfully."));
        }
        else
        {
            QMessageBox::warning(this, tr("Save File"), tr("Could not open file for writing."));
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file saved.");
    }
}

void CalibrateView::on_pushButton_outside_import_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Calibration File", "", tr("Calibration Text Files (*.txt)(*.ini);;Ini Files (*.*)"));
    if (!filePath.isEmpty())
    {
        if(!importSetting(filePath, true))
        {
            QMessageBox::warning(this, "Error", "file error.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file selected.");
    }
}

void CalibrateView::on_comboBox_inside_list_currentIndexChanged(int index)
{
    QString label = ui->comboBox_inside_list->currentText();
    auto it = cfg_detection_inside_list_.find(label);
    if(it != cfg_detection_inside_list_.end())
    {
        ui->label_inside_am->setText(QString::number(it->equivalent));
    }
    else
    {
        ui->label_inside_am->setText("");
    }
}


void CalibrateView::on_pushButton_inside_add_clicked()
{
    InsideDetectParam param;
    param.label   = ui->lineEdit_inside_add_num->text();
    if(!param.label.contains("缺陷"))
    {
        param.label   = QString("缺陷") + ui->lineEdit_inside_add_num->text();
    }
    if(cfg_detection_inside_list_.find(param.label) == cfg_detection_inside_list_.end())
    {
        param.equivalent = ui->lineEdit_inside_write->text().toDouble();
    //    param.amplitude  = 10 * std::log10((max.y() - min.y()) / db_list[0]);;
    //    param.dete_type  = EMDETECTION_TYPE::E_DETECTION_INNER;

        cfg_detection_inside_list_[param.label] = param;
        ui->comboBox_inside_list->addItem(param.label);
        ui->comboBox_inside_del->addItem(param.label);
        update_inside_detection_list(cfg_detection_inside_list_);
        QMessageBox::information(this,"info","添加成功");
    }
    else
    {
        QMessageBox::information(this,"info","不要重复添加缺陷信息");
    }
}


void CalibrateView::on_pushButton_inside_del_clicked()
{
    QString label = ui->comboBox_inside_del->currentText();
    auto it = cfg_detection_inside_list_.find(label);
    if(it != cfg_detection_inside_list_.end())
    {
        cfg_detection_inside_list_.erase(it);
        ui->comboBox_inside_del->removeItem(ui->comboBox_inside_del->currentIndex());
        ui->comboBox_inside_list->clear();
        for(auto& item : cfg_detection_inside_list_)
        {
            if(item.label != label)
            {
                ui->comboBox_inside_list->addItem(item.label);
            }
        }
        update_inside_detection_list(cfg_detection_inside_list_);
        QMessageBox::information(this,"info","删除成功");
    }
}

void CalibrateView::on_pushButton_inside_import_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Calibration File", "", tr("Calibration Text Files (*.txt)(*.ini);;Ini Files (*.*)"));
    if (!filePath.isEmpty())
    {
        if(!importSetting(filePath, false))
        {
            QMessageBox::warning(this, "Error", "file error.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file selected.");
    }
}

void CalibrateView::on_pushButton_inside_stand_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt)(*.ini);;Ini Files (*.*)"));
    if (!fileName.isEmpty())
    {
        if (saveSetting(fileName,false))
        {
            QMessageBox::information(this, tr("Save File"), tr("File saved successfully."));
        }
        else
        {
            QMessageBox::warning(this, tr("Save File"), tr("Could not open file for writing."));
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "No file saved.");
    }
}

