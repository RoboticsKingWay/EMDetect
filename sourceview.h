#ifndef SOURCEVIEW_H
#define SOURCEVIEW_H

#include <QThread>
#include "ZoomableChartView.h"
#include "UnitData.h"

class SourceView : public BaseView
{
    Q_OBJECT
public:
    explicit SourceView(QWidget* parent)
        : BaseView(parent)
    {

    }
    virtual ~SourceView()
    {
        if(butterfly_serial_ptr_)
        {
            butterfly_serial_ptr_->clear();
            delete butterfly_serial_ptr_;
            butterfly_serial_ptr_ = nullptr;
        }
        if(circle_series_ptr_)
        {
            circle_series_ptr_->clear();
            delete circle_series_ptr_;
            circle_series_ptr_ = nullptr;
        }
    }


    virtual void createChartView() override
    {
        BaseView::createChartView();
        chart_view_->setLocationShow(false);
        newSerial();
    }

    void newCircle(QPointF center_point, int radius)
    {
        if(!circle_series_ptr_)
        {
            circle_series_ptr_ = new QLineSeries();
            chart_->addSeries(circle_series_ptr_);
            chart_->setAxisX(axisX_,circle_series_ptr_);//为序列添加坐标轴
            chart_->setAxisY(axisY_,circle_series_ptr_);
        }
        circle_series_ptr_->clear();
        QVector<QPointF> point_list;
        for (int angle = 0; angle < 360; angle += 5)
        {
            double radians = angle * (M_PI / 180.0);
            QPointF point(radius * cos(radians) + center_point.x(),
                          radius * sin(radians) + center_point.y());
            point_list.append(point);
        }
        for (int i = 0; i < point_list.size(); ++i)
        {
            circle_series_ptr_->append(point_list[i]);
            if (i > 0)
            {
                circle_series_ptr_->append(point_list[(i + 1) % point_list.size()]);
            }
        }
    }

    void newSerial()
    {
        if(butterfly_serial_ptr_)
        {
            butterfly_serial_ptr_->clear();
            delete butterfly_serial_ptr_;
        }
        butterfly_serial_ptr_ = new QtCharts::QLineSeries();
        butterfly_serial_ptr_->setName(QString("蝶形图"));
        QPen pen(QColor(255,0,0));
        pen.setWidth(1);
        butterfly_serial_ptr_->setPen(pen);
        chart_->addSeries(butterfly_serial_ptr_);
        chart_->setAxisX(axisX_,butterfly_serial_ptr_);//为序列添加坐标轴
        chart_->setAxisY(axisY_,butterfly_serial_ptr_);
        chart_->legend()->hide();
    }

    void setViewChinnelRange()
    {
        int ymin = y_min_;
        int ymax = y_max_;
        int xmin = x_min_;
        int xmax = x_max_;
        if(ymin < 0)
        {
            ymin *= ZOOM_NUM_SOURCE_VIEW;
        }
        else
        {
            ymin /= ZOOM_NUM_SOURCE_VIEW;
        }
        if(ymax < 0)
        {
            ymax /= ZOOM_NUM_SOURCE_VIEW;
        }
        else
        {
            ymax *= ZOOM_NUM_SOURCE_VIEW;
        }

        if(xmin < 0)
        {
            xmin *= ZOOM_NUM_SOURCE_VIEW;
        }
        else
        {
            xmin /= ZOOM_NUM_SOURCE_VIEW;
        }
        if(xmax < 0)
        {
            xmax /= ZOOM_NUM_SOURCE_VIEW;
        }
        else
        {
            xmax *= ZOOM_NUM_SOURCE_VIEW;
        }

        axisX_->setRange(xmin, xmax);
        axisY_->setRange(ymin, ymax);
//        qDebug()<<"ymin_:"<<ymin<<"  ymax_:"<<ymax;
//        qDebug()<<"xmin_:"<<xmin<<"  xmax_:"<<xmax;
    }

    void updateChinnelView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        if (butterfly_serial_ptr_->count() >= DetectSettings::instance().max_points_count())
        {
//            butterfly_serial_ptr_->removePoints(0,draw_list.size());
            qDebug()<<"remove all point:"<<butterfly_serial_ptr_->count();
            resetSerials();

        }
//        int ymin = 1000000;
//        int ymax = -1000000;
//        int xmin = 1000000;
//        int xmax = -1000000;
        for (int j = 0; j< draw_list.size(); j = j+5)
        {
            butterfly_serial_ptr_->append(QPointF(draw_list[j].mag_data.data[1],draw_list[j].mag_data.data[0]));
            // 直接取极大值 和极小值
            y_min_ = std::min(y_min_, draw_list[j].mag_data.data[0]);
            y_max_ = std::max(y_max_, draw_list[j].mag_data.data[0]);
            x_min_ = std::min(x_min_, draw_list[j].mag_data.data[1]);
            x_max_ = std::max(x_max_, draw_list[j].mag_data.data[1]);
        }
        if(chart_ && chart_view_)
        {
            chart_->update();
            chart_view_->update();
        }
//        int start = butterfly_serial_ptr_->count() - draw_list.size();
//        for(int i = start; i < butterfly_serial_ptr_->count() ; i++)
//        {
//            ymin = std::min(ymin, (int)butterfly_serial_ptr_->at(i).y());
//            ymax = std::max(ymax, (int)butterfly_serial_ptr_->at(i).y());
//            xmin = std::min(xmin, (int)butterfly_serial_ptr_->at(i).x());
//            xmax = std::max(xmax, (int)butterfly_serial_ptr_->at(i).x());
//        }
//        y_min_ = ymin;
//        y_max_ = ymax;
//        x_min_ = xmin;
//        x_max_ = xmax;
        count_source_points_ += draw_list.size();
    }

    void updateButterflyView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        int ymin = 1000000;
        int ymax = -1000000;
        int xmin = 1000000;
        int xmax = -1000000;
        for (int j = 0; j< draw_list.size(); j++)
        {
            butterfly_serial_ptr_->append(QPointF(draw_list[j].mag_data.data[1],draw_list[j].mag_data.data[0]));
        }

        xmin = std::min(butterfly_serial_ptr_->at(0).x(),butterfly_serial_ptr_->at(butterfly_serial_ptr_->count()-1).x());
        xmax = std::max(butterfly_serial_ptr_->at(0).x(),butterfly_serial_ptr_->at(butterfly_serial_ptr_->count()-1).x());
        ymin = std::min(butterfly_serial_ptr_->at(0).y(),butterfly_serial_ptr_->at(butterfly_serial_ptr_->count()-1).y());
        ymax = std::max(butterfly_serial_ptr_->at(0).y(),butterfly_serial_ptr_->at(butterfly_serial_ptr_->count()-1).y());
        y_max_ = std::max(ymax,y_max_);
        y_min_ = std::min(ymin,y_min_);
        x_max_ = std::max(xmax,x_max_);
        x_min_ = std::min(xmin,x_min_);
        if(chart_ && chart_view_)
        {
            chart_->update();
            chart_view_->update();
        }
    }
    virtual void resetSerials() override
    {
        if(butterfly_serial_ptr_)
        {
            newSerial();
            if(chart_ && chart_view_)
            {
                chart_->update();
                chart_view_->update();
            }
        }
        y_min_ = 1000000;
        y_max_ = -1000000;
        x_min_ = 1000000;
        x_max_ = -1000000;
        count_source_points_ = 0;
    }

private:
    int y_min_;
    int y_max_;
    int x_min_;
    int x_max_;
    QtCharts::QLineSeries* butterfly_serial_ptr_ {nullptr};
    QLineSeries* circle_series_ptr_ {nullptr};
};

#endif // SOURCEVIEW_H
