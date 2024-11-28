/****************************************************************************
** Meta object code from reading C++ file 'sqlite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sqlite_t {
    QByteArrayData data[23];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sqlite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sqlite_t qt_meta_stringdata_sqlite = {
    {
QT_MOC_LITERAL(0, 0, 6), // "sqlite"
QT_MOC_LITERAL(1, 7, 6), // "openDb"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 11), // "createTable"
QT_MOC_LITERAL(4, 27, 12), // "isTableExist"
QT_MOC_LITERAL(5, 40, 9), // "tableName"
QT_MOC_LITERAL(6, 50, 10), // "queryTable"
QT_MOC_LITERAL(7, 61, 14), // "query_oneTable"
QT_MOC_LITERAL(8, 76, 9), // "DATA_BASE"
QT_MOC_LITERAL(9, 86, 2), // "id"
QT_MOC_LITERAL(10, 89, 16), // "singleInsertData"
QT_MOC_LITERAL(11, 106, 10), // "DATA_BASE&"
QT_MOC_LITERAL(12, 117, 10), // "singleData"
QT_MOC_LITERAL(13, 128, 14), // "moreInsertData"
QT_MOC_LITERAL(14, 143, 17), // "QList<DATA_BASE>&"
QT_MOC_LITERAL(15, 161, 8), // "moreData"
QT_MOC_LITERAL(16, 170, 10), // "modifyData"
QT_MOC_LITERAL(17, 181, 2), // "db"
QT_MOC_LITERAL(18, 184, 10), // "deleteData"
QT_MOC_LITERAL(19, 195, 11), // "deleteTable"
QT_MOC_LITERAL(20, 207, 7), // "closeDb"
QT_MOC_LITERAL(21, 215, 12), // "QSqlDatabase"
QT_MOC_LITERAL(22, 228, 8) // "database"

    },
    "sqlite\0openDb\0\0createTable\0isTableExist\0"
    "tableName\0queryTable\0query_oneTable\0"
    "DATA_BASE\0id\0singleInsertData\0DATA_BASE&\0"
    "singleData\0moreInsertData\0QList<DATA_BASE>&\0"
    "moreData\0modifyData\0db\0deleteData\0"
    "deleteTable\0closeDb\0QSqlDatabase\0"
    "database"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sqlite[] = {

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
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    1,   71,    2, 0x0a /* Public */,
       6,    1,   74,    2, 0x0a /* Public */,
       7,    2,   77,    2, 0x0a /* Public */,
      10,    2,   82,    2, 0x0a /* Public */,
      13,    2,   87,    2, 0x0a /* Public */,
      16,    2,   92,    2, 0x0a /* Public */,
      18,    2,   97,    2, 0x0a /* Public */,
      19,    1,  102,    2, 0x0a /* Public */,
      20,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    0x80000000 | 8, QMetaType::QString, QMetaType::Int,    5,    9,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    5,   12,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14,    5,   15,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8,    5,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    5,    9,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, 0x80000000 | 21,   22,

       0        // eod
};

void sqlite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sqlite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->openDb();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->createTable(); break;
        case 2: { bool _r = _t->isTableExist((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->queryTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { DATA_BASE _r = _t->query_oneTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< DATA_BASE*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->singleInsertData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< DATA_BASE(*)>(_a[2]))); break;
        case 6: _t->moreInsertData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<DATA_BASE>(*)>(_a[2]))); break;
        case 7: _t->modifyData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< DATA_BASE(*)>(_a[2]))); break;
        case 8: _t->deleteData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->deleteTable((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->closeDb((*reinterpret_cast< QSqlDatabase(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sqlite::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_sqlite.data,
    qt_meta_data_sqlite,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sqlite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sqlite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sqlite.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int sqlite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
