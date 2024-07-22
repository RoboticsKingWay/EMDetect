#ifndef CALIBRATEVIEW_H
#define CALIBRATEVIEW_H

#include <QDebug>
#include <QMap>
#include <QTabWidget>
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
};

#endif // CALIBRATEVIEW_H
