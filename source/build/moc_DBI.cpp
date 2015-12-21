/****************************************************************************
** Meta object code from reading C++ file 'DBI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../api-cdndepo-com/externals/HeimdallGI/DBI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DBI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HeimdallGI__DBI_t {
    QByteArrayData data[9];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeimdallGI__DBI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeimdallGI__DBI_t qt_meta_stringdata_HeimdallGI__DBI = {
    {
QT_MOC_LITERAL(0, 0, 15), // "HeimdallGI::DBI"
QT_MOC_LITERAL(1, 16, 13), // "CurrentStatus"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "intStatusCode"
QT_MOC_LITERAL(4, 45, 8), // "strQuery"
QT_MOC_LITERAL(5, 54, 8), // "strError"
QT_MOC_LITERAL(6, 63, 3), // "Row"
QT_MOC_LITERAL(7, 67, 10), // "QSqlRecord"
QT_MOC_LITERAL(8, 78, 6) // "qsrRow"

    },
    "HeimdallGI::DBI\0CurrentStatus\0\0"
    "intStatusCode\0strQuery\0strError\0Row\0"
    "QSqlRecord\0qsrRow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeimdallGI__DBI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       6,    1,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void HeimdallGI::DBI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DBI *_t = static_cast<DBI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CurrentStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->Row((*reinterpret_cast< QSqlRecord(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DBI::*_t)(int , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DBI::CurrentStatus)) {
                *result = 0;
            }
        }
        {
            typedef void (DBI::*_t)(QSqlRecord );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DBI::Row)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject HeimdallGI::DBI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HeimdallGI__DBI.data,
      qt_meta_data_HeimdallGI__DBI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HeimdallGI::DBI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeimdallGI::DBI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HeimdallGI__DBI.stringdata0))
        return static_cast<void*>(const_cast< DBI*>(this));
    return QObject::qt_metacast(_clname);
}

int HeimdallGI::DBI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void HeimdallGI::DBI::CurrentStatus(int _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HeimdallGI::DBI::Row(QSqlRecord _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
