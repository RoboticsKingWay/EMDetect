#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

/********
 * 云图显示：将数据绘制成二维云图，当完成依次检测工作后，通过将检测数据进行自差分处理，得到差分后的数据，利用差分后的数据计算上下域值线，同时将横坐标的点数转换成距离，得到域值线后，根据差分后的数据在域值线之间的分布情况，再绘制成云图。以2通道为例，注意这里2通道代表数据为一组，若为6通道即CH1和CH4为一组，CH2和CH5为一组，以此类推。
第①步：图5为原始检测数据，将检测数据自差分处理后，分别计算CH1和CH2两个通道差分后数据的均值μ1、μ2和标准差σ1、σ2。
第②步：如图6所示，图6中的曲线为数据自差分后的数据曲线，图中的Q1、Q2、Q3、Q4分别对应域值线，其中Q1和Q2为CH1通道的上下域值线，Q3、Q4为CH2通道的上下域值线，域值线的计算是利用第①步中计算得到的每组数据的均值和标准差，例如CH1通道差分后的数据的上域值线为Q1=μ+A×σ1，下域值线Q1=μ-A×σ1，其中参数A的值要求可自行设定。
第③步：完成上述计算后再绘制云图，绘制的云图形式如图7所示，根据图6的信息对比，当数据处于Q1和Q2域值线以外时，或处于Q3和Q4域值线之间，云图对应部分为蓝色。如图6中黑色标注所示，若数据处于Q1和Q3之间或Q2和Q4域值线之间，但该段数据的峰值不在上述区域内，则该部分在云图中依然显示为蓝色；如图6中红色标注所示，仅当数据处于Q1和Q3之间或Q2和Q4域值线之间且该段数据的峰值也在上述区域内，则该部分在云图中显示为黄色，且颜色深浅与该段数据的正相关，即数值的绝对值越大颜色越深。
 * 根据需求说明：一般阈值线
 * ******/
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include "UnitData.h"

class ImageView : public QLabel
{
public:
    ImageView(QLabel *parent = nullptr) : QLabel(parent)
    {
        parent_ = parent;
        bit_map_ = QImage(parent_->width(),parent_->height(),QImage::Format_ARGB32);
//        yellowGradient_.resize(YELLOW_GRADIENT_SIZE);
//        generateYellowTone();
        // 浅黄色到深黄色的RGB数值列表
        yellowGradient_.append(QColor(255, 255, 200)); // 浅黄
        yellowGradient_.append(QColor(255, 255, 190));
        yellowGradient_.append(QColor(255, 255, 180));

        yellowGradient_.append(QColor(255, 255, 150)); // 中黄
        yellowGradient_.append(QColor(255, 255, 140));
        yellowGradient_.append(QColor(255, 255, 130));

        yellowGradient_.append(QColor(255, 255, 100));  // 深黄
        yellowGradient_.append(QColor(255, 255, 80));
        yellowGradient_.append(QColor(255, 255, 60));

        yellowGradient_.append(QColor(255, 200, 100));  // 暗黄
        yellowGradient_.append(QColor(255, 180, 80));
        yellowGradient_.append(QColor(255, 160, 60));

        for (const QColor &color : yellowGradient_)
        {
            qDebug() << "Yellow gradient color: RGB(" << color.red() << color.green() << color.blue() << ")";
        }
        draw_source_data_.clear();
    }

    virtual ~ImageView()
    {

    }

    void setGradientToDistance(int max, int min)
    {
        max_data_ = max;
        min_data_ = min;
        space_distance_ = std::abs(max - min)/yellowGradient_.size();
        qDebug()<<"max_data:"<<max_data_<<"  min_data:"<<min_data_<<"  yellowGradient-space_distance:"<<space_distance_<<"\n";
    }

    void setScanLength(double len)
    {
        scan_length_ = len;
    }

    // 输入一个可变长度的二维数组，表示差分数据的距离，缺陷不在范围内设置距离为0，距离越大颜色越深，最大距离到最小距离对颜色梯度比
    void drawImage(std::vector<std::vector<int>>& distance_tab,bool is_update = false)
    {
        width_ = parent_->width();
        height_ = parent_->height();

        real_imgage_height_ = height_ - 15;
        qDebug()<<"image_w:"<<width_<<" image_h:"<<height_<<" real_imgage_height_:"<<real_imgage_height_<<"\n";
        setMinimumSize(QSize(width_,height_));

        bit_map_ = QImage(width_, height_, QImage::Format_ARGB32);
        bit_map_.fill(Qt::blue); // Fill the bitmap with blue color

        if(distance_tab.size() <= 0)
        {
            return;
        }
        if(!is_update)
        {
            draw_source_data_.clear();
            draw_source_data_ = distance_tab;
        }
        QPainter painter(&bit_map_);
        // image底部 real_imgage_height_ 位置用来绘制刻度
        QPen pen = QColor(255,0,0);
        pen.setWidth(2);
        painter.setPen(pen);
        drawSpliteLine(painter);
        drawDetectionArea(painter,draw_source_data_);
        painter.fillRect(0, real_imgage_height_, width_, 15, Qt::white); //
        drawScale(painter);
        drawText(painter);
    }
    void updateImage(int width,int height)
    {
       drawImage(draw_source_data_,true);
//       bit_map_ = bit_map_.scaled(width, height, Qt::KeepAspectRatio);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        painter.drawImage(0, 0, bit_map_); // Draw the bitmap at position (0, 0)
    }
private:
    // 黄色调色板
    void generateYellowTone()
    {
        // 定义黄色梯度值，从浅黄到深黄
        int red = 255;   // 红色分量最大值
        int green = 255; // 绿色分量最大值
        int blue = 200;       // 蓝色分量

        for (int i = 0; i < blue/YELLOW_GRADIENT_SIZE; ++i)
        {
            yellowGradient_.append(QColor(red, green, (blue - i*YELLOW_GRADIENT_SIZE)));
        }
        red = 255; green = 200; blue = 100;
        for (int i = 0; i < blue/YELLOW_GRADIENT_SIZE; ++i)
        {
            yellowGradient_.append(QColor(red, green, (blue - i*YELLOW_GRADIENT_SIZE)));
        }
        for (const QColor &color : yellowGradient_)
        {
            qDebug() << "Yellow gradient color:" << color;
        }
    }

    inline QColor getGenerateYellowTone(int distance)
    {
        int index = std::abs(distance - min_data_)/space_distance_;
        if(index >= 0 && index < yellowGradient_.size())
        {
            return yellowGradient_[index];
        }
        else
        {
            return QColor(Qt::blue);
        }
    }

    // 绘制缺陷区域
    // 点数还是长度对应像素宽度，哪个更合理？
    // 长度对应像素宽度
    // LENGTH_TO_POINT
    void drawDetectionArea(QPainter& painter,std::vector<std::vector<int>>& distance_tab)
    {
#if 0 // for test
        for (int x = 0; x < width_; ++x)
        {
            QColor color = yellowGradient_[(x/30)%yellowGradient_.size()];
            painter.setPen(color);
            painter.drawLine(x, 0, x, real_imgage_height_);
        }
#else
        int point_to_len   = 0;
        int pixel_to_point = 0;
        if(distance_tab.size())
        {
            point_to_len   = distance_tab[0].size()/scan_length_; // 1mm 对应点数个数
            pixel_to_point = distance_tab[0].size()/width_;       // 1个像素对应点数
        }

        if(point_to_len == 0 || pixel_to_point == 0)
        {
            return;
        }

        int h = real_imgage_height_/distance_tab.size();
        // 从CH1,CH2,CH3 开始绘制，共3组通道
        for(int i = 0; i < distance_tab.size()/2; i++)
        {

            int y = i * real_imgage_height_/distance_tab.size()*2;
            qDebug()<<"image_he_y:"<<y;
            // 每个通道绘制的点数对应像素
            for(int j = 0; j < distance_tab[i].size();j++)
            {
                QBrush brush = getGenerateYellowTone(distance_tab[i][j]);
                int x = j/pixel_to_point;
                painter.fillRect(x, y+h, 1, 3, brush); // 画2个像素宽度，2个像素的高度
            }
        }
#endif
    }

    void drawScale(QPainter& painter)
    {

        QFont font("Arial", 5);
        painter.setFont(font);
        painter.setPen(QPen(Qt::black, 1, Qt::DashLine));

        int numTicks = 10; // 刻度数量
        int tickSpacing = width_ / (numTicks - 1); // 计算刻度间隔

        for (int i = 1; i < numTicks; ++i)
        {
            int x1 = i * tickSpacing;
            int x2 = x1;
            int y1 = real_imgage_height_ + 2;
            int y2 = real_imgage_height_;
            painter.drawLine(x1, y1, x2, y2); // 水平刻度线
        }
    }

    void drawText(QPainter& painter)
    {
        int numTicks = 10; // 刻度数量
        int tickSpacing = width_ / numTicks; // 计算刻度间隔
        int y = real_imgage_height_ + 8;
        painter.drawText(3, y, QString::number(0));
        for (int i = 1; i <= numTicks; ++i)
        {
            // 计算标签位置
//            int textWidth = painter.fontMetrics().width(QString::number(i));
//            int x = i * tickSpacing - textWidth / 2;
            int x = i * tickSpacing - 5;
            // 绘制标签
            painter.drawText(x, y, QString::number(i * scan_length_/numTicks));
        }
    }

    void drawSpliteLine(QPainter& painter)
    {
        int h1 = (real_imgage_height_)/3;
        painter.drawLine(0,h1,width_,h1);
        int h2 = 2*(real_imgage_height_)/3;
        painter.drawLine(0,h2,width_,h2);
        int h3 = real_imgage_height_;
        painter.drawLine(0,h3,width_,h3);
    }

private:
    QImage bit_map_;
    int width_;
    int height_;
    int real_imgage_height_;
    double scan_length_{20}; // mm
    int count_num_; // 点数
    QLabel *parent_;
    QVector<QColor> yellowGradient_;
    double max_data_ {0};
    double min_data_ {0};
    double space_distance_ {0};
    std::vector<std::vector<int>> draw_source_data_;    // 差分计算得到的结果数据,距离数据
//    ScanThreshold_Q array_thresh_[CH_NUM/2];            // 阈值线
};
#endif // IMAGEVIEW_H
