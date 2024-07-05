#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include "setupwindow.h"
#include "SerialPortManager.h"
#include "RealTimeChartView.h"
#include "imageview.h"
#include "ImageViewNew.h"
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
    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_SerialSetup_clicked();

private:
    void getImageColor();
    void drawImage(bool is_update);
    void picContour(QPainter& painter,bool is_update = false);
    void Contourf(long intM, long intN, double Xmax, double Ymax,QPainter& painter);
    void draw_Depth_Image();
    void calcDetectData();
    void drawFileView();
    void drawImageView();
    void drawImageViewNew();
    void drawImageViewThread();
private:
    Ui::MainWindow *ui {nullptr};
    RealTimeChartView* chartview_ptr_ {nullptr};
    SourceView* source_view_ptr_ {nullptr};
//    ImageView* image_view_ptr_ {nullptr}; // 暂时不用在主页绘制图像
//    ImageViewNew* image_view_new_ptr_ {nullptr}; // 暂时不用在主页绘制图像
    SetupWindow* setup_win_ptr_ {nullptr};

    QTimer timer_;
    QTimer timer_draw_total_;
    int count_size_blk_;
    SerialPortManager* manager_ptr_ {nullptr};//串口操作类指针
    DataManager* data_manager_ptr_ {nullptr};
    bool is_chinnel_on_ [CH_NUM] = {false};
    QVector<ChinnelData> list_draw_src_data_;
    QVector<ChinnelData> list_draw_file_data_;
    int action_state_ {E_ACTION_STOP};//操作初始状态

    std::shared_ptr<std::thread> thread_calc_ptr_ {nullptr}; // 检测结果计算线程
    bool is_calc_thread_start_ {true};
    bool is_calc_start_ {false};

    // 绘制云图需要的参数
    QImage bit_map_;
    int width_;
    int height_;
    double max_data_ {0};
    double min_data_ {0};
    double scan_length_{20}; // mm
    double sensitivity_{0.0};
    QVector<QColor> yellowGradient_;
    std::vector<std::vector<double>> draw_image_data_;    // 差分计算得到的结果数据,距离数据
    QMutex mutex_image_;

};
#endif // MAINWINDOW_H
