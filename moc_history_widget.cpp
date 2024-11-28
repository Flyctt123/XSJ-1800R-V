/****************************************************************************
** Meta object code from reading C++ file 'history_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "history_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'history_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_history_widget_t {
    QByteArrayData data[20];
    char stringdata0[436];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_history_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_history_widget_t qt_meta_stringdata_history_widget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "history_widget"
QT_MOC_LITERAL(1, 15, 19), // "history_button_init"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "QPushButton*"
QT_MOC_LITERAL(4, 49, 11), // "button_init"
QT_MOC_LITERAL(5, 61, 10), // "changedata"
QT_MOC_LITERAL(6, 72, 15), // "excel_load_5min"
QT_MOC_LITERAL(7, 88, 9), // "tableName"
QT_MOC_LITERAL(8, 98, 11), // "QTableView*"
QT_MOC_LITERAL(9, 110, 9), // "tableview"
QT_MOC_LITERAL(10, 120, 10), // "data_time1"
QT_MOC_LITERAL(11, 131, 10), // "data_time2"
QT_MOC_LITERAL(12, 142, 33), // "on_button_water_timestart_cli..."
QT_MOC_LITERAL(13, 176, 38), // "on_button_flow_speed_timestar..."
QT_MOC_LITERAL(14, 215, 36), // "on_button_flow_now_timestart_..."
QT_MOC_LITERAL(15, 252, 36), // "on_button_rain_now_timestart_..."
QT_MOC_LITERAL(16, 289, 33), // "on_button_water_determine_cli..."
QT_MOC_LITERAL(17, 323, 36), // "on_button_rain_now_determine_..."
QT_MOC_LITERAL(18, 360, 38), // "on_button_flow_speed_determin..."
QT_MOC_LITERAL(19, 399, 36) // "on_button_flow_now_determine_..."

    },
    "history_widget\0history_button_init\0\0"
    "QPushButton*\0button_init\0changedata\0"
    "excel_load_5min\0tableName\0QTableView*\0"
    "tableview\0data_time1\0data_time2\0"
    "on_button_water_timestart_clicked\0"
    "on_button_flow_speed_timestart_clicked\0"
    "on_button_flow_now_timestart_clicked\0"
    "on_button_rain_now_timestart_clicked\0"
    "on_button_water_determine_clicked\0"
    "on_button_rain_now_determine_clicked\0"
    "on_button_flow_speed_determine_clicked\0"
    "on_button_flow_now_determine_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_history_widget[] = {

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
       1,    1,   69,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    4,   73,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,
      16,    0,   86,    2, 0x08 /* Private */,
      17,    0,   87,    2, 0x08 /* Private */,
      18,    0,   88,    2, 0x08 /* Private */,
      19,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8, QMetaType::QString, QMetaType::QString,    7,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void history_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<history_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->history_button_init((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 1: _t->changedata(); break;
        case 2: _t->excel_load_5min((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTableView*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->on_button_water_timestart_clicked(); break;
        case 4: _t->on_button_flow_speed_timestart_clicked(); break;
        case 5: _t->on_button_flow_now_timestart_clicked(); break;
        case 6: _t->on_button_rain_now_timestart_clicked(); break;
        case 7: _t->on_button_water_determine_clicked(); break;
        case 8: _t->on_button_rain_now_determine_clicked(); break;
        case 9: _t->on_button_flow_speed_determine_clicked(); break;
        case 10: _t->on_button_flow_now_determine_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPushButton* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableView* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject history_widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_history_widget.data,
    qt_meta_data_history_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *history_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *history_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_history_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int history_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
