#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QTabWidget>
#include "UnitData.h"

namespace Ui {
class SetupWindow;
}

class SetupWindow : public QTabWidget
{
    Q_OBJECT

public:
    explicit SetupWindow(QWidget *parent = nullptr);
    ~SetupWindow();

public slots:
    void setPortList(QVector<QString>& list, int action);
signals:
    void setSerialParam(SerialParam& param);
    void uplinePlus();
    void uplineDe();
    void uplineMoveto(double y_to);
    void uplineReset();
    void downlinePlus();
    void downlineDe();
    void downlineMoveto(double y_to);
    void downlineReset();
    void autoDirectFit(double rad);
    void manve_Fit(QPointF center, double rad);
    void butterfly_filter(int more_than,int less_than,int axes);
private slots:

    void on_pushButton_sure_clicked();

    void on_pushButton_cancel_clicked();
    void on_pushButton_uplineplus_clicked();

    void on_pushButton_uplinede_clicked();

    void on_pushButton_uplinesure_clicked();

    void on_pushButton_uplinereset_clicked();

    void on_pushButton_downlineplus_clicked();

    void on_pushButton_downlinede_clicked();

    void on_pushButton_downlinesure_clicked();

    void on_pushButton_downlinereset_clicked();

    void on_pushButton_circle_direct_clicked();

    void on_pushButton_circle_input_clicked();

    void on_pushButton_filter_clicked();

    void on_pushButton_filter_cancle_clicked();

private:
    Ui::SetupWindow *ui;
};

#endif // SETUPWINDOW_H
