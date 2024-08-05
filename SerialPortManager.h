#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QRegularExpression>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QVector2D>
#include "UnitData.h"
#include "DetectSettings.h"
#include "SafeQueue.h"
#include "DynamicFilter.h"

//QT_BEGIN_NAMESPACE

class SerialPortManager : public QThread
{
    Q_OBJECT
public:
    SerialPortManager(QObject *parent = nullptr)
        : QThread(parent)
    {
        is_opened_ = false;
        is_pause_ = true;
        is_runing_ = false;
        m_serialPort = nullptr;
        draw_add_size_ = DetectSettings::instance().add_point_count();
        src_max_size_ = DetectSettings::instance().max_points_count();
        filter_ptr_ = new DynamicFilter(DetectSettings::instance().filter_size());
    }

    ~SerialPortManager()
    {
        if(filter_ptr_)
        {
            delete filter_ptr_;
            filter_ptr_ = nullptr;
        }
        stopThread();
        if(m_serialPort)
        {
            delete m_serialPort;
            m_serialPort = nullptr;
        }
        closePort();
    }
public:
    void listPorts(QVector<QString>& port_list)
    {
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        foreach (const QSerialPortInfo &port, ports)
        {
            qDebug() << "Port name:" << port.portName();
            qDebug() << "Description:" << port.description();
            qDebug() << "Manufacturer:" << port.manufacturer();
            qDebug() << "Serial number:" << port.serialNumber();
            qDebug() << "Location:" << port.systemLocation();
            qDebug() << "Vendor Identifier:" << port.vendorIdentifier();
            qDebug() << "Product Identifier:" << port.productIdentifier();
            qDebug() << "Busy:" << port.isBusy();
//            if(!port.isBusy())
            {
                port_list.append(port.portName());
            }
        }
    }

    bool closeConnectSerial()
    {
        if(m_serialPort)
        {
            if(is_opened_ && is_pause_ == false)
            {
                QMessageBox::critical(nullptr, "Error", "操作失败,请先停止采集动作!");
                return false;
            }
            closePort();
            QThread::msleep(100);
            m_serialPort = nullptr;
            delete m_serialPort;
        }
        return true;
    }
    bool connectSerial(const QString portName = "COM3")
    {
        if(m_serialPort)
        {
            if(m_serialPort->isOpen())
            {
               QMessageBox::critical(nullptr, "Error", "串口已连接，请先关闭再选择重连");
                return false;
            }
            closePort();
            delete m_serialPort;
        }
        m_serialPort = new QSerialPort(serial_param_.port, this);
        port_name_ = portName;
        // 配置串口参数
        m_serialPort->setBaudRate(serial_param_.borate);
        m_serialPort->setDataBits((QSerialPort::DataBits)serial_param_.databit);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits((QSerialPort::StopBits)serial_param_.stopbit);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        m_serialPort->setReadBufferSize(128);
        qDebug()<<"serial buf_size="<<m_serialPort->readBufferSize()<<"\r\n";
        // 连接信号和槽
        //connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortManager::readData);
        connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError,Qt::QueuedConnection);
        //connect(&m_reconnectTimer, &QTimer::timeout, this, &SerialPortManager::reconnect);

        // 尝试打开串口
        openPort();
        if(!is_runing_)
        {
            startThread();
        }
        data_src_list_.clear();
        return is_opened_;
    }
    void openPort()
    {
        if (m_serialPort->open(QIODevice::ReadWrite))
        {
            qDebug() << "port:"<<serial_param_.port<<"opened.";
            is_opened_ = true;
        }
        else
        {
            QMessageBox::critical(nullptr, "Error", "连接串口失败");
            is_opened_ = false;
        }
    }

    void readData(const QByteArray &data)
    {
        // 读取串口数据
        if(m_serialPort->isOpen())
        {
            static QByteArray last_str = "";
            last_str += data;
            QRegularExpression regex("\\[(.*?)\\]"); // 匹配以 '[' 开头，以 ']' 结尾的字符串
            QRegularExpressionMatchIterator iter = regex.globalMatch(last_str);

            int lastPosition = 0; // 记录最后一个字符串 A 出现的位置
            while (iter.hasNext())
            {
                QRegularExpressionMatch match = iter.next();
                if (match.hasMatch())
                {
                    QString stringA = match.captured(1); // 获取匹配到的字符串 A
                    QStringList list = stringA.split(",");
                    if(list.size() == CH_NUM || list.size() == 6)
                    {
                        ChinnelMagData ch_data;
                        for(int i = 0; i < CH_NUM; i++)
                        {
                            ch_data.data[i] = list.at(i).toInt()/SCALE_SIZE;
                        }
                        data_src_list_.push_back(ChinnelData(count_index_++,ch_data));
                    }
                    else
                    {
                        qDebug()<<"ch_data size != "<<CH_NUM<<" size = "<<list.size();
                        qDebug()<<"err_str:"<<stringA;
                    }
                    lastPosition = match.capturedEnd(); // 更新最后一个字符串 A 出现的位置
                    if(data_src_list_.size() >= src_max_size_)
                    {
                        qDebug()<<"size >= "<<src_max_size_;
                        saveDataToExcelFile();
                        //emit clearRealTimeSerial();
//                        count_index_ = 0;
                        data_src_list_.clear();
                    }
                    if(count_index_ % draw_add_size_ == 0)
                    {
                        setDrawData();
                    }
                }
            }
            last_str = last_str.mid(lastPosition);
        }
    }
    void setDrawData()
    {
        if(data_src_list_.size() >= draw_add_size_ && data_src_list_.size()%draw_add_size_ == 0)
        {
            QVector<ChinnelData> temp;
            int start = (count_index_ % src_max_size_) - draw_add_size_;
            for(int i = start; i < (draw_add_size_ + start); i++)
            {
                ChinnelData data;
                data.index = data_src_list_[i].index;
                for(int j = 0; j < CH_NUM; j++)
                {
                    data.mag_data.data[j] = data_src_list_[i].mag_data.data[j];
                }
                //if(filter_ptr_->filter(data.mag_data.data[0]))
                {
                    temp.push_back(data);
                }
            }
            if(temp.size())
            {
                draw_queue_.enqueue(temp);
            }
        }
    }

    QVector<ChinnelData> getDrawData()
    {
        QVector<ChinnelData> temp;
        draw_queue_.dequeue(temp);
        return temp;
    }

    void getSrcListData(QVector<ChinnelData>& list)
    {
        if(mutex_.tryLock(100))
        {
            if(data_src_list_.size())
            {
                list.resize(data_src_list_.size());
                list = data_src_list_;
            }
            mutex_.unlock();
        }
        else
        {
            qDebug()<<"get src list mutex_.try_lock() failed"<<"\n";
        }
    }

    void saveDataToExcelFile()
    {
        //if(mutex_.try_lock())
        {
//            qDebug()<<"saveDataToExcelFile send:"<<QDateTime::currentDateTime();
            if(DetectSettings::instance().auto_save_source())
            {
                // 保存每次采集的原始数据
                emit SendData(data_src_list_);
            }
//            qDebug()<<"saveDataToExcelFile sendok:"<<QDateTime::currentDateTime();
            //mutex_.unlock();
        }
    }

    void clearSerialPort()
    {
        if(m_serialPort->isOpen())
        {
            m_serialPort->clear();
        }
    }
    void clearSrcListData()
    {
        //if(mutex_.tryLock(100))
        {
            clearSerialPort();
            data_src_list_.clear();
            count_index_ = 0;
           // mutex_.unlock();
        }
        //else
        {
            //qDebug()<<"clear src list mutex_.try_lock() failed"<<"\n";
        }
    }

    void closePort()
    {
        if(m_serialPort)
        {
            if(m_serialPort->isOpen())
            {
                m_serialPort->close();
                qDebug() << "close port success.";
                is_opened_ = false;
            }
        }
    }

    bool isPortOpened()
    {
        if(m_serialPort)
        {
            return m_serialPort->isOpen();
        }
        return false;
    }
    void startReconnectTimer()
    {
        if (!m_reconnectTimer.isActive())
        {
            m_reconnectTimer.start(5000); // 5秒后尝试重连
        }
    }

    void stopReconnectTimer()
    {
        if (m_reconnectTimer.isActive())
        {
            m_reconnectTimer.stop(); // 5秒后尝试重连
        }
    }
    void setSerialPause(bool action)
    {
        is_pause_ = action;
    }
    int getHeartbeatState()
    {
        return heart_beat_state_;
    }
public slots:
    void handleError(QSerialPort::SerialPortError error)
    {
        qDebug() << "Serial port error occurred:" << error;
        if (error == QSerialPort::OpenError)
        {
            if(m_serialPort)
            {
                m_serialPort->open(QIODevice::ReadWrite);
            }
        }
    }
    void getSerialParam(SerialParam& param)
    {
        serial_param_ = param;
        if(param.action == E_SERIAL_CONNECT)
        {
            connectSerial(serial_param_.port);
        }
        else
        {
            closeConnectSerial();
        }
        heart_beat_state_ = (isPortOpened()== true ? E_SERIAL_CONNECT:E_SERIAL_CLOSE);
    }
signals:
    void SendData(QVector<ChinnelData> list);
    void clearRealTimeSerial();
private:
    void startThread()
    {
        is_runing_ = true;
        start();
    }
    void stopThread()
    {
        is_runing_ = false;
        this->quit();
        this->wait(1000);
    }
    void run() override
    {
        int heart_beat_count = 0;
        while (!isInterruptionRequested() && is_runing_)
        {
            if(is_pause_)
            {
                QThread::msleep(100); // 100ms
                continue;
            }
            if(!is_opened_)
            {
                openPort();
                QThread::msleep(100); // 100ms
                continue;
            }
            if (m_serialPort->waitForReadyRead(2000))//1000ms
            {
                QByteArray data = m_serialPort->readAll();
                if(QString(data) != "")
                {
                    readData(data);
                    heart_beat_state_ = E_SERIAL_CONNECT;
                    continue;
                }
                else
                {
                    qDebug()<<"recv:empty\r\n";
                }
            }
            else
            {
                heart_beat_count++;
                if(heart_beat_count > 10)
                {
                    heart_beat_count = 0;
                    heart_beat_state_ = E_SERIAL_CLOSE;
                    closePort();
                }
            }
        }
        qDebug()<<"serial thread exit.";
    }

private:
    QMutex mutex_;
    int count_index_ {0};
    int count_size_  {0};
    bool is_runing_ {false};
    bool is_pause_ {false};
    int heart_beat_state_ {E_SERIAL_CLOSE}; //串口在线 与 离线状态
    QSerialPort *m_serialPort {nullptr};
    QTimer m_reconnectTimer;
    bool is_opened_ {false};
    QString port_name_;
    SerialParam serial_param_;
    QString str_data_;
    QVector<ChinnelData> data_src_list_;
    int draw_add_size_ {20};
    int src_max_size_ {12000};
    SafeQueue<QVector<ChinnelData>> draw_queue_;
    DynamicFilter* filter_ptr_;
};

// 在你的应用程序中创建SerialPortManager实例并使用
#endif // SERIALPORTMANAGER_H
