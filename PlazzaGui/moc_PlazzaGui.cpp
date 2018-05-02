/****************************************************************************
** Meta object code from reading C++ file 'PlazzaGui.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/PlazzaGui.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlazzaGui.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_plazza__master__PlazzaGui_t {
    QByteArrayData data[9];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plazza__master__PlazzaGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plazza__master__PlazzaGui_t qt_meta_stringdata_plazza__master__PlazzaGui = {
    {
QT_MOC_LITERAL(0, 0, 25), // "plazza::master::PlazzaGui"
QT_MOC_LITERAL(1, 26, 8), // "_compute"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "_computeFive"
QT_MOC_LITERAL(4, 49, 15), // "checkedPhoneNbr"
QT_MOC_LITERAL(5, 65, 15), // "checkedEAddress"
QT_MOC_LITERAL(6, 81, 16), // "checkedIpAddress"
QT_MOC_LITERAL(7, 98, 7), // "askFile"
QT_MOC_LITERAL(8, 106, 12) // "validateFile"

    },
    "plazza::master::PlazzaGui\0_compute\0\0"
    "_computeFive\0checkedPhoneNbr\0"
    "checkedEAddress\0checkedIpAddress\0"
    "askFile\0validateFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plazza__master__PlazzaGui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void plazza::master::PlazzaGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlazzaGui *_t = static_cast<PlazzaGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->_compute(); break;
        case 1: _t->_computeFive(); break;
        case 2: _t->checkedPhoneNbr(); break;
        case 3: _t->checkedEAddress(); break;
        case 4: _t->checkedIpAddress(); break;
        case 5: _t->askFile(); break;
        case 6: _t->validateFile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject plazza::master::PlazzaGui::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_plazza__master__PlazzaGui.data,
      qt_meta_data_plazza__master__PlazzaGui,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *plazza::master::PlazzaGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plazza::master::PlazzaGui::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_plazza__master__PlazzaGui.stringdata0))
        return static_cast<void*>(const_cast< PlazzaGui*>(this));
    if (!strcmp(_clname, "plazza::master::IUserController"))
        return static_cast< plazza::master::IUserController*>(const_cast< PlazzaGui*>(this));
    return QObject::qt_metacast(_clname);
}

int plazza::master::PlazzaGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
