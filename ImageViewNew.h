#ifndef IMAGEVIEW_NEW_H
#define IMAGEVIEW_NEW_H


/********
 * 云图显示：将数据绘制成二维云图，当完成依次检测工作后，通过将检测数据进行自差分处理，得到差分后的数据，利用差分后的数据计算上下域值线，同时将横坐标的点数转换成距离，得到域值线后，根据差分后的数据在域值线之间的分布情况，再绘制成云图。以2通道为例，注意这里2通道代表数据为一组，若为6通道即CH1和CH4为一组，CH2和CH5为一组，以此类推。
第①步：图5为原始检测数据，将检测数据自差分处理后，分别计算CH1和CH2两个通道差分后数据的均值μ1、μ2和标准差σ1、σ2。
第②步：如图6所示，图6中的曲线为数据自差分后的数据曲线，图中的Q1、Q2、Q3、Q4分别对应域值线，其中Q1和Q2为CH1通道的上下域值线，Q3、Q4为CH2通道的上下域值线，域值线的计算是利用第①步中计算得到的每组数据的均值和标准差，例如CH1通道差分后的数据的上域值线为Q1=μ+A×σ1，下域值线Q1=μ-A×σ1，其中参数A的值要求可自行设定。
第③步：完成上述计算后再绘制云图，绘制的云图形式如图7所示，根据图6的信息对比，当数据处于Q1和Q2域值线以外时，或处于Q3和Q4域值线之间，云图对应部分为蓝色。如图6中黑色标注所示，若数据处于Q1和Q3之间或Q2和Q4域值线之间，但该段数据的峰值不在上述区域内，则该部分在云图中依然显示为蓝色；如图6中红色标注所示，仅当数据处于Q1和Q3之间或Q2和Q4域值线之间且该段数据的峰值也在上述区域内，则该部分在云图中显示为黄色，且颜色深浅与该段数据的正相关，即数值的绝对值越大颜色越深。
 * 根据需求说明：一般阈值线
 * ******/
#include <QWidget>
#include <QImage>
#include <QImageWriter>
#include <QGraphicsView>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include "UnitData.h"

class ImageViewNew : public QLabel
{
public:
    ImageViewNew(QLabel *parent = nullptr) : QLabel(parent)
    {
        parent_ = parent;
        bit_map_ = QImage(parent_->width(),parent_->height(),QImage::Format_ARGB32);
        double MY_IMG_BLUE[64]  =  { 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        double MY_IMG_GREEN[64] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5, 0.4375, 0.375, 0.3125, 0.25, 0.1875, 0.125, 0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        double MY_IMG_RED[64]   =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0625, 0.125, 0.1875, 0.25, 0.3125, 0.375, 0.4375, 0.5, 0.5625, 0.625, 0.6875, 0.75, 0.8125, 0.875, 0.9375, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.9375, 0.875, 0.8125, 0.75, 0.6875, 0.625, 0.5625, 0.5 };

        for(int i = 0; i < 64; i++)
        {
            yellowGradient_.append(QColor(MY_IMG_BLUE[i]*255, MY_IMG_GREEN[i]*255, MY_IMG_RED[i]*255));
        }

        for (const QColor &color : yellowGradient_)
        {
            qDebug() << "new image view: Yellow gradient color: RGB(" << color.red() << color.green() << color.blue() << ")";
        }
        draw_source_data_.clear();
    }

    virtual ~ImageViewNew()
    {

    }

    void setGradientToDistance(double max, double min)
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
    void drawImage(std::vector<std::vector<double>>& distance_tab,bool is_update = false)
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
        picContour(distance_tab,is_update);
    }
    void updateImage(int width,int height)
    {
        drawImage(draw_source_data_,true);
        //       bit_map_ = bit_map_.scaled(width, height, Qt::KeepAspectRatio);
    }

    void picContour(std::vector<std::vector<double>>& distance_tab,bool is_update = false)
    {
        width_ = parent_->width();
        height_ = parent_->height();
        bit_map_ = QImage(width_, height_, QImage::Format_ARGB32);
        bit_map_.fill(Qt::blue); // Fill the bitmap with blue color

        if(distance_tab.size() <= 0 || distance_tab[0].size() <= 0)
        {
            return;
        }
        if(!is_update)
        {
            draw_source_data_.clear();
            draw_source_data_ = distance_tab;
        }
        QPainter painter(&bit_map_);
//        QBrush brush (Qt::black);
//        QPen blackPen (brush, 1);
//        QFont font =  QFont("Timers New Roman", 5);

        //Font font = new Font("宋体", 7, FontStyle.Regular);
        double x0 = 0.025;
        double y0 = 0.025;
        double W = 0.95;
        double H = 0.90;
        float x = (float)(this->width_ * x0);
        float y = (float)(this->height_ * y0);
        float width = (float)(this->width_ * W);
        float height = (float)(this->height_ * H);
        //Contourf(g, 2 * 40, (original_num - 1) * 5, FreadData, (original_num - 1) * 5, 2 * 40);
        //Contourf(g, 2, original_num, FreadData, original_num, 2);

        Contourf(2 * 40, draw_source_data_[0].size(), draw_source_data_[0].size(), 2 * 40,painter);

        QPen pen = QColor(0,0,0);
        pen.setWidth(1);
        painter.setPen(pen);
//        g.DrawRectangle(blackPen, x, y, width, height);
        float x1, x2, y1, y2;
        //画X方向刻度
        for (int k = 0; k <= 10; k++)
        {
            x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
            y1 = (float)(this->height_ * y0);
            x2 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
            y2 = (float)(this->height_ * (y0 + 0.02));
            painter.drawLine(x1, y1, x2, y2);


            x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
            y1 = (float)(this->height_ * (x0 + H));
            x2 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
            y2 = (float)(this->height_ * (x0 + H - 0.02));
            painter.drawLine(x1, y1, x2, y2);


            x1 = (float)(this->width_ * x0 + k * this->width_ * W / 10);
            y1 = (float)(this->height_ * (y0 + H + 0.02)) - 3;
            painter.drawText(x1, y1, QString::number(k * scan_length_ / 10));
        }
        //画Y方向刻度
        int b;
        for (int k = 1; k <= 2; k++)
        {
            b = k;
            x1 = (float)(this->width_ * x0);
            y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
            x2 = (float)(this->width_ * (x0 + 0.005));
            y2 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
            painter.drawLine(x1, y1, x2, y2);

            x1 = (float)(this->width_ * (x0 + W));
            y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
            x2 = (float)(this->width_ * (x0 + W - 0.005));
            y2 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
            painter.drawLine(x1, y1, x2, y2);

            x1 = (float)(this->width_ * (x0 - 0.02)) - 7;
            y1 = (float)(this->height_ * (1 - (y0 + k * H / 2) - 0.05));
            //g.DrawString((k * widthOfPiece / 5).ToString("0"), font, brush, x1, y1);
            painter.drawText(x1, y1,QString("CH")+QString::number(k));
        }
        QImageWriter imageWriter("saved_image.png");
        imageWriter.setFormat("png");  // 设置图像格式

        // 写入图像
        bool success = imageWriter.write(bit_map_);

        // 检查是否有错误
        if (!success) {
            qDebug() << "Failed to save image:" << imageWriter.errorString();
        } else {
            qDebug() << "Image saved successfully!";
        }
    }
    void Contourf(long intM, long intN, double Xmax, double Ymax,QPainter& painter)
    {
        //  Contourf(g, 2, original_num, FreadData, original_num, 2);

        int p;
        double picDX,picDY;
        double x0 = 0.025;
        double y0 = 0.025;
        double W = 0.95;
        double H = 0.90;
        double CurrentX = 0;
        double CurrentY = 0;
        double DDX = 0;
        double DDY = 0;

        //画彩图
        picDX = W / Xmax;
        picDY = H / Ymax;
        DDX = (bit_map_.width() * picDX);
        DDY = (bit_map_.height() * picDY);
        if(DDX < 1)
        {
            DDX = 1;
        }
        if(DDY < 1)
        {
            DDY = 1;
        }
        QBrush brush;
        for (long i = 0; i < intM; i++)
        {
            for (long j = 0; j < intN; j++)
            {
                CurrentX = (double)(bit_map_.width() * (x0 + j * picDX));
                // CurrentY = (float)(this->height_ * (1 - (y0 + 0.0625 + i * picDY)));
                CurrentY = (double)(bit_map_.height() * (0.925 - i * picDY));
                DDX = (bit_map_.width() * picDX);
                DDY = (bit_map_.height() * picDY);

                p = (int)((draw_source_data_[i][j] - min_data_) * 63 / (max_data_ - min_data_));
                if (j > intN - 80)//彩图去右边图像。    //DynamicpicContour（）的代码是j>intN-50   intN是数据点数
                {
                    p = 0;
                }
                if(p < 0)
                {
                    qDebug()<<" color index out of range.";
                    p = 0;
                }
                if(DDX < 1)
                {
                    DDX = 1;
                }
                QBrush brush = QBrush(yellowGradient_[p]);
                painter.fillRect(CurrentX, CurrentY, DDX, DDY,brush);
            }
        }
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(parent_);
        QImage image("saved_image.png");
        painter.drawImage(0, 0, image); // Draw the bitmap at position (0, 0)
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
    std::vector<std::vector<double>> draw_source_data_;    // 差分计算得到的结果数据,距离数据
    //    ScanThreshold_Q array_thresh_[CH_NUM/2];            // 阈值线
};

#endif // IMAGEVIEWNEW_H
