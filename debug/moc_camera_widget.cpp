/****************************************************************************
** Meta object code from reading C++ file 'camera_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../camera_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_camera_widget_t {
    QByteArrayData data[21];
    char stringdata0[368];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_camera_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_camera_widget_t qt_meta_stringdata_camera_widget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "camera_widget"
QT_MOC_LITERAL(1, 14, 11), // "eventFilter"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "QEvent*"
QT_MOC_LITERAL(4, 35, 12), // "callKeyBoard"
QT_MOC_LITERAL(5, 48, 10), // "QLineEdit*"
QT_MOC_LITERAL(6, 59, 1), // "a"
QT_MOC_LITERAL(7, 61, 16), // "callKeyBoard_ABC"
QT_MOC_LITERAL(8, 78, 18), // "camera_button_init"
QT_MOC_LITERAL(9, 97, 12), // "QPushButton*"
QT_MOC_LITERAL(10, 110, 11), // "button_init"
QT_MOC_LITERAL(11, 122, 31), // "on_pushButton_takephoto_clicked"
QT_MOC_LITERAL(12, 154, 30), // "on_checkBox_water_stateChanged"
QT_MOC_LITERAL(13, 185, 4), // "arg1"
QT_MOC_LITERAL(14, 190, 37), // "on_checkBox_flow_current_stat..."
QT_MOC_LITERAL(15, 228, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(16, 255, 36), // "on_comboBox_init_currentIndex..."
QT_MOC_LITERAL(17, 292, 5), // "index"
QT_MOC_LITERAL(18, 298, 29), // "on_checkBox_open_stateChanged"
QT_MOC_LITERAL(19, 328, 8), // "time_out"
QT_MOC_LITERAL(20, 337, 30) // "on_pushButton_osd_save_clicked"

    },
    "camera_widget\0eventFilter\0\0QEvent*\0"
    "callKeyBoard\0QLineEdit*\0a\0callKeyBoard_ABC\0"
    "camera_button_init\0QPushButton*\0"
    "button_init\0on_pushButton_takephoto_clicked\0"
    "on_checkBox_water_stateChanged\0arg1\0"
    "on_checkBox_flow_current_stateChanged\0"
    "on_pushButton_save_clicked\0"
    "on_comboBox_init_currentIndexChanged\0"
    "index\0on_checkBox_open_stateChanged\0"
    "time_out\0on_pushButton_osd_save_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_camera_widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x08 /* Private */,
       4,    1,   79,    2, 0x08 /* Private */,
       7,    1,   82,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,
      14,    1,   92,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,
      16,    1,   96,    2, 0x08 /* Private */,
      18,    1,   99,    2, 0x08 /* Private */,
      19,    0,  102,    2, 0x08 /* Private */,
      20,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QObjectStar, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void camera_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<camera_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->callKeyBoard((*reinterpret_cast< QLineEdit*(*)>(_a[1]))); break;
        case 2: _t->callKeyBoard_ABC((*reinterpret_cast< QLineEdit*(*)>(_a[1]))); break;
        case 3: _t->camera_button_init((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_takephoto_clicked(); break;
        case 5: _t->on_checkBox_water_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_checkBox_flow_current_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_save_clicked(); break;
        case 8: _t->on_comboBox_init_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_checkBox_open_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->time_out(); break;
        case 11: _t->on_pushButton_osd_save_clicked(); break;
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLineEdit* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPushButton* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject camera_widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_camera_widget.data,
    qt_meta_data_camera_widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *camera_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *camera_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_camera_widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int camera_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
