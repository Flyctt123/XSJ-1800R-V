/****************************************************************************
** Meta object code from reading C++ file 'keyboard_ABC.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "keyboard_ABC.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboard_ABC.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KeyBoard_ABC_t {
    QByteArrayData data[11];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyBoard_ABC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyBoard_ABC_t qt_meta_stringdata_KeyBoard_ABC = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KeyBoard_ABC"
QT_MOC_LITERAL(1, 13, 18), // "on_caps_Bt_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "slot_numClicked"
QT_MOC_LITERAL(4, 49, 16), // "QAbstractButton*"
QT_MOC_LITERAL(5, 66, 2), // "bt"
QT_MOC_LITERAL(6, 69, 15), // "slot_carClicked"
QT_MOC_LITERAL(7, 85, 19), // "slot_hanziBtClicked"
QT_MOC_LITERAL(8, 105, 16), // "on_delBt_clicked"
QT_MOC_LITERAL(9, 122, 18), // "on_closeBt_clicked"
QT_MOC_LITERAL(10, 141, 17) // "on_backBt_clicked"

    },
    "KeyBoard_ABC\0on_caps_Bt_clicked\0\0"
    "slot_numClicked\0QAbstractButton*\0bt\0"
    "slot_carClicked\0slot_hanziBtClicked\0"
    "on_delBt_clicked\0on_closeBt_clicked\0"
    "on_backBt_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyBoard_ABC[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       8,    0,   59,    2, 0x08 /* Private */,
       9,    0,   60,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KeyBoard_ABC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KeyBoard_ABC *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_caps_Bt_clicked(); break;
        case 1: _t->slot_numClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->slot_carClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 3: _t->slot_hanziBtClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->on_delBt_clicked(); break;
        case 5: _t->on_closeBt_clicked(); break;
        case 6: _t->on_backBt_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KeyBoard_ABC::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_KeyBoard_ABC.data,
    qt_meta_data_KeyBoard_ABC,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KeyBoard_ABC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyBoard_ABC::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KeyBoard_ABC.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int KeyBoard_ABC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
