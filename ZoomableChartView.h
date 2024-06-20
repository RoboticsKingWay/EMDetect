#ifndef ZOOMABLECHARTVIEW_H
#define ZOOMABLECHARTVIEW_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include <QWheelEvent>
#include <QLegend>
#include "UnitData.h"

class ZoomableChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ZoomableChartView(QChart* chart)
        : QChartView( chart)
    {
    }
    virtual ~ZoomableChartView()
    {
    }
protected:
    void wheelEvent(QWheelEvent *event) override {
        if (!event)
            return;

        const double zoomInFactor = 1.15;
        const double zoomOutFactor = 0.8666; // 1/1.15

        double factor = event->angleDelta().y() > 0 ? zoomInFactor : zoomOutFactor;
        if (event->modifiers() & Qt::ControlModifier)
        {
            // 使用 Ctrl 键进行缩放
            chart()->zoom(factor);
        }
        else
        {
            // 平移图表
            //            QPoint delta = event->angleDelta().x() / 15, deltay = event->angleDelta().y() / 15;
            //            chart()->scroll(-deltax, -deltay);
            QChartView::wheelEvent(event); // 默认滚动行为
        }
        event->accept();
    }
};

class BaseView : public QObject
{
    Q_OBJECT
public:
    explicit BaseView(QWidget *parent = nullptr)
        : QObject( parent)
    {
        parent_view_ptr_ = parent;
    }
    virtual ~BaseView()
    {
        for(int i = 0; i < CH_NUM; i++)
        {
            if(seriess_[i])
            {
                delete seriess_[i];
                seriess_[i] = nullptr;
            }
        }
        if(axisX_)
        {
            delete axisX_;
        }
        if(axisY_)
        {
            delete axisY_;
        }
        if(chart_)
        {
            delete chart_;
        }
        if(chart_view_)
        {
            layout_->removeWidget(chart_view_);
            delete chart_view_;
        }
//        if(layout_)
//        {//随父窗口释放而释放，不能直接释放
//            delete layout_;
//        }
    }
    virtual void createChartView()
    {
        chart_ = new QChart();
        //chart_->setTitle(QStringLiteral("实时曲线"));
        //创建图表
        chart_view_ = new ZoomableChartView(chart_);
        chart_view_->setChart(chart_);//将chart添加到chartview中
        chart_view_->setRubberBand(QChartView::VerticalRubberBand);

        layout_ = new QVBoxLayout(parent_view_ptr_);
        // 将ChartView添加到布局中，并设置填充和居中
        layout_->addWidget(chart_view_);
        //layout_->setAlignment(Qt::AlignCenter);
        parent_view_ptr_->setLayout(layout_);
        //创建坐标轴
        axisX_ = new QValueAxis;
        axisY_ = new QValueAxis;
        axisX_->setRange(0,100);
        axisX_->setTitleText("点数计数");

        axisY_->setRange(-0.0, -40.0);
        axisY_->setTitleText("磁场强度");
        //创建折线序列
        for(int i = 0; i < CH_NUM; i++)
        {
            seriess_[i] = new QtCharts::QLineSeries();
            seriess_[i]->setName(QString("ch%1").arg(i+1));
            seriess_[i]->setPointLabelsFont(QFont("Arial", 4));
            //seriess_[i]->setPointLabelsVisible(true);
            chart_->addSeries(seriess_[i]);
            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
            chart_->setAxisY(axisY_,seriess_[i]);
        }
    }
protected:
    QtCharts::QLineSeries* seriess_[CH_NUM] = {nullptr};
    bool ch_is_on_[CH_NUM] = {false};
    double ymin_[CH_NUM];
    double ymax_[CH_NUM];
    QValueAxis *axisX_ = {nullptr};
    QValueAxis *axisY_ = {nullptr};
    ZoomableChartView *chart_view_ = {nullptr};
    QChart* chart_ = {nullptr};
    QVBoxLayout* layout_ = {nullptr};
    QWidget* parent_view_ptr_ {nullptr};
};

#endif // ZOOMABLECHARTVIEW_H
