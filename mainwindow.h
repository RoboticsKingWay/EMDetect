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
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 定时器读取串口数据
    void updateData();
public slots:
    // 自动拟合圆
    void on_auto_FitDirect(double rad);
    // 手动拟合圆
    void on_manve_Fit(QPointF center, double rad);
    // 俘获特征区域
    void on_getRectPoints(int channel_id);
    // 蝶形图滤波
    void on_butterfly_Filter(int more,int less,int axes);
    // 软件关闭事件
    void closeEvent(QCloseEvent *event) override;

    // 串口状态
    void onSerialState(int state);
    // 弃用通道选择框
    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);
    // 开始采集 和 结束采集
    void on_pushButton_clicked();
    // 数据处理
    void on_pushButton_3_clicked();
    // 数据预览
    void on_pushButton_4_clicked();
    // 数据默认保存在程序路径下 data文件夹，并以时间戳保存,另存数据
    void on_pushButton_2_clicked();
    // 弃用阈值线
    void on_checkBox_upline_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);
    // 选择串口设置
    void on_action_serialSetup_triggered();
    // 选择上下阈值线设置
    void on_action_thresholdSetup_triggered();
    // 标定
    void on_action_outside_triggered();

    void on_action_inside_triggered();
    // 文件另存
    void on_action_filesave_triggered();
    // 选择框 特征区域选择
    void on_pushButton_5_clicked();
    void on_pushButton_detect_area2_clicked();
    // 文件预览
    void on_action_fileperview_triggered();
    // 拟合圆设置
    void on_action_fit_circle_triggered();
    // 滤波设置
    void on_action_filter_triggered();

    // 标定结果 通知主界面
    void on_update_inside_detection_list(QMap<QString,InsideDetectParam>& inside_list);
    void on_update_outside_detection_list(QMap<QString,OutsideDetectParam>& out_list);
    void on_update_function_result(std::pair<double, double>& result_param);
    // 内部缺陷当量匹配，默认选择外部缺陷结果处理
    void on_comboBox_2_currentIndexChanged(int index);
    // 磁激励设置
    void on_action_magstimulate_triggered();
    void onDrawData(QVector<ChinnelData> data);
private:
    void setPushButtonEnable(int state); //
    void drawFileView();
    void drawImageViewThread();
    void runThread();
private:
    Ui::MainWindow *ui {nullptr};
    RealTimeChartView* chartview_ptr_ {nullptr};  //实时扫查图像实例
    RealTimeChartView* chartview_ptr_2_ {nullptr};  //实时扫查图像实例
    SourceView* source_view_ptr_ {nullptr};       // 蝶形图功能实例
    SetupWindow* setup_win_ptr_ {nullptr};        // 软件设置子窗口
    CalibrateView* calibrate_view_ {nullptr};     //标定功能子窗口
    Widget* mag_widget_ptr_{nullptr};             // 磁激励功能子窗口

    QTimer timer_;                                //扫查实时图定时器  周期绘制图像
    QTimer timer_draw_total_;                     //预览文件定时器 周期绘制图像
    int count_size_blk_;
    SerialPortManager* manager_ptr_ {nullptr};    //扫查串口操作类指针
    DataManager* data_manager_ptr_ {nullptr};     //数据管理类操作execl表格
    QVector<ChinnelData> list_draw_src_data_;     //一次扫查启动到停止过程中读取到的数据并暂存后续数据处理，
                                                  // 数据预览也暂存在该结构中
    QVector<QPointF> rect_data_list_;             // 待处理分析的特征区域的数据
//    QVector<ChinnelData> list_fitted_data_; // 拟合圆数据
    int action_state_ {E_ACTION_STOP};            //操作初始状态

    std::shared_ptr<std::thread> thread_calc_ptr_ {nullptr}; // 检测结果计算线程
    bool is_calc_thread_start_ {true};
    bool is_calc_start_ {false};

    double scan_length_{20}; // mm
    double sensitivity_{0.0};
    //
    double y_max_am_; // 选中缺陷幅值
    // test
//    DynamicFilter* filter_ptr_ {nullptr};
    QThread* thread_ptr_;
};
#endif // MAINWINDOW_H
