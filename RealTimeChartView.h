#ifndef REALTIMECHARTVIEW_H
#define REALTIMECHARTVIEW_H

#include "UnitData.h"
#include "ZoomableChartView.h"

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

//        layout_ = new QVBoxLayout(parent_view_ptr_);
//        // 将ChartView添加到布局中，并设置填充和居中
//        layout_->addWidget(chart_view_);
//        layout_->setAlignment(Qt::AlignCenter);
//        parent_view_ptr_->setLayout(layout_);
        //创建坐标轴
        axisX_ = new QValueAxis;
        axisY_ = new QValueAxis;

        axisX_->setRange(0,100);
        axisX_->setTitleText("点数计数");
        axisX_->setTickCount(10);
        axisX_->setMinorTickCount(5);

        axisY_->setRange(-10.0, -40.0);
        axisY_->setTitleText("磁场强度nT");
        axisY_->setTickCount(5);
        axisY_->setMinorTickCount(5);
        //创建折线序列
        for(int i = 0; i < CH_NUM; i++)
        {
            seriess_[i] = new QtCharts::QLineSeries();
            seriess_[i]->setName(QString("ch%1").arg(i+1));
            seriess_[i]->setColor(serial_color_list[i]);
            QPen pen(serial_color_list[i]);
            pen.setWidth(2);
            seriess_[i]->setPen(pen);

            chart_->addSeries(seriess_[i]);
            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
            chart_->setAxisY(axisY_,seriess_[i]);
        }
    }

    void setChinnelRange()
    {
        qreal ymin = 0.0;
        qreal ymax = 0.0;
        bool is_init = false;

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

            if(count_points_ > 10000)
            {
//                axisX_->setTitleText("点数计数10^3");
                axisX_->setRange((count_points_ - DRAW_MAX_SIZE - DRAW_ADD_SIZE), (count_points_ + DRAW_ADD_SIZE));
            }
            else
            {
              axisX_->setRange(count_points_ - DRAW_MAX_SIZE - DRAW_ADD_SIZE, count_points_ + DRAW_ADD_SIZE);
            }
            axisY_->setRange(ymin, ymax);
//            axisX_->setTitleText("磁场强度nT");
        }
    }

    void updateChinnelView(QVector<ChinnelData>& draw_list,int ch_num, bool is_on)
    {
        if(DRAW_ADD_SIZE != draw_list.size())
        {
            return;
        }
        count_points_ = draw_list[0].index + draw_list.size();
        int x = draw_list[0].index;;
        if(seriess_[ch_num] && is_on)
        {
            ch_is_on_[ch_num] = is_on;

            if (seriess_[ch_num]->count() > DRAW_MAX_SIZE)// || seriess_[1]->count() >DRAW_MAX_SIZE)
            {
                seriess_[ch_num]->removePoints(0,draw_list.size());
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
    void setCurrentPointCount(int index)
    {
        count_points_ = index;
    }
private:
    int count_points_ = 0;
};

#endif // REALTIMECHARTVIEW_H
