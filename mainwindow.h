#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <condition_variable>
#include "setupwindow.h"
#include "calibrateview.h"
#include "SerialPortManager.h"
#include "RealTimeChartView.h"
#include "sourceview.h"
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
public slots:
    void on_auto_FitDirect(double rad);
    void on_manve_Fit(QPointF center, double rad);
    void on_getRectPoints();
    void on_butterfly_Filter(int more,int less,int axes);
protected:
    void closeEvent(QCloseEvent *event) override;
//    void resizeEvent(QResizeEvent *event) override;
//    void paintEvent(QPaintEvent *event)override;
//    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onSerialState(int state);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

//    void on_pushButton_SerialSetup_clicked();
    void on_checkBox_upline_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_action_serialSetup_triggered();

    void on_action_thresholdSetup_triggered();

    void on_action_outside_triggered();

    void on_action_inside_triggered();

    void on_action_filesave_triggered();

    void on_pushButton_5_clicked();

    void on_action_fileperview_triggered();

    void on_action_fit_circle_triggered();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_filter_clicked();

    void on_action_filter_triggered();

signals:

private:
    void setPushButtonEnable(int state); //
    void drawFileView();
    void drawImageViewThread();
    void runThread();
private:
    Ui::MainWindow *ui {nullptr};
    RealTimeChartView* chartview_ptr_ {nullptr};
    SourceView* source_view_ptr_ {nullptr};
    SetupWindow* setup_win_ptr_ {nullptr};
    CalibrateView* calibrate_view_ {nullptr};

    QTimer timer_;
    QTimer timer_draw_total_;
    int count_size_blk_;
    SerialPortManager* manager_ptr_ {nullptr};//串口操作类指针
    DataManager* data_manager_ptr_ {nullptr};
    QVector<ChinnelData> list_draw_src_data_;
    QVector<QPointF> rect_data_list_; // 特征区域的数据
//    QVector<ChinnelData> list_fitted_data_; // 拟合圆数据
    int action_state_ {E_ACTION_STOP};//操作初始状态

    std::shared_ptr<std::thread> thread_calc_ptr_ {nullptr}; // 检测结果计算线程
    bool is_calc_thread_start_ {true};
    bool is_calc_start_ {false};
    std::condition_variable wait_event_;
    std::mutex wait_mutex_;

    double scan_length_{20}; // mm
    double sensitivity_{0.0};
    QVector<QColor> yellowGradient_;
    std::vector<std::vector<double>> draw_image_data_;    // 差分计算得到的结果数据,距离数据

    // test
//    DynamicFilter* filter_ptr_ {nullptr};
};
#endif // MAINWINDOW_H
