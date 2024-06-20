#ifndef SOURCEVIEW_H
#define SOURCEVIEW_H

//#include <QObject>
//#include <QtCharts>
//#include <QtCharts/QChart>
#include "ZoomableChartView.h"
#include "UnitData.h"

static int count_source_points_ = 0;
class SourceView : public BaseView
{
    Q_OBJECT
public:
    explicit SourceView(QWidget *parent = nullptr)
        : BaseView(parent)
    {

    }
    virtual void createChartView() override
    {
        BaseView::createChartView();
//        chart_->legend()->setFont(QFont("Arial", 5));
        chart_->setTitleFont(QFont("Arial", 5));
        chart_->setTitle("原始数据");
        chart_->setMargins(QMargins(10,0,10,0));
        //chart_->legend()->setPos(QLegend::BottomLeft);  // 默认在底部
//        chart_->layout()->setContentsMargins(10, 5, 10, 3);  // 增加顶部边距
//        chart_->legend()->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        for(int i = 0; i < CH_NUM; i++)
        {
//            seriess_[i]->setPointLabelsFont(QFont("Arial", 4));
//            seriess_[i]->setPointLabelsVisible(true);
            //seriess_[i]->setPointLabelsFont();
//            seriess_[i] = new QtCharts::QLineSeries();
//            seriess_[i]->setName(QString("ch%1").arg(i+1));
//            chart_->addSeries(seriess_[i]);
//            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
//            chart_->setAxisY(axisY_,seriess_[i]);
        }

        axisX_->setRange(0,200);
        axisX_->setTickCount(10);
        axisX_->setMinorTickCount(100);
        axisX_->setLabelsFont(QFont("Arial", 5));
        axisX_->setTitleFont(QFont("Arial", 5));
        axisX_->setTitleText("测量长度mm");

        axisY_->setRange(-10.0, 10.0);
        axisX_->setTickCount(4);
        axisX_->setMinorTickCount(20);
        axisY_->setTitleText("磁场强度");
        axisY_->setTitleFont(QFont("Arial", 5));
        axisY_->setLabelsFont(QFont("Arial", 5));

        //chart_view_->setFont(QFont("Arial", 5));
//        chart_view_->setAlignment(Qt::AlignHorizontal_Mask);
//        layout_->setMargin(0);
    }
    void setChinnelRange()
    {
        qreal ymin = 0.0;
        qreal ymax = 0.0;

        ymin = 1000000;
        ymax = -1000000;
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
    }

    void updateChinnelView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        for(int i = 0; i < CH_NUM; i++)
        {
            int x = count_source_points_;
            qreal ymin = 1000000;
            qreal ymax = -1000000;

            for(int i = 0; i < CH_NUM; i++)
            {
                if (seriess_[i]->count() > SRC_MAX_SIZE)
                {
                    seriess_[i]->removePoints(0,draw_list.size());
                }
            }
            QList<QPointF> points;
            foreach (auto drawItem, draw_list)
            {
                points.append(QPointF(x++,(qreal)drawItem.mag_data.data[i]));
                //seriess_[i]->append(x++, (qreal)drawItem.mag_data.data[i]);
                ymin = std::min(ymin, (qreal)drawItem.mag_data.data[i]);
                ymax = std::max(ymax, (qreal)drawItem.mag_data.data[i]);
            }
            seriess_[i]->append(points);
            ymin_[i] = ymin;
            ymax_[i] = ymax;
        }
        count_source_points_ += draw_list.size();
        if(count_source_points_ >= SRC_MAX_SIZE)
        {
            setChinnelRange();
        }
        count_source_points_ = count_source_points_%SRC_MAX_SIZE;
    }

    void darwChinnelView(QVector<ChinnelData>& draw_list)
    {
        if(0 >= draw_list.size())
        {
            return;
        }
        resetSerials();
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
            ymin_[i] = ymin;
            ymax_[i] = ymax;
        }
        count_source_points_ = draw_list.size();
        setChinnelRange();
        count_source_points_ = 0;
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
