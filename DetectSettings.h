#ifndef DETECTSETTINGS_H
#define DETECTSETTINGS_H

#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QVector>
#include <QDir>
#include <QFile>
#include <QRegExp>
#include <QMessageBox>
#include <QDebug>

// 检测配置文件
class DetectSettings
{
private:
    DetectSettings() = default;
    ~DetectSettings()
    {
        saveSetting();
    }
protected:
    QVector<double> sensitivity_list_;
    int max_points_count_ {12000};
    int max_draw_points_count_ {300};
    int add_point_count_ {20};
    int real_time_rate_ {5};
    double calc_coefficient_ {30.0};
    int auto_save_source_ {1};
    double save_scan_length_{100.1};
    double sensitivity_perview_{1.91};

    int scan_speed_          = 40;
    int upline_              = 68000;
    int downline_            = 49000;
    double fitted_param_a_   = -5.1;
    double fitted_param_b_   = -1000.1;
    QString detect_profile_  = "奥氏体钢";
    double zoom_butterfly_view_      = 1.05;
    double zoom_real_time_view_      = 1.05;
    int filter_size_         = 10;
public:
    const int& filter_size()
    {
        return filter_size_;
    }
    const double& zoom_real_time_view()
    {
        return zoom_real_time_view_;
    }
    const double& zoom_butterfly_view()
    {
        return zoom_butterfly_view_;
    }
    const QVector<double>& sensitivity_list()
    {
        return sensitivity_list_;
    }
    const int& max_points_count()
    {
        return max_points_count_;
    }
    const int& max_darw_point_count()
    {
        return max_draw_points_count_;
    }
    const int& add_point_count()
    {
        return add_point_count_;
    }
    const int& real_time_rate()
    {
        return real_time_rate_;
    }
    const double& calc_coefficient()
    {
        return calc_coefficient_;
    }
    const int& auto_save_source()
    {
        return auto_save_source_;
    }
    const double& save_scan_length()
    {
        return save_scan_length_;
    }
    const double& sensitivity_perview()
    {
        return sensitivity_perview_;
    }
    const int& scan_speed()
    {
        return scan_speed_;
    }
    const int& upline()
    {
        return upline_;
    }
    const int& downline()
    {
        return downline_;
    }
    const double& fitted_param_a()
    {
        return fitted_param_a_;
    }
    const double& fitted_param_b()
    {
        return fitted_param_b_;
    }
    QString& detect_profile()
    {
        return detect_profile_;
    }
    void setline(int upline,int downline)
    {
        upline_ = upline;
        downline_ = downline;
    }
    void setDetectParam(double a, double b, QString label)
    {
        fitted_param_a_ = a;
        fitted_param_b_ = b;
        detect_profile_ = label;
    }
public:
    static DetectSettings& instance()
    {
        static DetectSettings settings;
        return settings;
    }
    QVector<double> extractFloatsFromBracedString(const QString &input)
    {
        if (input.isEmpty() || input.length() < 4)
        {
            return QVector<double>{1.91,2.91,3.91};
        }

        // 检查首字符和尾字符是否都是双引号
        QVector<double> results;
        //        if(input.at(0) == '"' && input.at(input.length() - 1) == '"')
        {
            //            QString str = input.mid(1,input.length()-2);
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
        }
        //        else
        //        {
        //            return QVector<double>{1.91,2.91,3.91};
        //        }
        return results;
    }

    bool initSettings()
    {
        QString config_dir = QDir::currentPath() + "//config//detect.ini";
        if(!QFile::exists(config_dir))
        {
            QMessageBox::critical(nullptr, "Error", "配置文件 detect.ini 不存在!");
            return false;
        }
        QSettings settings(config_dir, QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("utf-8")); // 解决乱码
        try
        {
            QString list = settings.value("Settings/sensitivity").toString();
            sensitivity_list_ = extractFloatsFromBracedString(list);
            max_points_count_ = settings.value("Settings/max_points_count", 12000).toInt();
            max_draw_points_count_ = settings.value("Settings/max_draw_points_count", 300).toInt();
            add_point_count_ = settings.value("Settings/add_point_count", 20).toInt();
            real_time_rate_ = settings.value("Settings/real_time_rate", 5).toInt();
            filter_size_    = settings.value("Settings/filter_size", 10).toInt();
            if(real_time_rate_ > 10 || real_time_rate_ < 1)
            {
                real_time_rate_ = 5;
            }
            calc_coefficient_ = settings.value("Settings/calc_coefficient", 30.0).toDouble();
            auto_save_source_ = settings.value("Settings/auto_save_source", 1).toInt();
            save_scan_length_ = settings.value("Settings/save_scan_length", 120.1).toDouble();
            sensitivity_perview_ = settings.value("Settings/sensitivity_perview", 2.91).toDouble();
            zoom_real_time_view_ = settings.value("Settings/zoom_real_time_view", 1.05).toDouble();
            zoom_butterfly_view_ = settings.value("Settings/zoom_butterfly_view", 1.05).toDouble();
            qDebug()<<"config: list"<<list<<" max_points_count_"<<max_points_count_<<" add_point_count_"<<add_point_count_\
                     <<" real_time_rate_"<<real_time_rate_<<" calc_coefficient_"<<calc_coefficient_<<" auto_save_source_"<<auto_save_source_\
                     <<"sensitivity_perview_"<<sensitivity_perview_<<"save_scan_length_"<<save_scan_length_;
            //
            scan_speed_ = settings.value("Settings/scan_speed", 40.0).toInt();
            upline_ = settings.value("Settings/upline", 30000.0).toInt();
            downline_ = settings.value("Settings/downline", -30000.0).toInt();
            fitted_param_a_ = settings.value("Settings/fitted_param_a", 30.0).toDouble();
            fitted_param_b_ = settings.value("Settings/fitted_param_b", 30.0).toDouble();
            detect_profile_ = settings.value("Settings/detect_profile", "奥氏体钢").toString();
                              qDebug()<<"config: scan_speed_"<<scan_speed_<<" upline_"<<upline_<<" downline_"<<downline_\
                              <<" fitted_param_a_"<<fitted_param_a_<<" fitted_param_b_"<<fitted_param_b_<<" detect_profile_"<<detect_profile_;
        }
        catch (const std::exception &e)
        {
            qDebug() << "read detect.ini error: " << e.what();
            QMessageBox::critical(nullptr, "config Error", QString(e.what()));
            return false;
        }
        return true;
    }

    bool saveSetting()
    {
        qDebug()<<"save settings";
        QString config_dir = QDir::currentPath() + "//config//detect.ini";
        if(!QFile::exists(config_dir))
        {
            QMessageBox::critical(nullptr, "Error", "配置文件 detect.ini 不存在!");
            return false;
        }
        QSettings settings(config_dir, QSettings::IniFormat);
        settings.setIniCodec(QTextCodec::codecForName("utf-8"));
        try
        {
            settings.setValue("Settings/upline", upline_);
            settings.setValue("Settings/downline", downline_);
            settings.setValue("Settings/fitted_param_a", fitted_param_a_);
            settings.setValue("Settings/fitted_param_b", fitted_param_b_);
            settings.setValue("Settings/detect_profile", detect_profile_);
            settings.sync();
        }
        catch (const std::exception &e)
        {
            qDebug() << "write detect.ini error: " << e.what();
            QMessageBox::critical(nullptr, "config Error", QString(e.what()));
            return false;
        }
        return true;
    }
};

#endif // DETECTSETTINGS_H
