/****************************************************************************
** Meta object code from reading C++ file 'QZBarThread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QZBarThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QZBarThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_zbar__QZBarThread[] = {

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
      18,   36,   43,   43, 0x05,
      44,   43,   43,   43, 0x05,
      53,   74,   43,   43, 0x05,
      84,  105,   43,   43, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_zbar__QZBarThread[] = {
    "zbar::QZBarThread\0videoOpened(bool)\0"
    "opened\0\0update()\0decoded(int,QString)\0"
    "type,data\0decodedText(QString)\0data\0"
};

void zbar::QZBarThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QZBarThread *_t = static_cast<QZBarThread *>(_o);
        switch (_id) {
        case 0: _t->videoOpened((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->decoded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->decodedText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData zbar::QZBarThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject zbar::QZBarThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_zbar__QZBarThread,
      qt_meta_data_zbar__QZBarThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &zbar::QZBarThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *zbar::QZBarThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *zbar::QZBarThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_zbar__QZBarThread))
        return static_cast<void*>(const_cast< QZBarThread*>(this));
    if (!strcmp(_clname, "Image::Handler"))
        return static_cast< Image::Handler*>(const_cast< QZBarThread*>(this));
    return QThread::qt_metacast(_clname);
}

int zbar::QZBarThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void zbar::QZBarThread::videoOpened(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void zbar::QZBarThread::update()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void zbar::QZBarThread::decoded(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void zbar::QZBarThread::decodedText(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
