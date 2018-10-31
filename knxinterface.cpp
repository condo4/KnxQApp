#include "knxinterface.h"
#include "knxobject.h"

#include <QEventLoop>
#include <qnngsubscriber.h>

//#define DEBUG_IFACE

KnxInterface* KnxInterface::_instance = nullptr;

KnxInterface::KnxInterface(QSharedPointer<QTcpSocket> sock, QObject *parent):
    QObject(parent),
    _sock(sock)
{
    QObject::connect(_sock.get(), &QTcpSocket::readyRead, this, &KnxInterface::dataReceived);
    _instance = this;
}

void KnxInterface::dataReceived()
{
    QByteArray data = _sock->readAll();


}

KnxInterface::~KnxInterface()
{

}

KnxInterface *KnxInterface::instance()
{
    return _instance;
}


KnxObject *KnxInterface::getKnxObject(QString id, bool *isnew)
{
    waitConnection();
    if(_objects.contains(id))
    {
        if(isnew) *isnew = false;
        return _objects[id];
    }
    if(isnew) *isnew = true;
    KnxObject *t = new KnxObject(id, this);
    registerObject(t);
    return t;
}

void KnxInterface::registerObject(KnxObject *t)
{
    QByteArray topic(t->id().toStdString().c_str());
    _sub->subscribe(topic);
    QByteArray request = QString("listen %1\n").arg(t->id()).toLocal8Bit();
#if defined(DEBUG_IFACE)
    qDebug() << "TX: " << request;
#endif
    _sock.write(request);
    _sock.flush();
    _objects[t->id()] = t;
}
