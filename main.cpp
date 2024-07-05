#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
#include <QMetaType>
#include "UnitData.h"
#include "DetectSettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册ChinnelData类型
    qRegisterMetaType<QVector<ChinnelData>>();
//    qRegisterMetaType<QVector<ChinnelData>&>();
    qRegisterMetaType<ChinnelMagData>();

    a.setApplicationName("弱磁检测软件");//设置应用程序名
    a.setWindowIcon(QIcon("res:/source/res/title.icon"));
    if(!DetectSettings::instance().initSettings())
    {
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
