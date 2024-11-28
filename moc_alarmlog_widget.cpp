/****************************************************************************
** Meta object code from reading C++ file 'alarmlog_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "alarmlog_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'alarmlog_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_alarmLog_widget_t {
    QByteArrayData data[24];
    char stringdata0[371];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_alarmLog_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_alarmLog_widget_t qt_meta_stringdata_alarmLog_widget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "alarmLog_widget"
QT_MOC_LITERAL(1, 16, 11), // "eventFilter"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "QEvent*"
QT_MOC_LITERAL(4, 37, 12), // "callKeyBoard"
QT_MOC_LITERAL(5, 50, 10), // "QLineEdit*"
QT_MOC_LITERAL(6, 61, 1), // "a"
QT_MOC_LITERAL(7, 63, 20), // "alarmlog_button_init"
QT_MOC_LITERAL(8, 84, 12), // "QPushButton*"
QT_MOC_LITERAL(9, 97, 11), // "button_init"
QT_MOC_LITERAL(10, 109, 10), // "changedata"
QT_MOC_LITERAL(11, 120, 15), // "excel_load_5min"
QT_MOC_LITERAL(12, 136, 9), // "tableName"
QT_MOC_LITERAL(13, 146, 11), // "QTableView*"
QT_MOC_LITERAL(14, 158, 9), // "tableview"
QT_MOC_LITERAL(15, 168, 10), // "data_time1"
QT_MOC_LITERAL(16, 179, 10), // "data_time2"
QT_MOC_LITERAL(17, 190, 31), // "on_tab_button_timestart_clicked"
QT_MOC_LITERAL(18, 222, 31), // "on_tab_button_determine_clicked"
QT_MOC_LITERAL(19, 254, 25), // "on_pushButton_log_clicked"
QT_MOC_LITERAL(20, 280, 31), // "on_pushButton_log_clear_clicked"
QT_MOC_LITERAL(21, 312, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(22, 334, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(23, 366, 4) // "arg1"

    },
    "alarmLog_widget\0eventFilter\0\0QEvent*\0"
    "callKeyBoard\0QLineEdit*\0a\0"
    "alarmlog_button_init\0QPushButton*\0"
    "button_init\0changedata\0excel_load_5min\0"
    "tableName\0QTableView*\0tableview\0"
    "data_time1\0data_time2\0"
    "on_tab_button_timestart_clicked\0"
    "on_tab_button_determine_clicked\0"
    "on_pushButton_log_clicked\0"
    "on_pushButton_log_clear_clicked\0"
    "on_pushButton_clicked\0"
    "on_comboBox_currentIndexChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_alarmLog_widget[] = {

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
       1,    2,   69,    2, 0x08 /* Private */,
       4,    1,   74,    2, 0x08 /* Private */,
       7,    1,   77,    2, 0x08 /* Private */,
      10,    0,   80,    2, 0x08 /* Private */,
      11,    4,   81,    2, 0x08 /* Private */,
      17,    0,   90,    2, 0x08 /* Private */,
      18,    0,   91,    2, 0x08 /* Private */,
      19,    0,   92,    2, 0x08 /* Private */,
      20,    0,   93,    2, 0x08 /* Private */,
      21,    0,   94,    2, 0x08 /* Private */,
      22,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13, QMetaType::QString, QMetaType::QString,   12,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void alarmLog_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<alarmLog_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->callKeyBoard((*reinterpret_cast< QLineEdit*(*)>(_a[1]))); break;
        case 2: _t->alarmlog_button_init((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 3: _t->changedata(); break;
        case 4: _t->excel_load_5min((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QTableView*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 5: _t->on_tab_button_timestart_clicked(); break;
        case 6: _t->on_tab_button_determine_clicked(); break;
        case 7: _t->on_pushButton_log_clicked(); break;
        case 8: _t->on_pushButton_log_clear_clicked(); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLineEdit* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPushButton* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableView* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject alarmLog_widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_alarmLog_widget.data,
    qt_meta_data_alarmLog_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *alarmLog_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *alarmLog_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_alarmLog_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int alarmLog_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
