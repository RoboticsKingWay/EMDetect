#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QThread>
#include <QMutex>
#include <QDateTime>
#include <windows.h>
#include <QDir>
#include "UnitData.h"
#include "SafeQueue.h"
#include "QXlsxExcelHelper.h"


class DataManager : public QThread
{
    Q_OBJECT
public:
    DataManager(QObject *parent = nullptr)
        : QThread(parent)
    {
        is_runing_  = false;
        is_pause_   = false;

        saveas_dir_ = QDir::currentPath() + "//data//";
        QDir d(saveas_dir_);
        if(!d.exists())
        {
            QDir().mkdir(saveas_dir_); // 创建绝对路径
        }
        this->start();
    }

    virtual ~DataManager()
    {
        if(is_runing_)
        {
            is_runing_ = false;
            this->quit();
            this->wait();
        }
    }
    void setSaveParam(double sensitivity,QString label,double scan_length)
    {
        file_label_ = label;
        file_scan_length_ = scan_length;
        sensitivity_ = sensitivity;
    }

    bool saveDataToFile(double sensitivity,QString lable,double len,QVector<ChinnelData>& list,QString dir = "")
    {

        QString file_dir;
        if(dir == "")
        {
           file_dir = saveas_dir_;
            QString prefix = lable+ "_" + QString::number(len)+"_" + QString::number(sensitivity);
    //        file_label_ = lable;
    //        file_scan_length_ = len;
    //        sensitivity_ = sensitivity;
            QString file_name = generateTimeBasedFileName(prefix,".xlsx");
            file_dir += file_name;
        }
        else
        {
            file_dir = dir;
        }
        return QXlsxExcelHelper::getInstance().saveDataToExcel(list.size(),sensitivity,file_label_,len,list,file_dir);
    }

    QString getDir()
    {
        return saveas_dir_;
    }
public slots:
    void DataHandle(QVector<ChinnelData> list)
    {
        safe_queue_.enqueue(list);
//        qDebug()<<"DataHandle:"<<QDateTime::currentDateTime();
    }

private:
    void setDir(QString& dir)
    {
        saveas_dir_ = dir;
        saveas_dir_ += "//";
        //QString absolutePath = QDir::currentPath() + "//" + saveas_dir_ + "//"; // 当前工作目录下的子目录
        QDir d(saveas_dir_);
        if(!d.exists())
        {
            QDir().mkdir(saveas_dir_); // 创建绝对路径
        }
    }

    // 生成基于时间的文件名
    QString generateTimeBasedFileName(const QString &prefix, const QString &suffix)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString baseName = currentDateTime.toString("yyyy-MM-dd_hh-mm-ss_zzz") + "_" + prefix;
        QString fileName = baseName + suffix;
        return fileName;
    }
//    void saveDataToFile()
//    {
//        QVector<ChinnelData> list;
//        if(safe_queue_.dequeue(list))
//        {
//            QString file_dir = saveas_dir_;
//            QString file_name = generateTimeBasedFileName("src",".xlsx");
//            file_dir += file_name;
//            QXlsxExcelHelper::getInstance().saveDataToExcel(list.size(),QString(""),0.0,list,file_dir);
//        }
//    }

    void run() override
    {
        is_runing_ = true;
        while(is_runing_)
        {
//            saveDataToFile();
            QVector<ChinnelData> list;
            if(safe_queue_.dequeue(list))
            {
                QString file_dir = saveas_dir_;
                QString file_name = generateTimeBasedFileName("src",".xlsx");
                file_dir += file_name;
                double sensitivity = DetectSettings::instance().sensitivity_perview();
                double scan_length = DetectSettings::instance().save_scan_length();
//                qDebug()<<"save to "<<file_dir<<" "<<QDateTime::currentDateTime()<<"\n";
                QXlsxExcelHelper::getInstance().saveDataToExcel(list.size(),sensitivity,QString(""),scan_length,list,file_dir);
            }
            QThread::msleep(100);
        }
        qDebug()<<"execl data thread exit.";
    }
private:
    bool is_runing_ {false};
    bool is_pause_ {false};
    SafeQueue<QVector<ChinnelData>> safe_queue_;
    QString saveas_dir_;
    QString file_label_ {""};
    double file_scan_length_ {120.1};
    double sensitivity_{1.780};
};


#endif // DATAMANAGER_H
