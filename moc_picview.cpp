/****************************************************************************
** Meta object code from reading C++ file 'picview.h'
**
** Created: Sun Dec 28 23:23:22 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "picview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'picview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PicView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    9,    8,    8, 0x05,
      36,    8,    8,    8, 0x05,
      48,    8,    8,    8, 0x05,
      59,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PicView[] = {
    "PicView\0\0size\0hasBeenResized(QSize)\0"
    "cleanedUp()\0PicFound()\0imageUnwrapped(QImage*)\0"
};

void PicView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PicView *_t = static_cast<PicView *>(_o);
        switch (_id) {
        case 0: _t->hasBeenResized((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 1: _t->cleanedUp(); break;
        case 2: _t->PicFound(); break;
        case 3: _t->imageUnwrapped((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PicView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PicView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PicView,
      qt_meta_data_PicView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PicView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PicView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PicView))
        return static_cast<void*>(const_cast< PicView*>(this));
    return QWidget::qt_metacast(_clname);
}

int PicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PicView::hasBeenResized(QSize _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PicView::cleanedUp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PicView::PicFound()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void PicView::imageUnwrapped(QImage * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
