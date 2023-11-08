/****************************************************************************
** Meta object code from reading C++ file 'dahuacamera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../main/dahuacamera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dahuacamera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DaHuaCamera_t {
    QByteArrayData data[18];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DaHuaCamera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DaHuaCamera_t qt_meta_stringdata_DaHuaCamera = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DaHuaCamera"
QT_MOC_LITERAL(1, 12, 17), // "DisplayThreadProc"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 26), // "Dahua::Infra::CThreadLite&"
QT_MOC_LITERAL(4, 58, 4), // "lite"
QT_MOC_LITERAL(5, 63, 13), // "setDisplayFPS"
QT_MOC_LITERAL(6, 77, 4), // "nFPS"
QT_MOC_LITERAL(7, 82, 15), // "isTimeToDisplay"
QT_MOC_LITERAL(8, 98, 12), // "recvNewFrame"
QT_MOC_LITERAL(9, 111, 6), // "CFrame"
QT_MOC_LITERAL(10, 118, 4), // "pBuf"
QT_MOC_LITERAL(11, 123, 9), // "ShowImage"
QT_MOC_LITERAL(12, 133, 8), // "uint8_t*"
QT_MOC_LITERAL(13, 142, 12), // "pRgbFrameBuf"
QT_MOC_LITERAL(14, 155, 6), // "nWidth"
QT_MOC_LITERAL(15, 162, 7), // "nHeight"
QT_MOC_LITERAL(16, 170, 8), // "uint64_t"
QT_MOC_LITERAL(17, 179, 12) // "nPixelFormat"

    },
    "DaHuaCamera\0DisplayThreadProc\0\0"
    "Dahua::Infra::CThreadLite&\0lite\0"
    "setDisplayFPS\0nFPS\0isTimeToDisplay\0"
    "recvNewFrame\0CFrame\0pBuf\0ShowImage\0"
    "uint8_t*\0pRgbFrameBuf\0nWidth\0nHeight\0"
    "uint64_t\0nPixelFormat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DaHuaCamera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,
       8,    1,   46,    2, 0x08 /* Private */,
      11,    4,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Bool, 0x80000000 | 12, QMetaType::Int, QMetaType::Int, 0x80000000 | 16,   13,   14,   15,   17,

       0        // eod
};

void DaHuaCamera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DaHuaCamera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayThreadProc((*reinterpret_cast< Dahua::Infra::CThreadLite(*)>(_a[1]))); break;
        case 1: _t->setDisplayFPS((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { bool _r = _t->isTimeToDisplay();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->recvNewFrame((*reinterpret_cast< const CFrame(*)>(_a[1]))); break;
        case 4: { bool _r = _t->ShowImage((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< uint64_t(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DaHuaCamera::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DaHuaCamera.data,
    qt_meta_data_DaHuaCamera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DaHuaCamera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DaHuaCamera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DaHuaCamera.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DaHuaCamera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
