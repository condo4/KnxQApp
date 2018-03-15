#include "knxobjectproxy.h"
#include "knxobject.h"
#include "knxinterface.h"

KnxObjectProxy::KnxObjectProxy(QObject *parent):
    QObject(parent),
    _obj(NULL)
{

}

QString KnxObjectProxy::value() const
{
    if(_obj) return _obj->value();
    return "";
}

void KnxObjectProxy::setValue(const QString &val)
{
    if(_obj) _obj->setValue(val);
}

QString KnxObjectProxy::unit() const
{
    if(_obj) return _obj->unit();
    return "";
}

void KnxObjectProxy::setUnit(const QString &unit)
{
    if(_obj) _obj->setUnit(unit);
}

QString KnxObjectProxy::id() const
{
    if(_obj) return _obj->id();
    return "";
}

void KnxObjectProxy::setId(const QString &id)
{
    if(_obj) _obj->setId(id);
    else
    {
        bool isnew;
        _obj = KnxInterface::instance()->getKnxObject(id, &isnew);
        QObject::connect(_obj, &KnxObject::idChanged, this, &KnxObjectProxy::idChanged);
        QObject::connect(_obj, &KnxObject::valueChanged, this, &KnxObjectProxy::valueChanged);
        QObject::connect(_obj, &KnxObject::unitChanged, this, &KnxObjectProxy::unitChanged);
        if(isnew)
        {
#if defined(DEBUG_KNXOBJECT)
            qDebug() << "Create NEW Binding Proxy for " << id;
#endif
        }
        else
        {
#if defined(DEBUG_KNXOBJECT)
            qDebug() << "Reuse Binding Proxy for " << id;
#endif
            emit unitChanged();
            emit valueChanged();
        }
    }
}

void KnxObjectProxy::changeValue(QString val)
{
    if(_obj) _obj->changeValue(val);
}
