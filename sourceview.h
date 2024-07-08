#ifndef SOURCEVIEW_H
#define SOURCEVIEW_H

#include <QThread>
#include "ZoomableChartView.h"
#include "UnitData.h"

//class SourceView : public BaseView
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
    }


    virtual void createChartView() override
    {
        BaseView::createChartView();
//        chart_->setTheme(QChart::ChartThemeLight);
//        chart_->legend()->setFont(QFont("Arial", 5));
//        chart_->setTitleFont(QFont("Arial", 5));
//        chart_->setTitle("磁场强度nT");
//        chart_->setMargins(QMargins(10,0,10,0));

        axisX_->setRange(0,12000);
        axisX_->setTickCount(10);
        axisX_->setMinorTickCount(100);
//        axisX_->setLabelsFont(QFont("Arial", 5));
//        axisX_->setTitleFont(QFont("Arial", 6));
        axisX_->setTitleText("计数点数");

        axisY_->setRange(-30000.0, 30000.0);
        axisX_->setTickCount(4);
        axisX_->setMinorTickCount(20);
        axisY_->setTitleText("磁场强度nT");
//        axisY_->setTitleFont(QFont("Arial", 6));
//        axisY_->setLabelsFont(QFont("Arial", 5));
    }
    void setChinnelRange()
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

        axisX_->setRange(-10, count_source_points_ + 10);
        axisY_->setRange(ymin, ymax);
//        qDebug()<<"ymin_:"<<ymin<<"  ymax_:"<<ymax;
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
        qDebug()<<"count_source_points_:"<<count_source_points_<<QDateTime::currentDateTime();
    }

    void darwChinnelView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        resetSerials();
        qDebug()<<"start to draw:"<<QDateTime::currentDateTime();
        for(int i = 0; i < CH_NUM; i++)
        {
            int x = 0;
            qreal ymin = 1000000;
            qreal ymax = -1000000;

            QList<QPointF> points;
            foreach (auto drawItem, draw_list)
            {
                points.append(QPointF(x++,(qreal)drawItem.mag_data.data[i]));
                ymin = std::min(ymin, (qreal)drawItem.mag_data.data[i]);
                ymax = std::max(ymax, (qreal)drawItem.mag_data.data[i]);
            }
            seriess_[i]->append(points);
            ymin_[i] = std::min(ymin,ymin_[i]);
            ymax_[i] = std::max(ymax,ymax_[i]);
        }
        count_source_points_ = draw_list.size();
        setChinnelRange();
        count_source_points_ = 0;
        qDebug()<<"draw finished:"<<QDateTime::currentDateTime();
    }

    void resetSerials()
    {
        for(int i = 0; i < CH_NUM; i++)
        {
            seriess_[i]->clear();
            ymin_[i] = 1000000;
            ymax_[i] = -1000000;
        }
        count_source_points_ = 0;
    }
};

#endif // SOURCEVIEW_H
