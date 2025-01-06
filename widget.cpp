#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <cmath>
#include <cstdint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , freqEdit(nullptr)
    , ampEdit(nullptr)
    , serialPort(new QSerialPort(this))
    , currentChannel(1) // 初始化当前通道为1
    , isPortOpen(false) // 新增变量来跟踪串口是否打开
{
    ui->setupUi(this);

    freqEdit = ui -> freqEdit;
    ampEdit = ui -> ampEdit;
    freqEdit_2 = ui -> freqEdit_2;
    ampEdit_2 = ui -> ampEdit_2;

    // 设置默认频率和幅值
    freqEdit->setText("1000.0"); // 默认频率1000Hz
    ampEdit->setText("2.0");      // 默认幅值2（假设0-65范围内，表示0-6.5v）
    freqEdit_2->setText("1000.0");
    ampEdit_2->setText("2.0");

    // 列出所有可用的串口
    QStringList serialNamePort;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        serialNamePort << info.portName();
    }

    ui->serialCb->addItems(serialNamePort);

    // 配置串口参数
    serialPort->setBaudRate(QSerialPort::Baud9600); // 设置波特率为9600
    serialPort->setDataBits(QSerialPort::Data8);    // 设置数据位为8
    serialPort->setStopBits(QSerialPort::OneStop);  // 设置停止位为1

    // 初始化按钮文本为“打开串口”
    ui->openBt->setText("打开串口");
    connect(ui->openBt, &QPushButton::clicked, this, &Widget::toggleSerialPort);

    // 连接读取数据的信号到槽函数
    connect(serialPort, &QSerialPort::readyRead, this, &Widget::readData);

    // 连接复选框状态变化的信号到槽函数
    connect(ui->checkCH1, &QCheckBox::stateChanged, this, &Widget::on_checkCH1_StateChanged);
    connect(ui->checkCH2, &QCheckBox::stateChanged, this, &Widget::on_checkCH2_StateChanged);

    // 初始化复选框状态
    ui->checkCH1->setChecked(true); // 默认选中通道1
    ui->checkCH2->setChecked(false);
}

Widget::~Widget()
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
        delete serialPort;
        serialPort = nullptr;
    }

    delete ui;
}

void Widget::toggleSerialPort()
{
    QString selectedPortName = ui->serialCb->currentText(); // 读取当前选中的串口名称

    if (isPortOpen) {
        // 如果串口已打开，则关闭它
        serialPort->close();

        // 检查串口是否确实已关闭
        if (!serialPort->isOpen()) {
            ui->openBt->setText("打开串口"); // 更改按钮文本为“打开串口”
            isPortOpen = false;
            QMessageBox::information(this, "提示", "串口已关闭");
        } else {
            QMessageBox::critical(this, "提示", "关闭串口失败，请检查是否有其他程序占用了该串口。");
            // 一种可能是串口在物理上被断开，但驱动程序仍然认为它是打开的。
        }
    } else {
        // 如果串口未打开，并且下拉框中有选中的串口
        if (!selectedPortName.isEmpty()) {
            serialPort->setPortName(selectedPortName); // 设置串口名称为用户选中的名称

            // 尝试打开串口
            if (serialPort->open(QIODevice::ReadWrite)) {
                ui->openBt->setText("关闭串口"); // 更改按钮文本为“关闭串口”
                isPortOpen = true;
                QMessageBox::information(this, "提示", "成功打开串口: " + selectedPortName);
            } else {
                QMessageBox::critical(this, "提示", "打开串口失败: " + serialPort->errorString());
            }
        } else {
            QMessageBox::warning(this, "警告", "请先选择一个串口！");
        }
    }
}


void Widget::readData()
{
    QByteArray data = serialPort->readAll();
    qDebug() << "Received data:" << data.toHex();
    // TODO: Process received data as needed
}

QByteArray Widget::generateSineWaveData(uint32_t freq, uint8_t channel)
{
    QByteArray data;
    // 确保低字节在前
    data.append(static_cast<char>(freq & 0xFF));       // 低字节
    data.append(static_cast<char>((freq >> 8) & 0xFF)); // 第二低字节
    data.append(static_cast<char>((freq >> 16) & 0xFF)); // 第二高字节
    data.append(static_cast<char>((freq >> 24) & 0xFF)); // 高字节
    data.append(static_cast<char>(channel));   // 通道
    return data;
}

QByteArray Widget::generateAmplitudeData(uint8_t amplitude, uint8_t channel)
{
    QByteArray data;
    data.append(static_cast<char>(amplitude)); // 幅度
    data.append(static_cast<char>(channel));   // 通道
    return data;
}

QByteArray Widget::constructCommand(uint8_t cmd, const QByteArray &data, int length)
{
    QByteArray command;
    command.append(char(0x55)); // 命令头
    command.append(char(0xAA));

    command.append(char(length));

    command.append(char(cmd)); // 命令字
    command.append(data); // 数据域（频率、幅度、通道）

    command.append(char(0xAA)); // 命令尾
    command.append(char(0x55));

    return command;
}


void Widget::on_checkCH1_StateChanged(int state)
{
    if (state == Qt::Checked) {
        currentChannel = 1; // 选择通道1
        ui->checkCH2->setChecked(false); // 自动取消通道2
        sendChannelCommand(1); // 发送切换通道命令
    }
}

void Widget::on_checkCH2_StateChanged(int state)
{
    if (state == Qt::Checked) {
        currentChannel = 2; // 选择通道2
        ui->checkCH1->setChecked(false); // 自动取消通道1
        sendChannelCommand(2); // 发送切换通道命令
    }
}

void Widget::sendChannelCommand(uint8_t channel)
{
    QByteArray channelData;
    channelData.append(static_cast<char>(channel)); // 添加通道数据

    // 构建完整的命令，包括头、长度、命令字、数据、尾
    QByteArray channelCommand = constructCommand(0x19, channelData, 3); // 长度是3（固定部分）+ 数据字节数

    // 打印出要发送的命令，以便调试
    qDebug() << "Sending channel command:" << channelCommand.toHex();

    // 发送命令到串口
    serialPort->write(channelCommand);
}

void Widget::on_sendampBt_clicked()
{
    // 检查串口是否连接
    if (!serialPort->isOpen()) {
        QMessageBox::critical(this, tr("错误"), tr("串口未连接，请检查连接并重新尝试."));
        return;
    }

    // 检查CH1是否已选中
    if (!ui->checkCH1->isChecked()) {
        QMessageBox::warning(this, tr("错误"), tr("请先选择CH1再进行发送"));
        return;
    }

    bool ampOk;
    QString ampStr = ui->ampEdit->text().trimmed(); // 移除幅度字符串的任何前导或尾随空格
    double ampDouble = ampStr.toDouble(&ampOk); // 将幅度字符串转换为双精度浮点数

    // 检查幅度转换是否成功，并且幅度值在0-6.5V范围内
    if (!ampOk || ampDouble < 0 || ampDouble > 6.5) {
        QMessageBox::warning(this, tr("失败"), tr("请输入合适的幅值（0-6.5V）."));
        return;
    }

    // 根据0-6.5V到0-65的映射关系计算幅度整数值
    int mappedAmp = static_cast<int>(ampDouble * (65 / 6.5));

    // 确保映射后的幅度整数值在0-65之间（理论上不需要，但保留此检查以符合原始代码风格）
    if (mappedAmp < 0 || mappedAmp > 65) {
        QMessageBox::critical(this, tr("内部错误"), tr("幅度映射出错，请检查代码."));
        return;
    }

    uint8_t amp = static_cast<uint8_t>(mappedAmp);
    uint8_t channel = currentChannel; // 使用当前通道

    // 构建并发送幅值命令
    QByteArray ampData = generateAmplitudeData(amp, channel); // 只包含幅度和通道
    QByteArray ampCommand = constructCommand(0x22, ampData, 4); // 长度字为0x04（4字节）
    qDebug() << "Sending amplitude command:" << ampCommand.toHex();
    serialPort->write(ampCommand);
}


void Widget::on_sendfreqBt_clicked()
{
    // 检查串口是否连接
    if (!serialPort->isOpen()) {
        QMessageBox::critical(this, tr("错误"), tr("串口未连接，请检查连接并重新尝试."));
        return;
    }

    // 检查CH1是否已选中
    if (!ui->checkCH1->isChecked()) {
        QMessageBox::warning(this, tr("错误"), tr("请先选择CH1再进行发送"));
        return;
    }

    bool freqOk;
    QString freqStr = ui->freqEdit->text().trimmed(); // 移除任何前导或尾随空格
    double freqDouble = freqStr.toDouble(&freqOk); // 尝试将频率字符串转换为双精度浮点数

    // 检查频率转换是否成功，并且频率值在合理范围内
    if (!freqOk || freqDouble > 16777215) {
        QMessageBox::warning(this, tr("失败"), tr("请输入合适的频率."));
        return;
    }

    // 将双精度浮点数频率转换为无符号整数
    uint32_t freq = static_cast<uint32_t>(freqDouble);

    uint8_t channel = currentChannel; // 使用当前通道

    // 构建并发送频率命令
    QByteArray freqData = generateSineWaveData(freq, channel); // 只包含频率和通道
    QByteArray freqCommand = constructCommand(0x23, freqData, 7); // 长度字为0x07（7字节）
    qDebug() << "Sending frequency command:" << freqCommand.toHex();
    serialPort->write(freqCommand);

}


void Widget::on_sendampBt_2_clicked()
{
    // 检查串口是否连接
    if (!serialPort->isOpen()) {
        QMessageBox::critical(this, tr("错误"), tr("串口未连接，请检查连接并重新尝试."));
        return;
    }

    // 检查CH2是否已选中
    if (!ui->checkCH2->isChecked()) {
        QMessageBox::warning(this, tr("错误"), tr("请先选择CH2再进行发送"));
        return;
    }

    bool ampOk;
    QString ampStr = ui->ampEdit_2->text().trimmed(); // 使用 ampEdit_2 获取幅度字符串
    double ampDouble = ampStr.toDouble(&ampOk); // 将幅度字符串转换为双精度浮点数

    // 检查幅度转换是否成功，并且幅度值在0-6.5V范围内
    if (!ampOk || ampDouble < 0 || ampDouble > 6.5) {
        QMessageBox::warning(this, tr("失败"), tr("请输入合适的幅值（0-6.5V）."));
        return;
    }

    // 根据0-6.5V到0-65的映射关系计算幅度整数值
    int mappedAmp = static_cast<int>(ampDouble * (65 / 6.5));

    // 映射后的幅度整数值应该在0-65之间，但由于之前的计算保证了这个范围，这个检查可以省略
    // 但为了保持一致性，我们还是保留这个检查（尽管它是多余的）
    if (mappedAmp < 0 || mappedAmp > 65) {
        QMessageBox::critical(this, tr("内部错误"), tr("幅度映射出错，请检查代码."));
        return;
    }

    uint8_t amp = static_cast<uint8_t>(mappedAmp);
    uint8_t channel = currentChannel; // 使用当前通道

    // 构建并发送幅值命令
    QByteArray ampData = generateAmplitudeData(amp, channel); // 只包含幅度和通道
    QByteArray ampCommand = constructCommand(0x22, ampData, 4); // 长度字为0x04（4字节）
    qDebug() << "Sending amplitude command (Button 2):" << ampCommand.toHex();
    serialPort->write(ampCommand);
}

void Widget::on_sendfreqBt_2_clicked()
{
    // 检查串口是否连接
    if (!serialPort->isOpen()) {
        QMessageBox::critical(this, tr("错误"), tr("串口未连接，请检查连接并重新尝试."));
        return;
    }

    // 检查CH2是否已选中
    if (!ui->checkCH2->isChecked()) {
        QMessageBox::warning(this, tr("错误"), tr("请先选择CH2再进行发送"));
        return;
    }

    bool freqOk;
    QString freqStr = ui->freqEdit_2->text().trimmed(); // 使用 freqEdit_2 获取频率字符串
    double freqDouble = freqStr.toDouble(&freqOk); // 尝试将频率字符串转换为双精度浮点数

    // 检查频率转换是否成功，并且频率值在合理范围内（这里假设最大频率为16777215，根据实际情况调整）
    if (!freqOk || freqDouble > 16777215) {
        QMessageBox::warning(this, tr("失败"), tr("请输入合适的频率."));
        return;
    }

    // 将双精度浮点数频率转换为无符号整数
    uint32_t freq = static_cast<uint32_t>(freqDouble);

    uint8_t channel = currentChannel; // 使用当前通道

    // 构建并发送频率命令
    QByteArray freqData = generateSineWaveData(freq, channel); // 只包含频率和通道
    QByteArray freqCommand = constructCommand(0x23, freqData, 7); // 长度字为0x07（7字节），根据实际情况调整长度
    qDebug() << "Sending frequency command (Button 2):" << freqCommand.toHex();
    serialPort->write(freqCommand);
}

