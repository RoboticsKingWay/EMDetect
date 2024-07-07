#ifndef UNITDATA_H
#define UNITDATA_H

#include <QDebug>
#include <QVector>
#include "DetectSettings.h"

//#define DRAW_ADD_SIZE 20    // 实时图绘制增量20个数据
#define DRAW_MAX_SIZE 300   // 实时图绘制最多300个点数据
//#define SRC_MAX_SIZE 12000   // 最大存储源数据个数
#define CH_NUM 6
#define ZOOM_NUM 1.15

#define LENGTH_TO_POINT   40 // 1mm扫查长度对应点数，扫查平均速率
#define SENSOR_TO_WIDTH   40 // 一组通道的传感器扫查宽度
#define SCALE_SIZE         1 // 处理检测数据缩放比例
#define YELLOW_GRADIENT_SIZE  10 // 设置黄色10个梯度，缺陷梯度颜色变化，距离阈值线远缺陷越大，颜色越深

enum E_SERIAL_ACTION:int
{
    E_SERIAL_INVAL = -1,
    E_SERIAL_CONNECT = 0,
    E_SERIAL_CLOSE
};

enum E_ACTION_UI
{
    E_ACTION_INVAL = -1,
    E_ACTION_ST  = 0, // 开始采集
    E_ACTION_STOP,  // 停止采集
    E_ACTION_DEAL_DATA,// 数据处理
    E_ACTION_REVIEW, // 预览数据
    E_ACTION_SAVEAS, // 数据保存
    E_ACTION_CTRL_SERIAL // 串口操作
};

struct SerialParam
{
    QString port;
    int borate;
    int databit;
    int stopbit;
    int action;
};

struct ScanThreshold
{
    int ch_num;
    double upline;
    double downline;
};

struct ScanThreshold_Q
{
    int ch_num;
    double Q1;
    double Q2;
    double Q3;
    double Q4;
};


struct ChinnelMagData
{
    int data[CH_NUM];
};



struct ChinnelData
{
    ChinnelData() = default;
    ~ChinnelData() = default;
    ChinnelData(int index, ChinnelMagData data)
    {
        this->index = index;
        this->mag_data = data;
    }
    int index;
    ChinnelMagData mag_data;
};

struct ChinnelDataGroup
{
    QVector<ChinnelData> list;
};


struct ChinnelMagDrawData
{
    double data[CH_NUM];
    double Min()
    {
        double min = data[0];
        for(int i = 0 ; i < CH_NUM; i++)
        {
            min = std::min(min,data[i]);
        }
        return min;
    }
    double Max()
    {
        double max = data[0];
        for(int i = 0 ; i < CH_NUM; i++)
        {
            max = std::min(max,data[i]);
        }
        return max;
    }
};

struct ChinnelDrawData
{
    ChinnelDrawData() = default;
    ~ChinnelDrawData() = default;
    ChinnelDrawData(int index, ChinnelMagDrawData data)
    {
        this->index = index;
        this->mag_data = data;
    }
    int index;
    ChinnelMagDrawData mag_data;
};

Q_DECLARE_METATYPE(ChinnelMagData)
Q_DECLARE_METATYPE(QVector<ChinnelData>)
//Q_DECLARE_METATYPE(QVector<ChinnelData>&)
#endif // UNITDATA_H
