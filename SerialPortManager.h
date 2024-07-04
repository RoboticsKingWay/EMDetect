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
        is_pause_ = true;
        is_runing_ = false;
        m_serialPort = nullptr;
    }

    ~SerialPortManager()
    {
        //stopReconnectTimer();
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
            if(is_opened_ && is_pause_ == false)
            {
                QMessageBox::critical(nullptr, "Error", "serial is opened,please stop collect action first!");
                return false;
            }
            closePort();
            QThread::sleep(1);
            m_serialPort = nullptr;
            delete m_serialPort;
        }
        m_serialPort = new QSerialPort(serial_param_.port, this);
        port_name_ = portName;
        // 配置串口参数
//        m_serialPort->setBaudRate(QSerialPort::Baud115200);
//        m_serialPort->setDataBits(QSerialPort::Data8);
//        m_serialPort->setParity(QSerialPort::NoParity);
//        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setBaudRate(serial_param_.borate);
        m_serialPort->setDataBits((QSerialPort::DataBits)serial_param_.databit);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits((QSerialPort::StopBits)serial_param_.stopbit);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

        qDebug()<<"buf_size_1="<<m_serialPort->readBufferSize()<<"\r\n";
        m_serialPort->setReadBufferSize(128);
        qDebug()<<"buf_size_2="<<m_serialPort->readBufferSize()<<"\r\n";
        // 连接信号和槽
        //connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortManager::readData);
        connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortManager::handleError,Qt::QueuedConnection);
        //connect(&m_reconnectTimer, &QTimer::timeout, this, &SerialPortManager::reconnect);

        // 尝试打开串口
        openPort();
//        qDebug()<<"main thread:"<<QThread::currentThreadId();
        if(!is_runing_)
        {
            startThread();
        }

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
            qDebug() << "port:"<<serial_param_.port<<"opened.";
            is_opened_ = true;
        }
        else
        {
            qDebug() << "port opened failed,retry...";
            is_opened_ = false;
        }
    }

    void readData(const QByteArray &data)
    {
        // 读取串口数据的槽函数
        //qDebug()<<"son thread:"<<QThread::currentThreadId();
        //QString str_debug = QString::fromUtf8(data);
        //qDebug()<<"\n\nstr_debug:"<<str_debug<<"\n\n";
        if(m_serialPort->isOpen())
        {
//            static int count_index = 0;
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
                    if(list.size() == CH_NUM)
                    {
                        ChinnelMagData ch_data;
                        ch_data.data[0] = list.at(0).toInt()/SCALE_SIZE;
                        ch_data.data[1] = list.at(1).toInt()/SCALE_SIZE;
                        ch_data.data[2] = list.at(2).toInt()/SCALE_SIZE;
                        ch_data.data[3] = list.at(3).toInt()/SCALE_SIZE;
                        ch_data.data[4] = list.at(4).toInt()/SCALE_SIZE;
                        ch_data.data[5] = list.at(5).toInt()/SCALE_SIZE;

//                        QDateTime currentTime = QDateTime::currentDateTime();
//                        qDebug()<<currentTime<<"-ch_data:"<<ch_data.ch1<<" "<<ch_data.ch2<<" "<<ch_data.ch3<<" "<<ch_data.ch4<<" "<<ch_data.ch5<<" "<<ch_data.ch6;
//                        lastPosition = match.capturedEnd(); // 更新最后一个字符串 A 出现的位置
                        data_src_list_.push_back(ChinnelData(++count_index_,ch_data));
                    }
                    else
                    {
                        qDebug()<<"ch_data size != "<<CH_NUM<<" size = "<<list.size();
                        qDebug()<<"err_str:"<<stringA;
                    }
                    lastPosition = match.capturedEnd(); // 更新最后一个字符串 A 出现的位置
                    if(data_src_list_.size() >= SRC_MAX_SIZE)
                    {
                        qDebug()<<"size >= "<<SRC_MAX_SIZE;
                        emit SendData(data_src_list_);
//                        count_index_ = 0;
                        data_src_list_.clear();
                    }
                    if(count_index_ % DRAW_ADD_SIZE == 0)
                    {
                        setDrawData(count_index_);
                    }
                }
            }
            last_str = last_str.mid(lastPosition);
        }
    }
    void setDrawData(int count)
    {
        if(mutex_.try_lock())
        {
            if(data_src_list_.size() >= DRAW_ADD_SIZE && data_src_list_.size()%DRAW_ADD_SIZE == 0)
            {
                int start = (count % SRC_MAX_SIZE) - DRAW_ADD_SIZE;
                for(int i = 0; i < DRAW_ADD_SIZE; i++)
                {
                    //qDebug()<<"i="<<i<<" count="<<count<<"\n";
                    ChinnelData data;
                    data.index = data_src_list_[start + i].index;
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
        else
        {
            qDebug()<<"set draw data mutex_.try_lock() failed"<<"\n";
        }
    }

    QVector<ChinnelData> getDrawData()
    {
        QVector<ChinnelData> temp;
        if(mutex_.tryLock(100))
        {
            temp.resize(data_add_list_.size());
            temp = data_add_list_;
            data_add_list_.clear();
            mutex_.unlock();
        }
        else
        {
            qDebug()<<"get draw data mutex_.try_lock() failed"<<"\n";
        }
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

    void clearSrcListData()
    {
        //if(mutex_.tryLock(100))
        {
            QVector<ChinnelData> list;
            data_src_list_.clear();
            data_add_list_.clear();
            data_src_list_ = list;
            data_add_list_ = list;
            count_index_ = 0;
            qDebug()<<"clear serial src data"<<"\n";
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
        connectSerial(serial_param_.port);
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
        this->wait(1000);
    }
    void run() override
    {
        while (!isInterruptionRequested() && is_runing_)
        {
            if(is_pause_)
            {
                QThread::msleep(100); // 100ms
                continue;
            }
            if(!is_opened_)
            {
                //emit portReconect();
                openPort();
                QThread::msleep(100); // 100ms
                continue;
            }
            if (m_serialPort->waitForReadyRead(1000))//1000ms
            {
                QByteArray data = m_serialPort->readAll();
                if(QString(data) != "")
                {
                    readData(data);
                    continue;
                }
                else
                {
                    //QThread::msleep(10);
                    qDebug()<<"recv:empty\r\n";
                }
            }
        }
    }

private:
    QMutex mutex_;
    long long count_index_ {0};
    bool is_runing_ {false};
    bool is_pause_ {false};
    QSerialPort *m_serialPort {nullptr};
    QTimer m_reconnectTimer;
    bool is_opened_ {false};
    QString port_name_;
    SerialParam serial_param_;
    QString str_data_;
    QVector<ChinnelData> data_src_list_;
    QVector<ChinnelData> data_add_list_;
//    SafeQueue<QVector<ChinnelData>> safe_queue_;
};

// 在你的应用程序中创建SerialPortManager实例并使用
#endif // SERIALPORTMANAGER_H
