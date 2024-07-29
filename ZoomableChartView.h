#ifndef ZOOMABLECHARTVIEW_H
#define ZOOMABLECHARTVIEW_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtWidgets>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include <QGraphicsObject>
#include <QLegend>
#include "UnitData.h"

class CircularItem : public QGraphicsObject
{
    Q_OBJECT
public:
    CircularItem(qreal x, qreal y, qreal radius, QGraphicsItem *parent = nullptr)
        : QGraphicsObject(parent), m_center(x, y), m_radius(radius) {}

    virtual QRectF boundingRect() const override
    {
        return QRectF(m_center - QPointF(m_radius, m_radius), QSizeF(2 * m_radius, 2 * m_radius));
    }

    virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::red, 2)); // 设置圆的颜色和线宽
        painter->drawEllipse(m_center, m_radius, m_radius);
//        QGraphicsObject::paint(painter,option, widget);
    }

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionHasChanged)
        {
            prepareGeometryChange();
        }
        return QGraphicsObject::itemChange(change, value);
    }

public slots:
    void updateCircle(const QPointF &newCenter, qreal newRadius)
    {
        m_center = newCenter;
        m_radius = newRadius;
        update();
    }

public:
    QPointF m_center;
    qreal m_radius;
};

class ZoomableChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ZoomableChartView(QChart* chart)
        : QChartView( chart)
    {
        grabGesture(Qt::PinchGesture);
        setMouseTracking(true); // 启用鼠标追踪
    }
    virtual ~ZoomableChartView()
    {
    }
    void setLocationShow(bool show)
    {
        is_localtion_show_ = show;
    }
signals:
    void selectRect(QPointF start,QPointF end);
protected:
//    void resizeEvent(QResizeEvent *event) override
//    {
//        QChartView::resizeEvent(event);
//    }
//    bool eventFilter(QObject *watched, QEvent *event)
//    {
//        QChartView::eventFilter(watched, event);
//        if(event->type() == QEvent::Paint)
//        {
//            QPainter painter(this);
//            if(painter.isActive())
//            {
//                QPointF cencer(0,0);
//                painter.drawEllipse(cencer, 100, 100);
//            }
//        }
//        return true;
//    }

//    virtual void paintEvent(QPaintEvent *event)override
//    {
//        QChartView::paintEvent(event); // 调用基类的事件处理
//    }
    virtual void gestureEvent(QGestureEvent *event) //override
    {
        if (event->gesture(Qt::PinchGesture))
        {
            QPinchGesture *pinchGesture = static_cast<QPinchGesture *>(event->gesture(Qt::PinchGesture));
            handlePinchGesture(pinchGesture);
        }
    }

    virtual void wheelEvent(QWheelEvent *event) override
    {
//        QChartView::wheelEvent(event); // 调用基类的事件处理
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
    virtual void mouseMoveEvent(QMouseEvent *event) override
    {
        QChartView::mouseMoveEvent(event); // 调用基类的事件处理
//        if(is_localtion_show_)
        {
            QPointF mousePoint = event->pos();
            QPointF point = chart()->mapToValue(event->pos());
            // 展示鼠标悬停位置的X和Y值
            QToolTip::showText(event->globalPos(), tr("X: %1, Y: %2").arg(point.x()).arg(point.y()), this);
        }
        event->accept();
    }
    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton && b_select_rect_)
        {
            start_point_ = chart()->mapToValue(event->pos());
        }
        else
        {
            QChartView::mousePressEvent(event); // 调用基类的事件处理
        }
        event->accept();
    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton && b_select_rect_)
        {
            end_point_ = chart()->mapToValue(event->pos());
            emit selectRect(start_point_,end_point_);
        }
        else
        {
            QChartView::mouseReleaseEvent(event); // 调用基类的事件处理
        }
        event->accept();
    }
    void handlePinchGesture(QPinchGesture *pinchGesture)
    {
        if (pinchGesture->state() == Qt::GestureStarted ||
            pinchGesture->state() == Qt::GestureUpdated) {

            // 计算缩放中心点
            QPointF center = pinchGesture->centerPoint().toPoint();
            // 计算缩放比例
            qreal scaleFactor = pinchGesture->scaleFactor() - 1.0;

            // 应用缩放变换
            Myzoom(scaleFactor, center);
        }
    }
    void Myzoom(qreal scaleFactor, const QPointF &center)
    {
        // 根据缩放比例和中心点调整图表的缩放
        // 这里需要根据你的具体图表和需求来实现缩放逻辑
        //
        scale(chart()->size().width() * scaleFactor, chart()->size().height() * scaleFactor);
        centerOn(center);
    }
public:
    bool is_localtion_show_{true};
    bool b_select_rect_    {false};
    QPointF start_point_;
    QPointF end_point_;
};

class BaseView : public QObject
{
    Q_OBJECT
public:
    explicit BaseView(QWidget *parent = nullptr)
        : QObject( parent)
    {
        parent_view_ptr_ = parent;
        draw_add_size_ = DetectSettings::instance().add_point_count();
        draw_max_size_ = DetectSettings::instance().max_darw_point_count();
    }
    virtual ~BaseView()
    {
        releaseView();
//        if(layout_)
//        {//随父窗口释放而释放，不能直接释放
//            delete layout_;
//        }
    }
    void releaseView()
    {
        for(int i = 0; i < CH_NUM; i++)
        {
            if(seriess_[i])
            {
                seriess_[i]->clear();
                delete seriess_[i];
                seriess_[i] = nullptr;
            }
        }
        if(axisX_)
        {
            delete axisX_;
            axisX_ = nullptr;
        }
        if(axisY_)
        {
            delete axisY_;
            axisY_ = nullptr;
        }
        if(chart_)
        {
            delete chart_;
            chart_ = nullptr;
        }
        if(chart_view_)
        {
            layout_->removeWidget(chart_view_);
            delete chart_view_;
            chart_view_ = nullptr;
        }
    }
    virtual void createChartView()
    {
        chart_ = new QChart();
//        chart_->setTheme(QChart::ChartThemeLight);
        chart_->setAnimationOptions(QChart::AllAnimations);
//        chart_->setAnimationOptions(QChart::NoAnimation); // 禁用图表动画
        chart_->setAnimationOptions(QChart::SeriesAnimations);
        //chart_->setTitle(QStringLiteral("实时曲线"));
        //创建图表
        chart_view_ = new ZoomableChartView(chart_);
//        chart_view_ = new QChartView(chart_);
        chart_view_->setChart(chart_);//将chart添加到chartview中
        chart_view_->setRenderHint(QPainter::Antialiasing);
        chart_view_->setRubberBand(QChartView::RectangleRubberBand); // 用于选择图表区域
        chart_view_->setResizeAnchor(QGraphicsView::AnchorUnderMouse); // 设置缩放锚点

        layout_ = new QVBoxLayout(parent_view_ptr_);
        layout_->setAlignment(Qt::AlignCenter);
        layout_->addWidget(chart_view_);
        parent_view_ptr_->setLayout(layout_);
        //创建坐标轴
        axisX_ = new QValueAxis;
        axisY_ = new QValueAxis;
        axisX_->setRange(-8000,8000);
        axisY_->setRange(-8000,8000);
        //创建折线序列
//        for(int i = 0; i < CH_NUM; i++)
//        {
//            seriess_[i] = new QtCharts::QLineSeries();
//            seriess_[i]->setName(QString("通道%1").arg(i+1));
//            QPen pen(serial_color_list[i]);
//            pen.setWidth(1);
//            seriess_[i]->setPen(pen);
//            seriess_[i]->setPointLabelsFont(QFont("Arial", 4));
//            //seriess_[i]->setPointLabelsVisible(true);
//            chart_->addSeries(seriess_[i]);
//            chart_->setAxisX(axisX_,seriess_[i]);//为序列添加坐标轴
//            chart_->setAxisY(axisY_,seriess_[i]);
//        }
    }

public slots:
    virtual void resetSerials()
    {
        for(int i = 0; i < CH_NUM; i++)
        {
            if(seriess_[i])
            {
                seriess_[i]->clear();
            }
            ymin_[i] = 1000000;
            ymax_[i] = -1000000;
        }
        count_source_points_ = 0;
    }
protected:
    QColor serial_color_list[CH_NUM] = {QColor(0,0,0),QColor(0,100,0)};
    QtCharts::QLineSeries* seriess_[CH_NUM] = {nullptr};
    bool ch_is_on_[CH_NUM] = {false};
    double ymin_[CH_NUM];
    double ymax_[CH_NUM];
    QValueAxis *axisX_ = {nullptr};
    QValueAxis *axisY_ = {nullptr};
//    ZoomableChartView *chart_view_ = {nullptr};

    QChart* chart_ = {nullptr};
    QVBoxLayout* layout_ = {nullptr};
    QWidget* parent_view_ptr_ {nullptr};
    int count_source_points_ = 0;
    int draw_add_size_ = {20};
    int draw_max_size_ = {300};
public:
    ZoomableChartView *chart_view_ = {nullptr};
};

#endif // ZOOMABLECHARTVIEW_H
