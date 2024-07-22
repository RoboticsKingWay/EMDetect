QT       += core gui charts serialport axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#RC_ICONS += source/res/title.icon
include(./src/xlsx/qtxlsx.pri)
SOURCES += \
    calibrateview.cpp \
    main.cpp \
    mainwindow.cpp\
    setupwindow.cpp

HEADERS += \
    Chasing.h \
    DataManager.h \
    DetectSettings.h \
    QXlsxExcelHelper.h \
    RealTimeChartView.h \
    SafeQueue.h \
    SerialPortManager.h \
    UnitCalc.h \
    UnitData.h \
    ZoomableChartView.h \
    calc/CFunction.h \
    calc/Chasing.h \
    calc/SPLine.h \
    calibrateview.h \
    mainwindow.h\
    setupwindow.h \
    sourceview.h

FORMS += \
    calibrateview.ui \
    mainwindow.ui \
    setupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

#DISTFILES += \
#    src/xlsx/qtxlsx.pri

DISTFILES += \
    bin/config/detect.ini \
    release/release/config/detect.ini
