#include "appstatus.h"

#include <QEventLoop>
#include <QDebug>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#endif

QString get_ssid()
{
    QString currentSsid = "Unknown";

#if defined(Q_OS_ANDROID)
    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject manager = activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", QAndroidJniObject::fromString("wifi").object<jstring>());
    if ( manager.isValid() )
    {
        QAndroidJniObject currentConnection = manager.callObjectMethod("getConnectionInfo", "()Landroid/net/wifi/WifiInfo;");
        if(currentConnection.isValid())
        {
            currentSsid = currentConnection.callObjectMethod("getSSID", "()Ljava/lang/String;").toString();
            currentSsid.replace("\"","");
        }
    }
#endif
    return currentSsid;
}


AppStatus::AppStatus(QString server_ip, quint16 server_port, QObject *parent, QString localssid, QString sshserver, QString sshlogin, QString sshpass):
    QObject(parent),
    _connectionState(0),
    _stateMessage("Click to connect"),
    _connectionMode("Not connected"),
    _knx(server_ip, server_port),
    _serverPort(server_port),
    _localssid(localssid),
    _sshserver(sshserver),
    _sshlogin(sshlogin),
    _sshpass(sshpass)
{
}

AppStatus::~AppStatus()
{
    _client.disconnectFromHost();
}


unsigned int AppStatus::connectionState() const
{
    return _connectionState;
}

void AppStatus::setConnectionState(unsigned int connectionState)
{
    _connectionState = connectionState;
    emit connectionStateChanged();
}

QString AppStatus::stateMessage() const
{
    return _stateMessage;
}

void AppStatus::setStateMessage(const QString &stateMessage)
{
    _stateMessage = stateMessage;
#if defined(DEBUG_APP)
    qDebug() << stateMessage;
#endif
    emit stateMessageChanged();
}

void AppStatus::setState(unsigned int id, const QString &stateMessage)
{
    setConnectionState(id);
    setStateMessage(stateMessage);
}

QString AppStatus::connectionMode() const
{
    return _connectionMode;
}

void AppStatus::setConnectionMode(const QString &connectionMode)
{
    _connectionMode = connectionMode;
    emit connectionModeChanged();
}

const KnxInterface *AppStatus::knx() const
{
    return &_knx;
}


void AppStatus::connect()
{
    if(_localssid.size())
    {
        if(get_ssid() != _localssid)
        {
            setState(20, "Start SSH connection");
            _client.setPassphrase(_sshpass);
            _client.connectToHost(_sshlogin, _sshserver, 22);

            setState(30, "Wait SSH connection");
            while(!_client.channelReady())
            {
                QEventLoop wait;
                QTimer t;
                QObject::connect(&t, &QTimer::timeout, &wait, &QEventLoop::quit);
                t.start(100);
                wait.exec();
            }

            setState(40, "Create SSH Port forwarding");
            _knx.setServer("127.0.0.1");
            _knx.setPort(_client.openRemotePortForwarding("knxcached", _serverPort));
            setState(50, "SSH Complete");
            setConnectionMode("SSH");
        }
    }

    setState(50, "Start Knx Interface");
    _knx.setConnection(true);
    setState(70, "Wait Knx Interface connected");
    _knx.waitConnection();
    setState(100, "Knx Interface CONNECTED");
}
