/****************************************************************************
** Meta object code from reading C++ file 'mymainwindow.hh'
**
** Created: Wed May 15 16:32:48 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mymainwindow.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymainwindow.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      29,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   13,   13,   13, 0x0a,
      67,   13,   13,   13, 0x0a,
      88,   86,   13,   13, 0x0a,
     106,   86,   13,   13, 0x0a,
     122,   13,   13,   13, 0x0a,
     132,   13,   13,   13, 0x0a,
     142,   13,   13,   13, 0x0a,
     158,   13,   13,   13, 0x0a,
     174,   13,   13,   13, 0x0a,
     189,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyMainWindow[] = {
    "MyMainWindow\0\0close_window()\0"
    "counterChanged(int)\0set_points_plus()\0"
    "set_points_minus()\0x\0set_begin(double)\0"
    "set_end(double)\0push_go()\0goodbye()\0"
    "push_method_1()\0push_method_2()\0"
    "push_graphic()\0push_residual()\0"
};

void MyMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyMainWindow *_t = static_cast<MyMainWindow *>(_o);
        switch (_id) {
        case 0: _t->close_window(); break;
        case 1: _t->counterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_points_plus(); break;
        case 3: _t->set_points_minus(); break;
        case 4: _t->set_begin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->set_end((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->push_go(); break;
        case 7: _t->goodbye(); break;
        case 8: _t->push_method_1(); break;
        case 9: _t->push_method_2(); break;
        case 10: _t->push_graphic(); break;
        case 11: _t->push_residual(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyMainWindow,
      qt_meta_data_MyMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindow))
        return static_cast<void*>(const_cast< MyMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MyMainWindow::close_window()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MyMainWindow::counterChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
