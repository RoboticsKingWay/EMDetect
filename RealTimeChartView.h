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
        threshold_up_line_.resize(2);
        threshold_down_line_.resize(2);
    }
    virtual ~RealTimeChartView()
    {
        if(threshold_serials_)
        {
            if(threshold_serials_[0])
            {
                delete threshold_serials_[0];
                threshold_serials_[0] = nullptr;
            }
            if(threshold_serials_[1])
            {
                delete threshold_serials_[1];
                threshold_serials_[1] = nullptr;
            }
        }
    }
    virtual void createChartView() override
    {
        chart_ = new QChart();
//        chart_->setTitle(QStringLiteral("实时曲线"));
        //创建图表
        chart_view_ = new ZoomableChartView(chart_);
        chart_view_->setChart(chart_);//将chart添加到chartview中
        chart_view_->setRenderHint(QPainter::Antialiasing);
        chart_view_->setRubberBand(QChartView::RectangleRubberBand); // 用于选择图表区域
        chart_view_->setResizeAnchor(QGraphicsView::AnchorUnderMouse); // 设置缩放锚点
        // 鼠标滚轮缩放
//        chart_view_->setRubberBand(QChartView::VerticalRubberBand);

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
        axisX_->setTickCount(5);
        axisX_->setMinorTickCount(2);

        axisY_->setRange(40.0, -40.0);
        axisY_->setTitleText("磁场强度nT");
        axisY_->setTickCount(5);
        axisY_->setMinorTickCount(2);
        //创建折线序列
        for(int i = 0; i < CH_NUM; i++)
        {
            seriess_[i] = new QtCharts::QLineSeries();
            seriess_[i]->setName(QString("通道%1").arg(i+1));
            seriess_[i]->setColor(serial_color_list[i]);
            QPen pen(serial_color_list[i]);
            pen.setWidth(2);
            seriess_[i]->setPen(pen);

            chart_->addSeries(seriess_[i]);
            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
            chart_->setAxisY(axisY_,seriess_[i]);
        }

        QPen pen(QColor(255,0,0,255));
        pen.setWidth(2);
        threshold_serials_[0] = new QtCharts::QLineSeries();
        threshold_serials_[0]->setName(QString("上阈值线"));
        threshold_serials_[0]->append(0,0);
        threshold_serials_[0]->append(0,0.001);
        threshold_serials_[0]->setPen(pen);
        chart_->addSeries(threshold_serials_[0]);
        chart_->setAxisX(axisX_,threshold_serials_[0]);
        chart_->setAxisY(axisY_,threshold_serials_[0]);

        threshold_serials_[1] = new QtCharts::QLineSeries();
        threshold_serials_[1]->setName(QString("下阈值线"));
        threshold_serials_[1]->append(0,0);
        threshold_serials_[1]->append(0,0.001);
        threshold_serials_[1]->setPen(pen);
        chart_->addSeries(threshold_serials_[1]);
        chart_->setAxisX(axisX_,threshold_serials_[1]);
        chart_->setAxisY(axisY_,threshold_serials_[1]);
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
            int x_since = count_points_ - DRAW_MAX_SIZE - draw_add_size_;
            int x_to    = count_points_ + draw_add_size_;

//          axisX_->setTitleText("点数计数10^3");
            axisX_->setRange(x_since, x_to);
            axisY_->setRange(ymin, ymax);
//            axisX_->setTitleText("磁场强度nT");
            if(!b_up_move_to_)
            {
                move_upline_to_   = ymax;
            }
            if(!b_down_move_to_)
            {
                move_downline_to_ = ymin;
            }

            int y_up_value   = move_upline_to_   + move_up_count_   * setp_move_for_line_;
            int y_down_value = move_downline_to_ + move_down_count_ * setp_move_for_line_;

            threshold_up_line_[0]   = QPointF(x_since, y_up_value);
            threshold_up_line_[1]   = QPointF(x_to, y_up_value);
            threshold_down_line_[0] = QPointF(x_since, y_down_value);
            threshold_down_line_[1] = QPointF(x_to, y_down_value);
        }
        if(b_upline_show_)
        {
            threshold_serials_[0]->replace(threshold_up_line_);
        }
        if(b_downline_show_)
        {
            threshold_serials_[1]->replace(threshold_down_line_);
        }
    }

    void updateChinnelView(QVector<ChinnelData>& draw_list,int ch_num, bool is_on)
    {
        if(draw_add_size_ != draw_list.size())
        {
            return;
        }
        count_points_ = draw_list[0].index + draw_list.size();
        int x = draw_list[0].index;;
        if(seriess_[ch_num] && is_on)
        {
            ch_is_on_[ch_num] = is_on;

            if (seriess_[ch_num]->count() > DRAW_MAX_SIZE)
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
        }
    }
    void setCurrentPointCount(int index)
    {
        count_points_ = index;
    }
    void setUpline(bool show)
    {
        b_upline_show_ = show;
    }
    void setDownline(bool show)
    {
        b_downline_show_ = show;
    }
public slots:
    void on_uplinePlus()
    {
        move_up_count_++;
    }
    void on_uplineDe()
    {
        move_up_count_--;
    }
    void on_uplineMoveto(double y_to)
    {
        move_upline_to_ = y_to;
        b_up_move_to_ = true;
    }
    void on_uplineReset()
    {
        move_upline_to_ = 0;
        b_up_move_to_ = false;
        move_up_count_ = 0;
    }
    void on_downlinePlus()
    {
        move_down_count_++;
    }
    void on_downlineDe()
    {
        move_down_count_--;
    }
    void on_downlineMoveto(double y_to)
    {
        move_downline_to_ = y_to;
        b_down_move_to_ = true;
    }
    void on_downlineReset()
    {
        move_upline_to_ = 0;
        b_down_move_to_ = false;
        move_down_count_ = 0;
    }
private:
    int count_points_ = 0;
    QtCharts::QLineSeries* threshold_serials_[2] = {nullptr};
    bool b_upline_show_ { false };
    bool b_downline_show_ { false };
    bool b_up_move_to_ {false};
    bool b_down_move_to_ {false};
    int move_up_count_  {-1};
    int move_down_count_  {1};
    int move_upline_to_{0};
    int move_downline_to_{0};
    QVector<QPointF> threshold_up_line_;
    QVector<QPointF> threshold_down_line_;
    const int setp_move_for_line_ = 100;
};

#endif // REALTIMECHARTVIEW_H
