/****************************************************************************
** Meta object code from reading C++ file 'RealTimeChartView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RealTimeChartView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RealTimeChartView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RealTimeChartView_t {
    QByteArrayData data[18];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RealTimeChartView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RealTimeChartView_t qt_meta_stringdata_RealTimeChartView = {
    {
QT_MOC_LITERAL(0, 0, 17), // "RealTimeChartView"
QT_MOC_LITERAL(1, 18, 8), // "rectData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "QVector<QPointF>&"
QT_MOC_LITERAL(4, 46, 9), // "rect_data"
QT_MOC_LITERAL(5, 56, 13), // "on_uplinePlus"
QT_MOC_LITERAL(6, 70, 11), // "on_uplineDe"
QT_MOC_LITERAL(7, 82, 15), // "on_uplineMoveto"
QT_MOC_LITERAL(8, 98, 4), // "y_to"
QT_MOC_LITERAL(9, 103, 14), // "on_uplineReset"
QT_MOC_LITERAL(10, 118, 15), // "on_downlinePlus"
QT_MOC_LITERAL(11, 134, 13), // "on_downlineDe"
QT_MOC_LITERAL(12, 148, 17), // "on_downlineMoveto"
QT_MOC_LITERAL(13, 166, 16), // "on_downlineReset"
QT_MOC_LITERAL(14, 183, 12), // "onSelectRect"
QT_MOC_LITERAL(15, 196, 5), // "start"
QT_MOC_LITERAL(16, 202, 3), // "end"
QT_MOC_LITERAL(17, 206, 12) // "resetSerials"

    },
    "RealTimeChartView\0rectData\0\0"
    "QVector<QPointF>&\0rect_data\0on_uplinePlus\0"
    "on_uplineDe\0on_uplineMoveto\0y_to\0"
    "on_uplineReset\0on_downlinePlus\0"
    "on_downlineDe\0on_downlineMoveto\0"
    "on_downlineReset\0onSelectRect\0start\0"
    "end\0resetSerials"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RealTimeChartView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    1,   74,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,
      14,    2,   84,    2, 0x0a /* Public */,
      17,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF, QMetaType::QPointF,   15,   16,
    QMetaType::Void,

       0        // eod
};

void RealTimeChartView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RealTimeChartView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rectData((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 1: _t->on_uplinePlus(); break;
        case 2: _t->on_uplineDe(); break;
        case 3: _t->on_uplineMoveto((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_uplineReset(); break;
        case 5: _t->on_downlinePlus(); break;
        case 6: _t->on_downlineDe(); break;
        case 7: _t->on_downlineMoveto((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_downlineReset(); break;
        case 9: _t->onSelectRect((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 10: _t->resetSerials(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RealTimeChartView::*)(QVector<QPointF> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RealTimeChartView::rectData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RealTimeChartView::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseView::staticMetaObject>(),
    qt_meta_stringdata_RealTimeChartView.data,
    qt_meta_data_RealTimeChartView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RealTimeChartView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RealTimeChartView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RealTimeChartView.stringdata0))
        return static_cast<void*>(this);
    return BaseView::qt_metacast(_clname);
}

int RealTimeChartView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void RealTimeChartView::rectData(QVector<QPointF> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
