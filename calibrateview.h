#ifndef CALIBRATEVIEW_H
#define CALIBRATEVIEW_H

#include <QSettings>
#include <QString>
#include <QTextCodec>
#include <QVector>
#include <QDir>
#include <QFile>
#include <QRegExp>
#include <QMessageBox>
#include <QMap>
#include <QVector>
#include <QTabWidget>
#include <functional>
#include "UnitData.h"

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
    QVector<double> getAmplitude()
    {
        return amplitude_list_;
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

    void on_pushButton_outside_stand_save_clicked();

    void on_pushButton_inside_stand_save_clicked();

    void on_pushButton_inside_import_clicked();

    void on_pushButton_outside_import_clicked();

signals:
    void update_inside_detection_list(QMap<QString,InsideDetectParam>& inside_list);
    void update_outside_detection_list(QMap<QString,OutsideDetectParam>& out_list);
    void update_function_result(std::pair<double, double>& result_param);
private:
    bool saveSetting(QString dir,bool outside = true);
    bool importSetting(QString dir,bool outside = true);
private:
    Ui::CalibrateView *ui;
    QMap<QString,OutsideDetectParam> cfg_detection_outside_list_;
    QMap<QString,InsideDetectParam> cfg_detection_inside_list_;
    std::pair<double, double> result_param_{0,0};
    QVector<double> amplitude_list_;
//    double inside_amplitude_;
//    std::function<void(QVector<QPointF>&)> getDetectRectData_Func_;
};

#endif // CALIBRATEVIEW_H
