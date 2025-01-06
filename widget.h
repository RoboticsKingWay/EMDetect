#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QLineEdit>
#include <QSerialPortInfo>
#include <cmath>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void toggleSerialPort();

    void readData();

    void sendChannelCommand(uint8_t channel);


    void on_checkCH1_StateChanged(int state);

    void on_checkCH2_StateChanged(int state);

    void on_sendampBt_clicked();

    void on_sendfreqBt_clicked();

    void on_sendfreqBt_2_clicked();

    void on_sendampBt_2_clicked();

private:
    Ui::Widget *ui;

    QSerialPort * serialPort;
    QLineEdit *freqEdit;
    QLineEdit *ampEdit;
    QLineEdit *freqEdit_2;
    QLineEdit *ampEdit_2;

    QByteArray generateSineWaveData(uint32_t freq, uint8_t channel);
    QByteArray constructCommand(uint8_t cmd, const QByteArray &data, int length);
    QByteArray generateAmplitudeData(uint8_t amplitude, uint8_t channel);

    int currentChannel;
    int isPortOpen;



};
#endif // WIDGET_H
