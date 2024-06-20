#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QRegularExpression>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QVector2D>
#include "UnitData.h"
#include "SafeQueue.h"

//QT_BEGIN_NAMESPACE

class SerialPortManager : public QThread
{
    Q_OBJECT
public:
    SerialPortManager(QObject *parent = nullptr)
        : QThread(parent)
    {
        is_opened_ = false;
        m_serialPort = nullptr;
    }

    ~SerialPortManager()
    {
        //stopReconnectTimer();
        closePort();
        stopThread();
        if(m_serialPort)
        {
            delete m_serialPort;
        }
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
            if(!port.isBusy())
            {
                port_list.append(port.portName());
            }
        }
    }

    bool connectSerial(const QString portName = "COM3")
    {
        if(m_serialPort)
        {
            closePort();
            QThread::sleep(1);
        }
        else
        {
            m_serialPort = new QSerialPort(portName, this);
        }
        port_name_ = portName;
        // 配置串口参数
        m_serialPort->setBaudRate(QSerialPort::Baud115200);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        qDebug()<<"buf_size_1="<<m_serialPort->readBufferSize()<<"\r\n";
        m_serialPort->setReadBufferSize(1024);
        qDebug()<<"buf_size_2="<<m_serialPort->readBufferSize()<<"\r\n";
        // 连接信号和槽
        //connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortManager::readData);
        connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError,Qt::QueuedConnection);
        //connect(&m_reconnectTimer, &QTimer::timeout, this, &SerialPortManager::reconnect);

        // 尝试打开串口
        openPort();
        qDebug()<<"main thread:"<<QThread::currentThreadId();
        startThread();

        //data_add_list_.resize(DRAW_ADD_SIZE);
        //data_src_list_.resize(SRC_MAX_SIZE);
        data_add_list_.clear();
        data_src_list_.clear();
        return is_opened_;
    }
    void openPort()
    {
        if (m_serialPort->open(QIODevice::ReadWrite))
        {
            qDebug() << "串口"<<port_name_<<"已打开";
            //stopReconnectTimer();
            is_opened_ = true;
        }
        else
        {
            qDebug() << "串口打开失败，尝试重连...";
            //startReconnectTimer();
            is_opened_ = false;
        }
    }

    //void readData()
    void readData(const QByteArray &data)
    {
        // 读取串口数据的槽函数
        //qDebug()<<"son thread:"<<QThread::currentThreadId();
        //QString str_debug = QString::fromUtf8(data);
        //qDebug()<<"\n\nstr_debug:"<<str_debug<<"\n\n";
        if(m_serialPort->isOpen())
        {
            static int count_index = 0;
            static QByteArray last_str = "";
            //QByteArray data = m_serialPort->readAll();
            last_str += data;
            QRegularExpression regex("\\[(.*?)\\]"); // 匹配以 '[' 开头，以 ']' 结尾的字符串
            QRegularExpressionMatchIterator iter = regex.globalMatch(last_str);
//            int startPosition = -1;
            int lastPosition = 0; // 记录最后一个字符串 A 出现的位置

            while (iter.hasNext())
            {
                QRegularExpressionMatch match = iter.next();
                if (match.hasMatch())
                {
                    QString stringA = match.captured(1); // 获取匹配到的字符串 A
                    QStringList list = stringA.split(",");
                    ChinnelMagData ch_data;
                    ch_data.data[0] = list.at(0).toInt()/SCALE_SIZE;
                    ch_data.data[1] = list.at(1).toInt()/SCALE_SIZE;
                    ch_data.data[2] = list.at(2).toInt()/SCALE_SIZE;
                    ch_data.data[3] = list.at(3).toInt()/SCALE_SIZE;
                    ch_data.data[4] = list.at(4).toInt()/SCALE_SIZE;
                    ch_data.data[5] = list.at(5).toInt()/SCALE_SIZE;
                    QDateTime currentTime = QDateTime::currentDateTime();
                    //qDebug()<<currentTime<<"-ch_data:"<<ch_data.ch1<<" "<<ch_data.ch2<<" "<<ch_data.ch3<<" "<<ch_data.ch4<<" "<<ch_data.ch5<<" "<<ch_data.ch6;
                    lastPosition = match.capturedEnd(); // 更新最后一个字符串 A 出现的位置
//                  qDebug() << "Found string A:" << stringA<<",startPosition="<<startPosition<< "lastPosition:"<<lastPosition<<"\n";

                    data_src_list_.push_back(ChinnelData(count_index++,ch_data));

                    if(data_src_list_.size() >= SRC_MAX_SIZE)
                    {
                        qDebug()<<"size >= 30000\n";
                        emit SendData(data_src_list_);
                        count_index = 0;
                        data_src_list_.clear();
                    }
                    setDrawData(count_index);
                }
            }
            last_str = last_str.mid(lastPosition);
        }
    }
    void setDrawData(int count)
    {
        mutex_.lock();
        data_add_list_.clear();
        if(data_src_list_.size() >= DRAW_ADD_SIZE)
        {
            int start = count - DRAW_ADD_SIZE;
            for(int i = 0; i < DRAW_ADD_SIZE; i++)
            {
                //qDebug()<<"i="<<i<<" count="<<count<<"\n";
                ChinnelData data;
                data.index = start + i;
                data.mag_data.data[0] = data_src_list_[start + i].mag_data.data[0];
                data.mag_data.data[1] = data_src_list_[start + i].mag_data.data[1];
                data.mag_data.data[2] = data_src_list_[start + i].mag_data.data[2];
                data.mag_data.data[3] = data_src_list_[start + i].mag_data.data[3];
                data.mag_data.data[4] = data_src_list_[start + i].mag_data.data[4];
                data.mag_data.data[5] = data_src_list_[start + i].mag_data.data[5];
                data_add_list_.push_back(data);
            }
        }
        mutex_.unlock();
    }

    QVector<ChinnelData> getDrawData()
    {
        QVector<ChinnelData> temp;
        if(mutex_.try_lock())
        {
            temp.resize(data_add_list_.size());
            temp = data_add_list_;
            mutex_.unlock();
            // qDebug()<<"mutex_.try_lock() success"<<"\n";
        }
        else
        {
            qDebug()<<"mutex_.try_lock() failed"<<"\n";
        }
        return temp;
    }

    void getSrcListData(QVector<ChinnelData>& list)
    {
        if(mutex_.try_lock())
        {
            list.resize(data_src_list_.size());
            list = data_src_list_;
            mutex_.unlock();
        }
        else
        {
            qDebug()<<"get src list mutex_.try_lock() failed"<<"\n";
        }
    }

//    void saveDataToQueue()
//    {
//        safe_queue_.enqueue(data_src_list_);
//    }

    void closePort()
    {
        if(m_serialPort->isOpen())
        {
            m_serialPort->close();
            qDebug() << "串口已关闭";
            is_opened_ = false;
        }
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

public slots:
    void handleError(QSerialPort::SerialPortError error)
    {
        if(m_serialPort->isOpen())
        {
            //qDebug() << "Serial port error occurred:" << error;
            //closePort();
            //startReconnectTimer();
        }
    }

signals:
    //void dataReady(const QByteArray &data);
    //void portReconect();
    void SendData(QVector<ChinnelData> list);
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
        this->wait(100);
    }
    void run() override
    {
        while (!isInterruptionRequested() && is_runing_)
        {
            if(!is_opened_)
            {
                //emit portReconect();
                openPort();
                QThread::msleep(100); // 100ms
                continue;
            }
            if(is_pause_)
            {
                QThread::msleep(100); // 100ms
                continue;
            }
            if (m_serialPort->waitForReadyRead(50))//50ms
            {
                QByteArray data = m_serialPort->readAll();
                //emit dataReady(data);
                readData(data);
            }
        }
    }

private:
    QMutex mutex_;
    bool is_runing_ {false};
    bool is_pause_ {false};
    QSerialPort *m_serialPort {nullptr};
    QTimer m_reconnectTimer;
    bool is_opened_ {false};
    QString port_name_;
    QString str_data_;
    QVector<ChinnelData> data_src_list_;
    QVector<ChinnelData> data_add_list_;
//    SafeQueue<QVector<ChinnelData>> safe_queue_;
};

// 在你的应用程序中创建SerialPortManager实例并使用
#endif // SERIALPORTMANAGER_H
