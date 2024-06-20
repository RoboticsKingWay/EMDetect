#ifndef GRADIENTVIEW_H
#define GRADIENTVIEW_H

#include "ZoomableChartView.h"
#include "UnitData.h"


class GradientView : public BaseView
{
    Q_OBJECT
public:
    explicit GradientView(QWidget *parent = nullptr)
        : BaseView(parent)
    {

    }
    virtual void createChartView() override
    {

        BaseView::createChartView();

        //        chart_->legend()->setFont(QFont("Arial", 5));
        chart_->setTitleFont(QFont("Arial", 5));
        chart_->setTitle("梯度曲线");
        chart_->setMargins(QMargins(10,0,10,0));

        axisX_->setRange(0,200);
        axisX_->setTickCount(10);
        axisX_->setMinorTickCount(100);
        axisX_->setLabelsFont(QFont("Arial", 5));
        axisX_->setTitleFont(QFont("Arial", 5));
        axisX_->setTitleText("测量长度/mm");

        axisY_->setRange(-10.0, 10.0);
        axisX_->setTickCount(4);
        axisX_->setMinorTickCount(20);
        axisY_->setTitleText("磁场强度T");
        axisY_->setTitleFont(QFont("Arial", 5));
        axisY_->setLabelsFont(QFont("Arial", 5));

        //chart_view_->setFont(QFont("Arial", 5));
        chart_view_->setAlignment(Qt::AlignHorizontal_Mask);
        layout_->setMargin(0);
    }
};

#endif // GRADIENTVIEW_H
