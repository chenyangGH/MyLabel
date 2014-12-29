/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Dec 29 07:32:09 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      39,   12,   11,   11, 0x05,
      56,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,
     110,   11,   11,   11, 0x08,
     133,   11,   11,   11, 0x08,
     156,   11,   11,   11, 0x08,
     177,   11,   11,   11, 0x08,
     198,   11,   11,   11, 0x08,
     219,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0disable\0enableBezier(bool)\0"
    "enablePara(bool)\0enableRect(bool)\0"
    "open()\0updateStatusBar()\0showAbout()\0"
    "clickBezierActionAdd()\0clickBezierActionDel()\0"
    "clickParaActionAdd()\0clickParaActionDel()\0"
    "clickRectActionAdd()\0clickRectActionDel()\0"
    "clickClearAll()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->enableBezier((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->enablePara((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->enableRect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->open(); break;
        case 4: _t->updateStatusBar(); break;
        case 5: _t->showAbout(); break;
        case 6: _t->clickBezierActionAdd(); break;
        case 7: _t->clickBezierActionDel(); break;
        case 8: _t->clickParaActionAdd(); break;
        case 9: _t->clickParaActionDel(); break;
        case 10: _t->clickRectActionAdd(); break;
        case 11: _t->clickRectActionDel(); break;
        case 12: _t->clickClearAll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::enableBezier(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::enablePara(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::enableRect(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
