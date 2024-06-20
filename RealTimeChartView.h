#ifndef REALTIMECHARTVIEW_H
#define REALTIMECHARTVIEW_H

#include "UnitData.h"
#include "ZoomableChartView.h"

static int count_points_ = 0;
class RealTimeChartView : public BaseView
{
    Q_OBJECT
public:
    explicit RealTimeChartView(QWidget *parent = nullptr)
        : BaseView(parent)
    {

    }
    virtual ~RealTimeChartView()
    {

    }
    virtual void createChartView() override
    {
        chart_ = new QChart();
        chart_->setTitle(QStringLiteral("实时曲线"));
        //创建图表
        chart_view_ = new ZoomableChartView(chart_);
        chart_view_->setChart(chart_);//将chart添加到chartview中
        // 鼠标滚轮缩放
        chart_view_->setRubberBand(QChartView::VerticalRubberBand);
        // 设置ChartView样式，使用绝对定位居中
        //        chart_view_->setStyleSheet("position: absolute; "
        //                                 "top: 50%; left: 50%; "
        //                                 "transform: translate(-50%, -50%);");
        layout_ = new QVBoxLayout(parent_view_ptr_);
        // 将ChartView添加到布局中，并设置填充和居中
        layout_->addWidget(chart_view_);
        layout_->setAlignment(Qt::AlignCenter);
        parent_view_ptr_->setLayout(layout_);
        //创建坐标轴
        axisX_ = new QValueAxis;
        axisY_ = new QValueAxis;

        axisX_->setRange(0,100);
        axisX_->setTitleText("点数计数");
        axisX_->setTickCount(10);
        axisX_->setMinorTickCount(5);

        axisY_->setRange(-10.0, -40.0);
        axisY_->setTitleText("磁场强度");
        axisY_->setTickCount(5);
        axisY_->setMinorTickCount(5);
        //创建折线序列
        for(int i = 0; i < CH_NUM; i++)
        {
            seriess_[i] = new QtCharts::QLineSeries();
            seriess_[i]->setName(QString("ch%1").arg(i+1));
            chart_->addSeries(seriess_[i]);
            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
            chart_->setAxisY(axisY_,seriess_[i]);
        }
    }

    void setRange(int count)
    {
        int count0 = seriess_[0]->count();
        if(count0 > 1)
        {
            qreal ymin = seriess_[0]->at(0).y();
            qreal ymax = seriess_[0]->at(0).y();
            for(int i = 0; i < count0; i++)
            {
                ymin = std::min(ymin, seriess_[0]->at(i).y());
                ymin = std::min(ymin, seriess_[1]->at(i).y());
                ymin = std::min(ymin, seriess_[2]->at(i).y());
                ymin = std::min(ymin, seriess_[3]->at(i).y());
                ymin = std::min(ymin, seriess_[4]->at(i).y());
                ymin = std::min(ymin, seriess_[5]->at(i).y());

                ymax = std::max(ymax, seriess_[0]->at(i).y());
                ymax = std::max(ymax, seriess_[1]->at(i).y());
                ymax = std::max(ymax, seriess_[2]->at(i).y());
                ymax = std::max(ymax, seriess_[3]->at(i).y());
                ymax = std::max(ymax, seriess_[4]->at(i).y());
                ymax = std::max(ymax, seriess_[5]->at(i).y());
            }
            axisX_->setRange(count - DRAW_MAX_SIZE - DRAW_ADD_SIZE, count + DRAW_ADD_SIZE);
            if(ymin < 0)
            {
                ymin *= 1.15;
            }
            else
            {
                ymin /= 1.15;
            }
            if(ymax < 0)
            {
                ymax /= 1.15;
            }
            else
            {
                ymax *= 1.15;
            }
            axisY_->setRange(ymin, ymax);
            qDebug()<<"y:"<<ymin<<"~"<<ymax<<"\n";
        }
    }

    void updateView(QVector<ChinnelData>& draw_list)
    {

        if(draw_list.size() == DRAW_ADD_SIZE)
        {
            if (seriess_[0]->count() > DRAW_MAX_SIZE)// || seriess_[1]->count() >DRAW_MAX_SIZE)
            {
                for(int i = 0; i < CH_NUM; i++)
                {
                    seriess_[i]->removePoints(0,DRAW_ADD_SIZE);
                }
            }
            int x = count_points_;
            foreach (auto drawItem, draw_list)
            {
                seriess_[0]->append(x, (qreal)drawItem.mag_data.data[0]);
                seriess_[1]->append(x, (qreal)drawItem.mag_data.data[1]);
                seriess_[2]->append(x, (qreal)drawItem.mag_data.data[2]);
                seriess_[3]->append(x, (qreal)drawItem.mag_data.data[3]);
                seriess_[4]->append(x, (qreal)drawItem.mag_data.data[4]);
                seriess_[5]->append(x, (qreal)drawItem.mag_data.data[5]);
                x++;
                //qDebug()<<"point 1:"<<drawItem.index<<" "<<drawItem.mag_data.ch1<<"\n";
                //qDebug()<<"point 2:"<<drawItem.index<<" "<<drawItem.mag_data.ch2<<"\n";
            }
            count_points_ += DRAW_ADD_SIZE;
            setRange(count_points_);
        }
    }

    void setChinnelRange()
    {
        qreal ymin = 0.0;
        qreal ymax = 0.0;
        bool is_init = false;
        count_points_ += DRAW_ADD_SIZE;

        ymin = 1000000;
        ymax = -1000000;
        for(int i = 0; i < CH_NUM; i++)
        {
            if(ch_is_on_[i])
            {
                if(!is_init)
                {
                    is_init = true;
                }
                ymin = std::min(ymin_[i],ymin);
                ymax = std::max(ymax_[i],ymax);
            }
        }
        if(ymin < 0)
        {
            ymin *= ZOOM_NUM;
        }
        else
        {
            ymin /= ZOOM_NUM;
        }
        if(ymax < 0)
        {
            ymax /= ZOOM_NUM;
        }
        else
        {
            ymax *= ZOOM_NUM;
        }
        if(is_init)
        {
            axisX_->setRange(count_points_ - DRAW_MAX_SIZE - DRAW_ADD_SIZE, count_points_ + DRAW_ADD_SIZE);
            axisY_->setRange(ymin, ymax);
        }
    }

    void updateChinnelView(QVector<ChinnelData>& draw_list,int ch_num, bool is_on)
    {
        int x = count_points_;
        if(DRAW_ADD_SIZE != draw_list.size())
        {
            return;
        }
        if(seriess_[ch_num] && is_on)
        {
            ch_is_on_[ch_num] = is_on;

            if (seriess_[ch_num]->count() > DRAW_MAX_SIZE)// || seriess_[1]->count() >DRAW_MAX_SIZE)
            {
                seriess_[ch_num]->removePoints(0,DRAW_ADD_SIZE);
            }

            foreach (auto drawItem, draw_list)
            {
                seriess_[ch_num]->append(x++, (qreal)drawItem.mag_data.data[ch_num]);
            }
            qreal ymin = seriess_[ch_num]->at(0).y();
            qreal ymax = seriess_[ch_num]->at(0).y();
            int count = seriess_[ch_num]->count();
            for(int i = 0; i < seriess_[ch_num]->count(); i++)
            {
                ymin = std::min(ymin, seriess_[ch_num]->at(i).y());
                ymax = std::max(ymax, seriess_[ch_num]->at(i).y());
            }
            ymin_[ch_num] = ymin;
            ymax_[ch_num] = ymax;
            //setChinnelRange();
        }
    }

};

#endif // REALTIMECHARTVIEW_H
