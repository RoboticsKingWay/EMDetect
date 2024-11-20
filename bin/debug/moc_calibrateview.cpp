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
    QByteArrayData data[26];
    char stringdata0[683];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalibrateView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalibrateView_t qt_meta_stringdata_CalibrateView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CalibrateView"
QT_MOC_LITERAL(1, 14, 28), // "update_inside_detection_list"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 32), // "QMap<QString,InsideDetectParam>&"
QT_MOC_LITERAL(4, 77, 11), // "inside_list"
QT_MOC_LITERAL(5, 89, 29), // "update_outside_detection_list"
QT_MOC_LITERAL(6, 119, 33), // "QMap<QString,OutsideDetectPar..."
QT_MOC_LITERAL(7, 153, 8), // "out_list"
QT_MOC_LITERAL(8, 162, 22), // "update_function_result"
QT_MOC_LITERAL(9, 185, 25), // "std::pair<double,double>&"
QT_MOC_LITERAL(10, 211, 12), // "result_param"
QT_MOC_LITERAL(11, 224, 14), // "on_GetRectData"
QT_MOC_LITERAL(12, 239, 17), // "QVector<QPointF>&"
QT_MOC_LITERAL(13, 257, 6), // "points"
QT_MOC_LITERAL(14, 264, 44), // "on_comboBox_outside_list_curr..."
QT_MOC_LITERAL(15, 309, 5), // "index"
QT_MOC_LITERAL(16, 315, 33), // "on_pushButton_outside_add_cli..."
QT_MOC_LITERAL(17, 349, 33), // "on_pushButton_outside_del_cli..."
QT_MOC_LITERAL(18, 383, 43), // "on_comboBox_inside_list_curre..."
QT_MOC_LITERAL(19, 427, 32), // "on_pushButton_inside_add_clicked"
QT_MOC_LITERAL(20, 460, 32), // "on_pushButton_inside_del_clicked"
QT_MOC_LITERAL(21, 493, 35), // "on_pushButton_outside_stand_c..."
QT_MOC_LITERAL(22, 529, 40), // "on_pushButton_outside_stand_s..."
QT_MOC_LITERAL(23, 570, 39), // "on_pushButton_inside_stand_sa..."
QT_MOC_LITERAL(24, 610, 35), // "on_pushButton_inside_import_c..."
QT_MOC_LITERAL(25, 646, 36) // "on_pushButton_outside_import_..."

    },
    "CalibrateView\0update_inside_detection_list\0"
    "\0QMap<QString,InsideDetectParam>&\0"
    "inside_list\0update_outside_detection_list\0"
    "QMap<QString,OutsideDetectParam>&\0"
    "out_list\0update_function_result\0"
    "std::pair<double,double>&\0result_param\0"
    "on_GetRectData\0QVector<QPointF>&\0"
    "points\0on_comboBox_outside_list_currentIndexChanged\0"
    "index\0on_pushButton_outside_add_clicked\0"
    "on_pushButton_outside_del_clicked\0"
    "on_comboBox_inside_list_currentIndexChanged\0"
    "on_pushButton_inside_add_clicked\0"
    "on_pushButton_inside_del_clicked\0"
    "on_pushButton_outside_stand_clicked\0"
    "on_pushButton_outside_stand_save_clicked\0"
    "on_pushButton_inside_stand_save_clicked\0"
    "on_pushButton_inside_import_clicked\0"
    "on_pushButton_outside_import_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalibrateView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    1,   92,    2, 0x06 /* Public */,
       8,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   98,    2, 0x0a /* Public */,
      14,    1,  101,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    1,  106,    2, 0x08 /* Private */,
      19,    0,  109,    2, 0x08 /* Private */,
      20,    0,  110,    2, 0x08 /* Private */,
      21,    0,  111,    2, 0x08 /* Private */,
      22,    0,  112,    2, 0x08 /* Private */,
      23,    0,  113,    2, 0x08 /* Private */,
      24,    0,  114,    2, 0x08 /* Private */,
      25,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
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
        case 0: _t->update_inside_detection_list((*reinterpret_cast< QMap<QString,InsideDetectParam>(*)>(_a[1]))); break;
        case 1: _t->update_outside_detection_list((*reinterpret_cast< QMap<QString,OutsideDetectParam>(*)>(_a[1]))); break;
        case 2: _t->update_function_result((*reinterpret_cast< std::pair<double,double>(*)>(_a[1]))); break;
        case 3: _t->on_GetRectData((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        case 4: _t->on_comboBox_outside_list_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_outside_add_clicked(); break;
        case 6: _t->on_pushButton_outside_del_clicked(); break;
        case 7: _t->on_comboBox_inside_list_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_inside_add_clicked(); break;
        case 9: _t->on_pushButton_inside_del_clicked(); break;
        case 10: _t->on_pushButton_outside_stand_clicked(); break;
        case 11: _t->on_pushButton_outside_stand_save_clicked(); break;
        case 12: _t->on_pushButton_inside_stand_save_clicked(); break;
        case 13: _t->on_pushButton_inside_import_clicked(); break;
        case 14: _t->on_pushButton_outside_import_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CalibrateView::*)(QMap<QString,InsideDetectParam> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrateView::update_inside_detection_list)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CalibrateView::*)(QMap<QString,OutsideDetectParam> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrateView::update_outside_detection_list)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CalibrateView::*)(std::pair<double,double> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrateView::update_function_result)) {
                *result = 2;
                return;
            }
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CalibrateView::update_inside_detection_list(QMap<QString,InsideDetectParam> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalibrateView::update_outside_detection_list(QMap<QString,OutsideDetectParam> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalibrateView::update_function_result(std::pair<double,double> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
