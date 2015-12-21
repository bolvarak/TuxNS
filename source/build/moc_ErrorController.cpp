/****************************************************************************
** Meta object code from reading C++ file 'ErrorController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../api-cdndepo-com/externals/HeimdallGI/ErrorController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ErrorController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HeimdallGI__ErrorController_t {
    QByteArrayData data[9];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeimdallGI__ErrorController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeimdallGI__ErrorController_t qt_meta_stringdata_HeimdallGI__ErrorController = {
    {
QT_MOC_LITERAL(0, 0, 27), // "HeimdallGI::ErrorController"
QT_MOC_LITERAL(1, 28, 8), // "NotFound"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "CGI*&"
QT_MOC_LITERAL(4, 44, 10), // "objRequest"
QT_MOC_LITERAL(5, 55, 6), // "View*&"
QT_MOC_LITERAL(6, 62, 11), // "objResponse"
QT_MOC_LITERAL(7, 74, 11), // "ServerFault"
QT_MOC_LITERAL(8, 86, 10) // "strMessage"

    },
    "HeimdallGI::ErrorController\0NotFound\0"
    "\0CGI*&\0objRequest\0View*&\0objResponse\0"
    "ServerFault\0strMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeimdallGI__ErrorController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       7,    3,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, QMetaType::QString,    4,    6,    8,

       0        // eod
};

void HeimdallGI::ErrorController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ErrorController *_t = static_cast<ErrorController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotFound((*reinterpret_cast< CGI*(*)>(_a[1])),(*reinterpret_cast< View*(*)>(_a[2]))); break;
        case 1: _t->ServerFault((*reinterpret_cast< CGI*(*)>(_a[1])),(*reinterpret_cast< View*(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject HeimdallGI::ErrorController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HeimdallGI__ErrorController.data,
      qt_meta_data_HeimdallGI__ErrorController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HeimdallGI::ErrorController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeimdallGI::ErrorController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HeimdallGI__ErrorController.stringdata0))
        return static_cast<void*>(const_cast< ErrorController*>(this));
    return QObject::qt_metacast(_clname);
}

int HeimdallGI::ErrorController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
