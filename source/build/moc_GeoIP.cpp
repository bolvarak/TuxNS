/****************************************************************************
** Meta object code from reading C++ file 'GeoIP.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../api-cdndepo-com/controllers/GeoIP.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeoIP.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GeoIPController_t {
    QByteArrayData data[10];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GeoIPController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GeoIPController_t qt_meta_stringdata_GeoIPController = {
    {
QT_MOC_LITERAL(0, 0, 15), // "GeoIPController"
QT_MOC_LITERAL(1, 16, 11), // "dynamicJSON"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "HeimdallGI::CGI*&"
QT_MOC_LITERAL(4, 47, 10), // "hgiRequest"
QT_MOC_LITERAL(5, 58, 18), // "HeimdallGI::View*&"
QT_MOC_LITERAL(6, 77, 11), // "hgiResponse"
QT_MOC_LITERAL(7, 89, 10), // "dynamicXML"
QT_MOC_LITERAL(8, 100, 10), // "staticJSON"
QT_MOC_LITERAL(9, 111, 9) // "staticXML"

    },
    "GeoIPController\0dynamicJSON\0\0"
    "HeimdallGI::CGI*&\0hgiRequest\0"
    "HeimdallGI::View*&\0hgiResponse\0"
    "dynamicXML\0staticJSON\0staticXML"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeoIPController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       7,    2,   39,    2, 0x0a /* Public */,
       8,    2,   44,    2, 0x0a /* Public */,
       9,    2,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void GeoIPController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GeoIPController *_t = static_cast<GeoIPController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dynamicJSON((*reinterpret_cast< HeimdallGI::CGI*(*)>(_a[1])),(*reinterpret_cast< HeimdallGI::View*(*)>(_a[2]))); break;
        case 1: _t->dynamicXML((*reinterpret_cast< HeimdallGI::CGI*(*)>(_a[1])),(*reinterpret_cast< HeimdallGI::View*(*)>(_a[2]))); break;
        case 2: _t->staticJSON((*reinterpret_cast< HeimdallGI::CGI*(*)>(_a[1])),(*reinterpret_cast< HeimdallGI::View*(*)>(_a[2]))); break;
        case 3: _t->staticXML((*reinterpret_cast< HeimdallGI::CGI*(*)>(_a[1])),(*reinterpret_cast< HeimdallGI::View*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject GeoIPController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GeoIPController.data,
      qt_meta_data_GeoIPController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GeoIPController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeoIPController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GeoIPController.stringdata0))
        return static_cast<void*>(const_cast< GeoIPController*>(this));
    return QObject::qt_metacast(_clname);
}

int GeoIPController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
