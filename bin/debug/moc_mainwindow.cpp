/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[43];
    char stringdata0[898];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "on_auto_FitDirect"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "rad"
QT_MOC_LITERAL(4, 34, 12), // "on_manve_Fit"
QT_MOC_LITERAL(5, 47, 6), // "center"
QT_MOC_LITERAL(6, 54, 16), // "on_getRectPoints"
QT_MOC_LITERAL(7, 71, 19), // "on_butterfly_Filter"
QT_MOC_LITERAL(8, 91, 4), // "more"
QT_MOC_LITERAL(9, 96, 4), // "less"
QT_MOC_LITERAL(10, 101, 4), // "axes"
QT_MOC_LITERAL(11, 106, 13), // "onSerialState"
QT_MOC_LITERAL(12, 120, 5), // "state"
QT_MOC_LITERAL(13, 126, 26), // "on_checkBox_2_stateChanged"
QT_MOC_LITERAL(14, 153, 4), // "arg1"
QT_MOC_LITERAL(15, 158, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(16, 183, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(17, 205, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(18, 229, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(19, 253, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(20, 277, 23), // "on_lineEdit_textChanged"
QT_MOC_LITERAL(21, 301, 31), // "on_checkBox_upline_stateChanged"
QT_MOC_LITERAL(22, 333, 26), // "on_checkBox_3_stateChanged"
QT_MOC_LITERAL(23, 360, 31), // "on_action_serialSetup_triggered"
QT_MOC_LITERAL(24, 392, 34), // "on_action_thresholdSetup_trig..."
QT_MOC_LITERAL(25, 427, 27), // "on_action_outside_triggered"
QT_MOC_LITERAL(26, 455, 26), // "on_action_inside_triggered"
QT_MOC_LITERAL(27, 482, 28), // "on_action_filesave_triggered"
QT_MOC_LITERAL(28, 511, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(29, 535, 31), // "on_action_fileperview_triggered"
QT_MOC_LITERAL(30, 567, 30), // "on_action_fit_circle_triggered"
QT_MOC_LITERAL(31, 598, 25), // "on_lineEdit_2_textChanged"
QT_MOC_LITERAL(32, 624, 28), // "on_pushButton_filter_clicked"
QT_MOC_LITERAL(33, 653, 26), // "on_action_filter_triggered"
QT_MOC_LITERAL(34, 680, 31), // "on_update_inside_detection_list"
QT_MOC_LITERAL(35, 712, 32), // "QMap<QString,InsideDetectParam>&"
QT_MOC_LITERAL(36, 745, 11), // "inside_list"
QT_MOC_LITERAL(37, 757, 32), // "on_update_outside_detection_list"
QT_MOC_LITERAL(38, 790, 33), // "QMap<QString,OutsideDetectPar..."
QT_MOC_LITERAL(39, 824, 8), // "out_list"
QT_MOC_LITERAL(40, 833, 25), // "on_update_function_result"
QT_MOC_LITERAL(41, 859, 25), // "std::pair<double,double>&"
QT_MOC_LITERAL(42, 885, 12) // "result_param"

    },
    "MainWindow\0on_auto_FitDirect\0\0rad\0"
    "on_manve_Fit\0center\0on_getRectPoints\0"
    "on_butterfly_Filter\0more\0less\0axes\0"
    "onSerialState\0state\0on_checkBox_2_stateChanged\0"
    "arg1\0on_checkBox_stateChanged\0"
    "on_pushButton_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_4_clicked\0on_pushButton_2_clicked\0"
    "on_lineEdit_textChanged\0"
    "on_checkBox_upline_stateChanged\0"
    "on_checkBox_3_stateChanged\0"
    "on_action_serialSetup_triggered\0"
    "on_action_thresholdSetup_triggered\0"
    "on_action_outside_triggered\0"
    "on_action_inside_triggered\0"
    "on_action_filesave_triggered\0"
    "on_pushButton_5_clicked\0"
    "on_action_fileperview_triggered\0"
    "on_action_fit_circle_triggered\0"
    "on_lineEdit_2_textChanged\0"
    "on_pushButton_filter_clicked\0"
    "on_action_filter_triggered\0"
    "on_update_inside_detection_list\0"
    "QMap<QString,InsideDetectParam>&\0"
    "inside_list\0on_update_outside_detection_list\0"
    "QMap<QString,OutsideDetectParam>&\0"
    "out_list\0on_update_function_result\0"
    "std::pair<double,double>&\0result_param"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x0a /* Public */,
       4,    2,  157,    2, 0x0a /* Public */,
       6,    0,  162,    2, 0x0a /* Public */,
       7,    3,  163,    2, 0x0a /* Public */,
      11,    1,  170,    2, 0x08 /* Private */,
      13,    1,  173,    2, 0x08 /* Private */,
      15,    1,  176,    2, 0x08 /* Private */,
      16,    0,  179,    2, 0x08 /* Private */,
      17,    0,  180,    2, 0x08 /* Private */,
      18,    0,  181,    2, 0x08 /* Private */,
      19,    0,  182,    2, 0x08 /* Private */,
      20,    1,  183,    2, 0x08 /* Private */,
      21,    1,  186,    2, 0x08 /* Private */,
      22,    1,  189,    2, 0x08 /* Private */,
      23,    0,  192,    2, 0x08 /* Private */,
      24,    0,  193,    2, 0x08 /* Private */,
      25,    0,  194,    2, 0x08 /* Private */,
      26,    0,  195,    2, 0x08 /* Private */,
      27,    0,  196,    2, 0x08 /* Private */,
      28,    0,  197,    2, 0x08 /* Private */,
      29,    0,  198,    2, 0x08 /* Private */,
      30,    0,  199,    2, 0x08 /* Private */,
      31,    1,  200,    2, 0x08 /* Private */,
      32,    0,  203,    2, 0x08 /* Private */,
      33,    0,  204,    2, 0x08 /* Private */,
      34,    1,  205,    2, 0x08 /* Private */,
      37,    1,  208,    2, 0x08 /* Private */,
      40,    1,  211,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Double,    5,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void, 0x80000000 | 41,   42,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_auto_FitDirect((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->on_manve_Fit((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->on_getRectPoints(); break;
        case 3: _t->on_butterfly_Filter((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->onSerialState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkBox_2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_pushButton_3_clicked(); break;
        case 9: _t->on_pushButton_4_clicked(); break;
        case 10: _t->on_pushButton_2_clicked(); break;
        case 11: _t->on_lineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->on_checkBox_upline_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_checkBox_3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_action_serialSetup_triggered(); break;
        case 15: _t->on_action_thresholdSetup_triggered(); break;
        case 16: _t->on_action_outside_triggered(); break;
        case 17: _t->on_action_inside_triggered(); break;
        case 18: _t->on_action_filesave_triggered(); break;
        case 19: _t->on_pushButton_5_clicked(); break;
        case 20: _t->on_action_fileperview_triggered(); break;
        case 21: _t->on_action_fit_circle_triggered(); break;
        case 22: _t->on_lineEdit_2_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 23: _t->on_pushButton_filter_clicked(); break;
        case 24: _t->on_action_filter_triggered(); break;
        case 25: _t->on_update_inside_detection_list((*reinterpret_cast< QMap<QString,InsideDetectParam>(*)>(_a[1]))); break;
        case 26: _t->on_update_outside_detection_list((*reinterpret_cast< QMap<QString,OutsideDetectParam>(*)>(_a[1]))); break;
        case 27: _t->on_update_function_result((*reinterpret_cast< std::pair<double,double>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
