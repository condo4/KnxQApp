#include "knxobject.h"
#include <QDebug>

#include "knxinterface.h"

// #define DEBUG_KNXOBJECT

KnxObject::KnxObject()
{
    _knxiface = KnxInterface::instance();
}

KnxObject::KnxObject(QString id, KnxInterface *knxiface):
    QObject((QObject*)knxiface),
    _knxiface(knxiface),
    _id(id)
{
#if defined(DEBUG_KNXOBJECT)
    qDebug() << "Create KnxObject(" << id << ")";
#endif
}

QString KnxObject::id() const
{
    return _id;
}

void KnxObject::setId(const QString &id)
{
    _id = id;
#if defined(DEBUG_KNXOBJECT)
    qDebug() << "Register KnxObject(" << id << ")";
#endif
    KnxInterface::instance()->registerObject(this);
}

QString KnxObject::value() const
{
    return _val;
}

void KnxObject::setValue(const QString &val)
{
#if defined(DEBUG_KNXOBJECT)
    qDebug() << "KnxObject " << _id << " new value:" << val;
#endif
    if(_val == val) return;
    _val = val;
    emit valueChanged();
}

QString KnxObject::unit() const
{
    return _unit;
}

void KnxObject::setUnit(const QString &unit)
{
    if(_unit == unit) return;
    _unit = unit;
    emit unitChanged();
}

void KnxObject::changeValue(QString val)
{
#if defined(DEBUG_KNXOBJECT)
    qDebug() << "Change " << _id << " for " << val;
#endif
    _knxiface->setValue(_id, val);
}
