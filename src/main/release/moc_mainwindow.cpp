/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SaveImage_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SaveImage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SaveImage_t qt_meta_stringdata_SaveImage = {
    {
QT_MOC_LITERAL(0, 0, 9) // "SaveImage"

    },
    "SaveImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SaveImage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SaveImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SaveImage::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SaveImage.data,
    qt_meta_data_SaveImage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SaveImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SaveImage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SaveImage.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int SaveImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[47];
    char stringdata0[910];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "signal_showImage"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "Showexec"
QT_MOC_LITERAL(4, 38, 10), // "closeEvent"
QT_MOC_LITERAL(5, 49, 12), // "QCloseEvent*"
QT_MOC_LITERAL(6, 62, 5), // "event"
QT_MOC_LITERAL(7, 68, 11), // "resizeEvent"
QT_MOC_LITERAL(8, 80, 13), // "QResizeEvent*"
QT_MOC_LITERAL(9, 94, 16), // "on_login_toggled"
QT_MOC_LITERAL(10, 111, 4), // "arg1"
QT_MOC_LITERAL(11, 116, 16), // "on_start_toggled"
QT_MOC_LITERAL(12, 133, 8), // "loginBtn"
QT_MOC_LITERAL(13, 142, 14), // "loginCancelBtn"
QT_MOC_LITERAL(14, 157, 10), // "loginClose"
QT_MOC_LITERAL(15, 168, 32), // "on_mainInterfaceAction_triggered"
QT_MOC_LITERAL(16, 201, 31), // "on_setInterfaceAction_triggered"
QT_MOC_LITERAL(17, 233, 33), // "on_imageInterfaceAction_trigg..."
QT_MOC_LITERAL(18, 267, 9), // "ShowImage"
QT_MOC_LITERAL(19, 277, 14), // "slot_showImage"
QT_MOC_LITERAL(20, 292, 19), // "on_clearBtn_clicked"
QT_MOC_LITERAL(21, 312, 21), // "on_saveImgBtn_toggled"
QT_MOC_LITERAL(22, 334, 7), // "checked"
QT_MOC_LITERAL(23, 342, 19), // "on_studyBtn_toggled"
QT_MOC_LITERAL(24, 362, 21), // "on_FullScreen_toggled"
QT_MOC_LITERAL(25, 384, 17), // "on_Exit_triggered"
QT_MOC_LITERAL(26, 402, 20), // "on_startBtn_released"
QT_MOC_LITERAL(27, 423, 19), // "on_stopBtn_released"
QT_MOC_LITERAL(28, 443, 20), // "on_resetBtn_released"
QT_MOC_LITERAL(29, 464, 19), // "on_startBtn_pressed"
QT_MOC_LITERAL(30, 484, 18), // "on_stopBtn_pressed"
QT_MOC_LITERAL(31, 503, 19), // "on_resetBtn_pressed"
QT_MOC_LITERAL(32, 523, 25), // "on_clearBottleBtn_pressed"
QT_MOC_LITERAL(33, 549, 26), // "on_clearBottleBtn_released"
QT_MOC_LITERAL(34, 576, 23), // "on_beltPowerBtn_toggled"
QT_MOC_LITERAL(35, 600, 25), // "on_clearBufferBtn_pressed"
QT_MOC_LITERAL(36, 626, 26), // "on_clearBufferBtn_released"
QT_MOC_LITERAL(37, 653, 21), // "on_shaker1Add_clicked"
QT_MOC_LITERAL(38, 675, 21), // "on_shaker1Dec_clicked"
QT_MOC_LITERAL(39, 697, 21), // "on_shaker2Add_clicked"
QT_MOC_LITERAL(40, 719, 21), // "on_shaker2Dec_clicked"
QT_MOC_LITERAL(41, 741, 21), // "on_shaker3Add_clicked"
QT_MOC_LITERAL(42, 763, 21), // "on_shaker3Dec_clicked"
QT_MOC_LITERAL(43, 785, 31), // "on_singleNumBox_editingFinished"
QT_MOC_LITERAL(44, 817, 30), // "on_Shaker1VBox_editingFinished"
QT_MOC_LITERAL(45, 848, 30), // "on_Shaker2VBox_editingFinished"
QT_MOC_LITERAL(46, 879, 30) // "on_Shaker3VBox_editingFinished"

    },
    "MainWindow\0signal_showImage\0\0Showexec\0"
    "closeEvent\0QCloseEvent*\0event\0resizeEvent\0"
    "QResizeEvent*\0on_login_toggled\0arg1\0"
    "on_start_toggled\0loginBtn\0loginCancelBtn\0"
    "loginClose\0on_mainInterfaceAction_triggered\0"
    "on_setInterfaceAction_triggered\0"
    "on_imageInterfaceAction_triggered\0"
    "ShowImage\0slot_showImage\0on_clearBtn_clicked\0"
    "on_saveImgBtn_toggled\0checked\0"
    "on_studyBtn_toggled\0on_FullScreen_toggled\0"
    "on_Exit_triggered\0on_startBtn_released\0"
    "on_stopBtn_released\0on_resetBtn_released\0"
    "on_startBtn_pressed\0on_stopBtn_pressed\0"
    "on_resetBtn_pressed\0on_clearBottleBtn_pressed\0"
    "on_clearBottleBtn_released\0"
    "on_beltPowerBtn_toggled\0"
    "on_clearBufferBtn_pressed\0"
    "on_clearBufferBtn_released\0"
    "on_shaker1Add_clicked\0on_shaker1Dec_clicked\0"
    "on_shaker2Add_clicked\0on_shaker2Dec_clicked\0"
    "on_shaker3Add_clicked\0on_shaker3Dec_clicked\0"
    "on_singleNumBox_editingFinished\0"
    "on_Shaker1VBox_editingFinished\0"
    "on_Shaker2VBox_editingFinished\0"
    "on_Shaker3VBox_editingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  217,    2, 0x08 /* Private */,
       4,    1,  218,    2, 0x08 /* Private */,
       7,    1,  221,    2, 0x08 /* Private */,
       9,    1,  224,    2, 0x08 /* Private */,
      11,    1,  227,    2, 0x08 /* Private */,
      12,    0,  230,    2, 0x08 /* Private */,
      13,    0,  231,    2, 0x08 /* Private */,
      14,    0,  232,    2, 0x08 /* Private */,
      15,    0,  233,    2, 0x08 /* Private */,
      16,    0,  234,    2, 0x08 /* Private */,
      17,    0,  235,    2, 0x08 /* Private */,
      18,    0,  236,    2, 0x08 /* Private */,
      19,    1,  237,    2, 0x08 /* Private */,
      20,    0,  240,    2, 0x08 /* Private */,
      21,    1,  241,    2, 0x08 /* Private */,
      23,    1,  244,    2, 0x08 /* Private */,
      24,    1,  247,    2, 0x08 /* Private */,
      25,    0,  250,    2, 0x08 /* Private */,
      26,    0,  251,    2, 0x08 /* Private */,
      27,    0,  252,    2, 0x08 /* Private */,
      28,    0,  253,    2, 0x08 /* Private */,
      29,    0,  254,    2, 0x08 /* Private */,
      30,    0,  255,    2, 0x08 /* Private */,
      31,    0,  256,    2, 0x08 /* Private */,
      32,    0,  257,    2, 0x08 /* Private */,
      33,    0,  258,    2, 0x08 /* Private */,
      34,    1,  259,    2, 0x08 /* Private */,
      35,    0,  262,    2, 0x08 /* Private */,
      36,    0,  263,    2, 0x08 /* Private */,
      37,    0,  264,    2, 0x08 /* Private */,
      38,    0,  265,    2, 0x08 /* Private */,
      39,    0,  266,    2, 0x08 /* Private */,
      40,    0,  267,    2, 0x08 /* Private */,
      41,    0,  268,    2, 0x08 /* Private */,
      42,    0,  269,    2, 0x08 /* Private */,
      43,    0,  270,    2, 0x08 /* Private */,
      44,    0,  271,    2, 0x08 /* Private */,
      45,    0,  272,    2, 0x08 /* Private */,
      46,    0,  273,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    6,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_showImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->Showexec(); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 4: _t->on_login_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_start_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->loginBtn(); break;
        case 7: _t->loginCancelBtn(); break;
        case 8: _t->loginClose(); break;
        case 9: _t->on_mainInterfaceAction_triggered(); break;
        case 10: _t->on_setInterfaceAction_triggered(); break;
        case 11: _t->on_imageInterfaceAction_triggered(); break;
        case 12: _t->ShowImage(); break;
        case 13: _t->slot_showImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 14: _t->on_clearBtn_clicked(); break;
        case 15: _t->on_saveImgBtn_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->on_studyBtn_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->on_FullScreen_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_Exit_triggered(); break;
        case 19: _t->on_startBtn_released(); break;
        case 20: _t->on_stopBtn_released(); break;
        case 21: _t->on_resetBtn_released(); break;
        case 22: _t->on_startBtn_pressed(); break;
        case 23: _t->on_stopBtn_pressed(); break;
        case 24: _t->on_resetBtn_pressed(); break;
        case 25: _t->on_clearBottleBtn_pressed(); break;
        case 26: _t->on_clearBottleBtn_released(); break;
        case 27: _t->on_beltPowerBtn_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_clearBufferBtn_pressed(); break;
        case 29: _t->on_clearBufferBtn_released(); break;
        case 30: _t->on_shaker1Add_clicked(); break;
        case 31: _t->on_shaker1Dec_clicked(); break;
        case 32: _t->on_shaker2Add_clicked(); break;
        case 33: _t->on_shaker2Dec_clicked(); break;
        case 34: _t->on_shaker3Add_clicked(); break;
        case 35: _t->on_shaker3Dec_clicked(); break;
        case 36: _t->on_singleNumBox_editingFinished(); break;
        case 37: _t->on_Shaker1VBox_editingFinished(); break;
        case 38: _t->on_Shaker2VBox_editingFinished(); break;
        case 39: _t->on_Shaker3VBox_editingFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signal_showImage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signal_showImage(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
