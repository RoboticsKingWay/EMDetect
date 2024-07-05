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
            this->wait(100);
        }
//        CoUninitialize();
    }
    void setLabel(QString label)
    {
        file_label_ = label;
    }

    bool saveDataToFile(QString lable,QVector<ChinnelData>& list)
    {
        QString file_dir = saveas_dir_;
        QString file_name = generateTimeBasedFileName(lable,".xlsx");
        file_dir += file_name;
        return QXlsxExcelHelper::getInstance().saveDataToExcel(list,file_dir);
    }

    QString getDir()
    {
        return saveas_dir_;
    }
public slots:
    void DataHandle(QVector<ChinnelData> list)
    {
        safe_queue_.enqueue(list);
        qDebug()<<"DataHandle\n";
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
    void saveDataToFile()
    {
        QVector<ChinnelData> list;
        if(safe_queue_.dequeue(list))
        {
            QString file_dir = saveas_dir_;
            QString file_name = generateTimeBasedFileName("src",".xlsx");
            file_dir += file_name;
            QXlsxExcelHelper::getInstance().saveDataToExcel(list,file_dir);
        }
    }

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
                qDebug()<<"save to "<<file_dir<<"\n";
                QXlsxExcelHelper::getInstance().saveDataToExcel(list,file_dir);
            }
            QThread::msleep(100);
        }
    }
private:
    bool is_runing_ {false};
    bool is_pause_ {false};
    SafeQueue<QVector<ChinnelData>> safe_queue_;
    QString saveas_dir_;
    QString file_label_ {""};
};


#endif // DATAMANAGER_H
