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
    QMap<QString,InsideDetectParam>& getInsideAmplitudeList()
    {
        return cfg_detection_inside_list_;
    }
    void initView(/*std::function<void(QVector<QPointF>&)> getDetectRectData_Func*/);
public slots:
    // 显示当前窗口时候表示为标定捕获，则捕获当前特征区域幅值
    void on_GetRectData(QVector<QPointF>& points);
private slots:
    void on_comboBox_outside_list_currentIndexChanged(int index);

    void on_pushButton_outside_add_clicked();

    void on_pushButton_outside_del_clicked();

    void on_comboBox_inside_list_currentIndexChanged(int index);

    void on_pushButton_inside_add_clicked();

    void on_pushButton_inside_del_clicked();
    //外部缺陷标定结果计算
    void on_pushButton_outside_stand_clicked();
    // 外部缺陷标定保存
    void on_pushButton_outside_stand_save_clicked();
    // 内部缺陷结果保存
    void on_pushButton_inside_stand_save_clicked();
    // 内部缺陷结果导入
    void on_pushButton_inside_import_clicked();
    // 外部缺陷结果保存
    void on_pushButton_outside_import_clicked();

signals:
    void update_inside_detection_list(QMap<QString,InsideDetectParam>& inside_list);
    void update_outside_detection_list(QMap<QString,OutsideDetectParam>& out_list);
    void update_function_result(std::pair<double, double>& result_param);
private:
    // 保存标定结果 outside==true默认外部缺陷保存
    bool saveSetting(QString dir,bool outside = true);
    // 导入标定结果
    bool importSetting(QString dir,bool outside = true);
private:
    Ui::CalibrateView *ui;
    QMap<QString,OutsideDetectParam> cfg_detection_outside_list_;
    QMap<QString,InsideDetectParam> cfg_detection_inside_list_; // 内部缺陷直接用当前标定当量表示
    std::pair<double, double> result_param_{0,0};
    //标定结果的线性函数：y=ax+b,result_param_.first=x,result_param_.second=y
    // x表示深宽比 ，y 表示幅值
//    std::function<void(QVector<QPointF>&)> getDetectRectData_Func_;
};

#endif // CALIBRATEVIEW_H
