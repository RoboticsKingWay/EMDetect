/****************************************************************************
** Meta object code from reading C++ file 'calibrateview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../calibrateview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrateview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalibrateView_t {
    QByteArrayData data[16];
    char stringdata0[436];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalibrateView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalibrateView_t qt_meta_stringdata_CalibrateView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CalibrateView"
QT_MOC_LITERAL(1, 14, 14), // "on_GetRectData"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "QVector<QPointF>&"
QT_MOC_LITERAL(4, 48, 6), // "points"
QT_MOC_LITERAL(5, 55, 44), // "on_comboBox_outside_list_curr..."
QT_MOC_LITERAL(6, 100, 5), // "index"
QT_MOC_LITERAL(7, 106, 33), // "on_pushButton_outside_add_cli..."
QT_MOC_LITERAL(8, 140, 33), // "on_pushButton_outside_del_cli..."
QT_MOC_LITERAL(9, 174, 43), // "on_comboBox_inside_list_curre..."
QT_MOC_LITERAL(10, 218, 32), // "on_pushButton_inside_add_clicked"
QT_MOC_LITERAL(11, 251, 32), // "on_pushButton_inside_del_clicked"
QT_MOC_LITERAL(12, 284, 35), // "on_pushButton_outside_stand_c..."
QT_MOC_LITERAL(13, 320, 34), // "on_pushButton_inside_stand_cl..."
QT_MOC_LITERAL(14, 355, 40), // "on_pushButton_outside_stand_s..."
QT_MOC_LITERAL(15, 396, 39) // "on_pushButton_inside_stand_sa..."

    },
    "CalibrateView\0on_GetRectData\0\0"
    "QVector<QPointF>&\0points\0"
    "on_comboBox_outside_list_currentIndexChanged\0"
    "index\0on_pushButton_outside_add_clicked\0"
    "on_pushButton_outside_del_clicked\0"
    "on_comboBox_inside_list_currentIndexChanged\0"
    "on_pushButton_inside_add_clicked\0"
    "on_pushButton_inside_del_clicked\0"
    "on_pushButton_outside_stand_clicked\0"
    "on_pushButton_inside_stand_clicked\0"
    "on_pushButton_outside_stand_save_clicked\0"
    "on_pushButton_inside_stand_save_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalibrateView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       5,    1,   72,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      10,    0,   80,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CalibrateView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CalibrateView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_GetRectData((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 1: _t->on_comboBox_outside_list_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_outside_add_clicked(); break;
        case 3: _t->on_pushButton_outside_del_clicked(); break;
        case 4: _t->on_comboBox_inside_list_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_inside_add_clicked(); break;
        case 6: _t->on_pushButton_inside_del_clicked(); break;
        case 7: _t->on_pushButton_outside_stand_clicked(); break;
        case 8: _t->on_pushButton_inside_stand_clicked(); break;
        case 9: _t->on_pushButton_outside_stand_save_clicked(); break;
        case 10: _t->on_pushButton_inside_stand_save_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CalibrateView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTabWidget::staticMetaObject>(),
    qt_meta_stringdata_CalibrateView.data,
    qt_meta_data_CalibrateView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CalibrateView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalibrateView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalibrateView.stringdata0))
        return static_cast<void*>(this);
    return QTabWidget::qt_metacast(_clname);
}

int CalibrateView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE