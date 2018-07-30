#ifndef APPSTATUS_H
#define APPSTATUS_H

#include <QObject>

#include "knxinterface.h"
#include "sshclient.h"
#include "sshtunnelin.h"

class KnxInterface;

class AppStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged)
    Q_PROPERTY(QString stateMessage READ stateMessage WRITE setStateMessage NOTIFY stateMessageChanged)
    Q_PROPERTY(QString connectionMode READ connectionMode WRITE setConnectionMode NOTIFY connectionModeChanged)
    Q_PROPERTY(KnxInterface knx READ knx)

    unsigned int _connectionState;
    QString _stateMessage;
    QString _connectionMode;
    KnxInterface _knx;
    SshClient _client;
    quint16 _serverPort;
    QString _localssid;
    QString _sshserver;
    QString _sshlogin;
    QString _sshpass;

public:
    explicit AppStatus(QString server_ip, quint16 server_port, QObject *parent = nullptr, QString localssid = "", QString sshserver = "", QString sshlogin = "", QString sshpass = "");
    virtual ~AppStatus();

    unsigned int connectionState() const;
    void setConnectionState(unsigned int connectionState);

    QString stateMessage() const;
    void setStateMessage(const QString &stateMessage);

    void setState(unsigned int id, const QString &stateMessage);

    const KnxInterface *knx() const;

    QString connectionMode() const;
    void setConnectionMode(const QString &connectionMode);

public slots:
    void startConnect();
    void connect();

signals:
    void connectionStateChanged();
    void stateMessageChanged();
    void connectionModeChanged();
};

#endif // APPSTATUS_H
