#include "knxinterface.h"
#include "knxobject.h"

#include <QEventLoop>
#include <qnngsubscriber.h>

//#define DEBUG_IFACE

KnxInterface* KnxInterface::_instance = nullptr;

KnxInterface::KnxInterface(QString server, quint16 port, quint16 subport, QObject *parent):
    QObject(parent),
    _server(server),
    _port(port),
    _subport(subport),
    _connection(0)
{
    QObject::connect(&_sock, &QTcpSocket::connected, [this](){
#if defined(DEBUG_IFACE)
        qDebug() << "CONNECTED";
#endif
        _connection = 1;
        _sock.write("*idn?\n");
        emit connectionChanged();
    });
    QObject::connect(&_sock, &QTcpSocket::readyRead, this, &KnxInterface::dataReceived);
    _instance = this;
}

void KnxInterface::setPort(const quint16 &port)
{
    _port = port;
}

void KnxInterface::setServer(const QString &server)
{
    _server = server;
}

void KnxInterface::setSubport(const quint16 &subport)
{
    _subport = subport;
}

void KnxInterface::dataReceived()
{
    QByteArray datal = _sock.readAll();

    foreach (QByteArray data, datal.split('\n')) {
        if(data.startsWith("\"KnxCached\","))
        {
#if defined(DEBUG_IFACE)
            qDebug() << "IDN OK";
#endif
            _connection = 2;
            emit connectionChanged();
        }
#if defined(DEBUG_IFACE)
        qDebug() << "RX: " << data;
#endif
        QList<QByteArray> dt = data.split(' ');
        if(dt.size() < 3)
            continue;
        QString id = dt[1].replace(":","");
        if(_objects.contains(id))
        {
            _objects[id]->setValue(dt[2]);
            if(dt.size() > 3)
                _objects[id]->setUnit(dt[3]);
        }
    }
}

KnxInterface::~KnxInterface()
{

}


bool KnxInterface::connection() const
{
    return _connection;
}

void KnxInterface::setConnection(bool connection)
{
    if(connection)
    {
        if(!_connection)
        {
#if defined(DEBUG_IFACE)
            qDebug() << "Connect to " << _server << " on " << _port;
#endif
            _sock.connectToHost(_server, _port);
            _sub = new QNngSubscriber(QString("tcp://%1:%2").arg(_server).arg(_subport));
        }
    }
    else
    {
        if(_connection)
        {
            _sock.close();
        }
    }
}

void KnxInterface::waitConnection()
{
    if(!_connection)
    {
#if defined(DEBUG_IFACE)
        qDebug() << "Wait connection";
#endif
        while(_connection < 2)
        {
            QEventLoop loop;
            QObject::connect(this, &KnxInterface::connectionChanged, &loop, &QEventLoop::quit);
            loop.exec();
        }
#if defined(DEBUG_IFACE)
        qDebug() << "Wait connection OK";
#endif
    }
}

KnxInterface *KnxInterface::instance()
{
    return _instance;
}

void KnxInterface::setValue(QString id, QString value)
{
    QByteArray request = (QString("set ") + id + " " + value).toLocal8Bit() + "\n";
#if defined(DEBUG_IFACE)
    qDebug() << "TX: " << request;
#endif
    _sock.write(request);
    _sock.flush();
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
