#ifndef KNXINTERFACE_H
#define KNXINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include <qnngsubscriber.h>

class KnxObject;

class KnxInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int connection READ connection WRITE setConnection NOTIFY connectionChanged)

private:
    QString _server;
    quint16 _port;
    quint16 _subport;
    QTcpSocket _sock;
    unsigned _connection;
    QMap<QString, KnxObject*> _objects;
    static KnxInterface* _instance;
    QNngSubscriber* _sub;

private slots:
    void dataReceived();

public:
    explicit KnxInterface(QString server, quint16 port, quint16 subport, QObject *parent = nullptr);
    virtual ~KnxInterface();

    bool connection() const;
    void setConnection(bool connection);
    void waitConnection();
    static KnxInterface *instance();

    void setPort(const quint16 &port);
    void setServer(const QString &server);

    void setSubport(const quint16 &subport);

public slots:
    KnxObject *getKnxObject(QString id, bool *isnew = nullptr);
    void registerObject(KnxObject *t);
    void setValue(QString id, QString value);

signals:
    void connectionChanged();

public slots:
};

#endif // KNXINTERFACE_H
