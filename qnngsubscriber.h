#ifndef QNNGSUBSCRIBER_H
#define QNNGSUBSCRIBER_H

#include <QObject>
#include <QSocketNotifier>
#include <nng.h>


class QNngSubscriber : public QObject
{
    Q_OBJECT
    nng_socket m_sub;
    QSocketNotifier *m_notifier;

public:
    QNngSubscriber(QString host);
    ~QNngSubscriber();

private slots:
    void readyRead();

public slots:
    void subscribe(const QByteArray &topic);

signals:
    void message(const QByteArray &result);
};

#endif // QNNGSUBSCRIBER_H
