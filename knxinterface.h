#ifndef KNXINTERFACE_H
#define KNXINTERFACE_H

#include <QObject>
#include <QTcpSocket>
#include <QSharedPointer>
#include <QMap>

class KnxObject;

class KnxInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int connection READ connection WRITE setConnection NOTIFY connectionChanged)

private:
    QSharedPointer<QTcpSocket> _sock;
    QMap<quint16, KnxObject*> _objects;
    static KnxInterface* _instance;

private slots:
    void dataReceived();

public:
    explicit KnxInterface(QSharedPointer<QTcpSocket> sock, QObject *parent = nullptr);
    virtual ~KnxInterface();

    static KnxInterface *instance();

public slots:
    KnxObject *getKnxObject(QString id, bool *isnew = nullptr);
    void registerObject(KnxObject *t);
    void setValue(QString id, QString value);

signals:
    void connectionChanged();

public slots:
};

#endif // KNXINTERFACE_H
