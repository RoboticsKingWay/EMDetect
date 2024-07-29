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
        if(threshold_serials_)
        {
            if(threshold_serials_[0])
            {
                threshold_serials_[0]->clear();
                delete threshold_serials_[0];
                threshold_serials_[0] = nullptr;
            }
            if(threshold_serials_[1])
            {
                threshold_serials_[1]->clear();
                delete threshold_serials_[1];
                threshold_serials_[1] = nullptr;
            }
        }
        if(detect_rect_serials_)
        {
            detect_rect_serials_->clear();
            delete detect_rect_serials_;
            detect_rect_serials_ = nullptr;
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

        upline_start_ = DetectSettings::instance().upline();
        downline_start_ = DetectSettings::instance().downline();
        axisX_->setRange(0,200);
        axisX_->setTitleText("点数计数");
        axisX_->setTickCount(5);
        axisX_->setMinorTickCount(2);

        axisY_->setRange(downline_start_ - 1000, upline_start_ + 1000);
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
        threshold_serials_[0]->setName(QString("upline"));
//        upline_start_ = DetectSettings::instance().upline();
        ymax_value_   = upline_start_;
        threshold_serials_[0]->append(0,upline_start_);
        threshold_serials_[0]->append(draw_max_size_,upline_start_);
        threshold_up_line_.append(threshold_serials_[0]->at(0));
        threshold_up_line_.append(threshold_serials_[0]->at(1));
        threshold_serials_[0]->setPen(pen);
        threshold_serials_[0]->setVisible(false);
        chart_->addSeries(threshold_serials_[0]);
        chart_->setAxisX(axisX_,threshold_serials_[0]);
        chart_->setAxisY(axisY_,threshold_serials_[0]);

        threshold_serials_[1] = new QtCharts::QLineSeries();
        threshold_serials_[1]->setName(QString("downline"));
//        downline_start_ = DetectSettings::instance().downline();
        ymin_value_     = downline_start_;
        threshold_serials_[1]->append(0, downline_start_);
        threshold_serials_[1]->append(draw_max_size_, downline_start_);
        threshold_down_line_.append(threshold_serials_[1]->at(0));
        threshold_down_line_.append(threshold_serials_[1]->at(1));

        threshold_serials_[1]->setPen(pen);
        threshold_serials_[1]->setVisible(false);
        chart_->addSeries(threshold_serials_[1]);
        chart_->setAxisX(axisX_,threshold_serials_[1]);
        chart_->setAxisY(axisY_,threshold_serials_[1]);

        detect_rect_serials_ = new QtCharts::QLineSeries();
        detect_rect_serials_->setName(QString("detect"));
        detect_rect_serials_->setPen(pen);
        chart_->addSeries(detect_rect_serials_);
        chart_->setAxisX(axisX_,detect_rect_serials_);
        chart_->setAxisY(axisY_,detect_rect_serials_);
        if(chart_view_)
        {
            connect(chart_view_,&ZoomableChartView::selectRect,this,&RealTimeChartView::onSelectRect,Qt::AutoConnection);
        }
        showLegend("detect",false);
        showLegend("upline",false);
        showLegend("downline",false);
    }

    void showLegend(const QString &legendName, bool visible)
    {
        QLegend *legend = chart_->legend();
        if (legend)
        {
            for (QLegendMarker *marker : legend->markers())
            {
                if (marker->label() == legendName)
                {
                    marker->setVisible(visible);
                }
            }
        }
    }
    void setSelectSwitch(bool sw)
    {
        if(chart_view_)
        {
            chart_view_->b_select_rect_ = sw;
            if(sw)
            {
                chart_view_->setRubberBand(QChartView::NoRubberBand);
            }
            else
            {
                chart_view_->setRubberBand(QChartView::RectangleRubberBand);
            }
        }
    }
    void setChinnelRange(int count)
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
        ymax_value_ = ymax;
        ymin_value_ = ymin;
        count_points_ += count;
        int x_since = count_points_ - draw_max_size_ - draw_add_size_;
        int x_to    = count_points_ + draw_add_size_;
        //          axisX_->setTitleText("点数计数10^3");
        //            axisX_->setTitleText("磁场强度nT");
        updateThresholdLine(0,x_to);
        if(is_init)
        {
            axisX_->setRange(x_since, x_to);
            axisY_->setRange(ymin, ymax);
        }
    }
    QVector<QPointF> getThresholdUpline()
    {
        return threshold_up_line_;
    }
    QVector<QPointF> getThresholdDownline()
    {
        return threshold_down_line_;
    }
    void getDetectRectData(QVector<QPointF>& ret_points)
    {
        QVector<QPointF> points;
        qreal x_since = detect_rect_.left();
        qreal x_to    = detect_rect_.right();
        if(x_to > x_since)
        {
            for(int x = x_since; x < x_to; x++)
            {
                points.append(seriess_[0]->at(x));
            }
        }
        else if(x_since > x_to)
        {
            qDebug()<<"detect_rect_ error!!!!";
        }
        ret_points = points;
    }
    void updateChinnelView(QVector<ChinnelData>& draw_list,int ch_num, bool is_on)
    {
        if(draw_add_size_ != draw_list.size())
        {
            return;
        }
//        count_points_ = draw_list[0].index;
        int x = draw_list[0].index;
        if(seriess_[ch_num] && is_on)
        {
            ch_is_on_[ch_num] = is_on;

            if (seriess_[ch_num]->count() > DetectSettings::instance().max_points_count())
            {
                seriess_[ch_num]->removePoints(0,draw_list.size());
            }

            foreach (auto drawItem, draw_list)
            {
                seriess_[ch_num]->append(x++, (qreal)drawItem.mag_data.data[ch_num]);
            }
//            qreal ymin = seriess_[ch_num]->at(0).y();
//            qreal ymax = seriess_[ch_num]->at(0).y();
//            int count = seriess_[ch_num]->count();
//            for(int i = 0; i < seriess_[ch_num]->count(); i++)
//            {
//                ymin = std::min(ymin, seriess_[ch_num]->at(i).y());
//                ymax = std::max(ymax, seriess_[ch_num]->at(i).y());
//            }
//            int start = seriess_[ch_num]->count() - draw_list.size();
            qreal ymin = 1000000;
            qreal ymax = -1000000;
            int start = seriess_[ch_num]->count() - draw_list.size();
            if(seriess_[ch_num]->count() > 60)
            {
                start = seriess_[ch_num]->count() - 60;
            }

            for(int i = start; i < seriess_[ch_num]->count(); i++)
            {
                ymin = std::min(ymin, seriess_[ch_num]->at(i).y());
                ymax = std::max(ymax, seriess_[ch_num]->at(i).y());
            }
            ymin_[ch_num] = ymin;
            ymax_[ch_num] = ymax;
        }
    }

    void setUpline(bool show)
    {
        threshold_serials_[0]->setVisible(show);
    }
    void setDownline(bool show)
    {
        threshold_serials_[1]->setVisible(show);
    }
    void updateThresholdLine(qreal x_since, qreal x_to)
    {
        int y_up_value   = upline_start_   + move_up_count_   * setp_move_for_line_;
        int y_down_value = downline_start_ + move_down_count_ * setp_move_for_line_;

        threshold_up_line_[0]   = QPointF(x_since, y_up_value);
        threshold_up_line_[1]   = QPointF(x_to, y_up_value);
        threshold_down_line_[0] = QPointF(x_since, y_down_value);
        threshold_down_line_[1] = QPointF(x_to, y_down_value);

        threshold_serials_[0]->replace(threshold_up_line_);
        threshold_serials_[1]->replace(threshold_down_line_);
        DetectSettings::instance().setline(threshold_up_line_[0].y(), threshold_down_line_[0].y());
    }
    /*******************************************************/
    void setViewChinnelRange()
    {
        qreal ymin = 0.0;
        qreal ymax = 0.0;

        ymin = 1000000.0;
        ymax = -1000000.0;
        for(int i = 0; i < CH_NUM; i++)
        {
            ymin = std::min(ymin_[i],ymin);
            ymax = std::max(ymax_[i],ymax);
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
        ymax_value_ = ymax;
        ymin_value_ = ymin;

        int x_since = -10;
        int x_to    = count_source_points_ + 10;
        updateThresholdLine(x_since,x_to);
        axisX_->setRange(x_since, x_to);
        axisY_->setRange(ymin, ymax);
    }
    void updateChinnelView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        qreal ymin = 1000000.0;
        qreal ymax = -1000000.0;
        for(int i = 0; i < CH_NUM; i++)
        {
            int x = count_source_points_;
            QList<QPointF> points;
            for (int j = 0; j< draw_list.size(); j++)
            {
                points.append(QPointF(x++,(qreal)draw_list[j].mag_data.data[i]));
                //seriess_[i]->append(x++, (qreal)drawItem.mag_data.data[i]);
                ymin = std::min(ymin, (qreal)draw_list[j].mag_data.data[i]);
                ymax = std::max(ymax, (qreal)draw_list[j].mag_data.data[i]);
            }
            seriess_[i]->append(points);
            ymin_[i] = std::min(ymin,ymin_[i]);
            ymax_[i] = std::max(ymax,ymax_[i]);
            //            qDebug()<<"ymin_:"<<ymin_[i]<<"  ymax_:"<<ymax_[i];
        }
        count_source_points_ += draw_list.size();
        qDebug()<<"chartview count_source_points_:"<<count_source_points_<<QDateTime::currentDateTime();
    }
    /*******************************************************/
public slots:
    void on_uplinePlus()
    {
        move_up_count_++;
        updateThresholdLine(threshold_up_line_[0].x(),threshold_up_line_[1].x());
    }
    void on_uplineDe()
    {
        move_up_count_--;
        updateThresholdLine(threshold_up_line_[0].x(),threshold_up_line_[1].x());
    }
    void on_uplineMoveto(double y_to)
    {
        upline_start_ = y_to;
        move_up_count_ = 0;
        updateThresholdLine(threshold_up_line_[0].x(),threshold_up_line_[1].x());
    }
    void on_uplineReset()
    {
        upline_start_ = ymax_value_;
        move_up_count_ = 0;
        updateThresholdLine(threshold_up_line_[0].x(),threshold_up_line_[1].x());
    }
    void on_downlinePlus()
    {
        move_down_count_++;
        updateThresholdLine(threshold_down_line_[0].x(),threshold_down_line_[1].x());
    }
    void on_downlineDe()
    {
        move_down_count_--;
        updateThresholdLine(threshold_down_line_[0].x(),threshold_down_line_[1].x());
    }
    void on_downlineMoveto(double y_to)
    {
        downline_start_ = y_to;
        move_down_count_ = 0;
        updateThresholdLine(threshold_down_line_[0].x(),threshold_down_line_[1].x());
    }
    void on_downlineReset()
    {
        downline_start_ = ymin_value_;
        move_down_count_ = 0;
        updateThresholdLine(threshold_down_line_[0].x(),threshold_down_line_[1].x());
    }
    void onSelectRect(QPointF start,QPointF end)
    {
        if(detect_rect_serials_ && chart_)
        {
            detect_rect_serials_->clear();
            QList<QPointF> rect;
            rect.append(start);
            rect.append(QPoint(end.x(), start.y()));
            rect.append(end);
            rect.append(QPoint(start.x(),end.y()));
            rect.append(start);
            detect_rect_serials_->append(rect);
            chart_->update();
            detect_rect_ = QRectF(start,end);
            QVector<QPointF> rect_data;
            getDetectRectData(rect_data);
            emit rectData(rect_data);
        }
    }
    virtual void resetSerials() override
    {
        count_points_ = 0;
        BaseView::resetSerials();
    }
signals:
    void rectData(QVector<QPointF>& rect_data);
private:
    int count_points_ = 0;
    QtCharts::QLineSeries* threshold_serials_[2] = {nullptr};
    QtCharts::QLineSeries* detect_rect_serials_  = {nullptr};
    QList<QtCharts::QLineSeries*> auto_detect_rect_list_;
    int move_up_count_  {-1};
    int move_down_count_  {1};
    int upline_start_{0};
    int downline_start_{0};
    QVector<QPointF> threshold_up_line_;
    QVector<QPointF> threshold_down_line_;
    const int setp_move_for_line_ = 100;
    double ymax_value_ {26000};
    double ymin_value_{20000};
    QRectF detect_rect_;
};

#endif // REALTIMECHARTVIEW_H
