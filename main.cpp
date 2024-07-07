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

//    QApplication::setApplicationName("弱磁检测软件");//设置应用程序名
//    QApplication::setWindowIcon(QIcon("res:/appicon"));
    if(!DetectSettings::instance().initSettings())
    {
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
