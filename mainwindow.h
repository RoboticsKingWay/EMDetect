#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include "setupwindow.h"
#include "SerialPortManager.h"
#include "RealTimeChartView.h"
#include "imageview.h"
#include "sourceview.h"
#include "gradientview.h"
#include "QXlsxExcelHelper.h"
#include "DataManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateData();

protected:

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event)override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_action_serial_triggered();

    void on_action_save_triggered();

    void on_action_saveas_triggered();

    void on_action_setup_other_triggered();

    void on_tabWidget_tabBarClicked(int index);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void onOpenExcelClicked();
private:
    void draw_Depth_Image();
    int magnetic_Convert_Depth();
private:
    Ui::MainWindow *ui {nullptr};
    RealTimeChartView* chartview_ptr_ {nullptr};
    SourceView* source_view_ptr_ {nullptr};
    GradientView* gradient_view_ptr_ {nullptr};
    ImageView* image_view_ptr_ {nullptr};
    SetupWindow* setup_win_ptr_ {nullptr};

    QTimer timer_;
    SerialPortManager* manager_ptr_ {nullptr};
    DataManager* data_manager_ptr_ {nullptr};
    bool is_chinnel_on_ [CH_NUM] = {false};
    QVector<ChinnelData> list_draw_src_data_;
    int action_state_ {E_ACTION_ST};//{E_ACTION_INVAL};
};
#endif // MAINWINDOW_H
