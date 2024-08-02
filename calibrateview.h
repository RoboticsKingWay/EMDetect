#ifndef CALIBRATEVIEW_H
#define CALIBRATEVIEW_H

#include <QDebug>
#include <QMap>
#include <QTabWidget>
#include <functional>
#include "UnitData.h"
#include "DetectSettings.h"

namespace Ui {
class CalibrateView;
}

class CalibrateView : public QTabWidget
{
    Q_OBJECT

public:
    explicit CalibrateView(QWidget *parent = nullptr);
    ~CalibrateView();
    std::pair<double, double> getStandarParam()
    {
        return result_param_;
    }
    double getAmplitude()
    {
        return inside_amplitude_;
    }
    void initView(/*std::function<void(QVector<QPointF>&)> getDetectRectData_Func*/);
public slots:
    void on_GetRectData(QVector<QPointF>& points);
private slots:
    void on_comboBox_outside_list_currentIndexChanged(int index);

    void on_pushButton_outside_add_clicked();

    void on_pushButton_outside_del_clicked();

    void on_comboBox_inside_list_currentIndexChanged(int index);

    void on_pushButton_inside_add_clicked();

    void on_pushButton_inside_del_clicked();

    void on_pushButton_outside_stand_clicked();

    void on_pushButton_inside_stand_clicked();

    void on_pushButton_outside_stand_save_clicked();

    void on_pushButton_inside_stand_save_clicked();

private:
    Ui::CalibrateView *ui;
    QMap<QString,DetectDeclaerParam> cfg_detection_list_;
    std::pair<double, double> result_param_;
//    QVector<double> amplitude_list_;
    double inside_amplitude_;
//    std::function<void(QVector<QPointF>&)> getDetectRectData_Func_;
};

#endif // CALIBRATEVIEW_H
