/****************************************************************************
** Meta object code from reading C++ file 'mian_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mian_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mian_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mian_widget_t {
    QByteArrayData data[12];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mian_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mian_widget_t qt_meta_stringdata_mian_widget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mian_widget"
QT_MOC_LITERAL(1, 12, 15), // "refresh_timeout"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "serial_send"
QT_MOC_LITERAL(4, 41, 30), // "on_checkBox_DYC_1_stateChanged"
QT_MOC_LITERAL(5, 72, 4), // "arg1"
QT_MOC_LITERAL(6, 77, 30), // "on_checkBox_DYC_2_stateChanged"
QT_MOC_LITERAL(7, 108, 30), // "on_checkBox_DYC_3_stateChanged"
QT_MOC_LITERAL(8, 139, 30), // "on_checkBox_DYC_4_stateChanged"
QT_MOC_LITERAL(9, 170, 28), // "on_checkBox_DO1_stateChanged"
QT_MOC_LITERAL(10, 199, 28), // "on_checkBox_DO2_stateChanged"
QT_MOC_LITERAL(11, 228, 28) // "on_checkBox_DO3_stateChanged"

    },
    "mian_widget\0refresh_timeout\0\0serial_send\0"
    "on_checkBox_DYC_1_stateChanged\0arg1\0"
    "on_checkBox_DYC_2_stateChanged\0"
    "on_checkBox_DYC_3_stateChanged\0"
    "on_checkBox_DYC_4_stateChanged\0"
    "on_checkBox_DO1_stateChanged\0"
    "on_checkBox_DO2_stateChanged\0"
    "on_checkBox_DO3_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mian_widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    1,   61,    2, 0x08 /* Private */,
       6,    1,   64,    2, 0x08 /* Private */,
       7,    1,   67,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
       9,    1,   73,    2, 0x08 /* Private */,
      10,    1,   76,    2, 0x08 /* Private */,
      11,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void mian_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mian_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh_timeout(); break;
        case 1: _t->serial_send(); break;
        case 2: _t->on_checkBox_DYC_1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_checkBox_DYC_2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_DYC_3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_checkBox_DYC_4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_checkBox_DO1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_checkBox_DO2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_checkBox_DO3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mian_widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_mian_widget.data,
    qt_meta_data_mian_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mian_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mian_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mian_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int mian_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
