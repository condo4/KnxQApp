#include "qnngsubscriber.h"
#include <qdebug.h>
#include <QCoreApplication>

#include <protocol/pubsub0/sub.h>

QNngSubscriber::QNngSubscriber(QString host) {
    int fd;
    int rv;
    size_t sz;

    qDebug() << "QNngSubscriber(" << host << ")";
    if((rv = nng_sub0_open(&m_sub)) != 0)
    {
        qWarning("%s %i", "nng_sub0_open fail", rv);
    }
    if ((rv = nng_dial(m_sub, qPrintable(host), nullptr, 0)) != 0)
    {
        qWarning("%s %i", "nng_dial", rv);
    }

    if ((rv = nng_setopt(m_sub, NNG_OPT_SUB_SUBSCRIBE, "", 0)) != 0)
    {
        qWarning("%s %i", "nng_setopt", rv);
    }

    sz = sizeof(fd);
    if(nng_getopt(m_sub, NNG_OPT_RECVFD, &fd, &sz) == 0)
    {
        m_notifier = new QSocketNotifier(fd, QSocketNotifier::Read, this);
        connect(m_notifier, &QSocketNotifier::activated, this, &QNngSubscriber::readyRead);
    }

}

QNngSubscriber::~QNngSubscriber() {

}

void QNngSubscriber::readyRead()
{
    char *buf = nullptr;
    QByteArray result;
    int rv;
    size_t sz;
    if ((rv = nng_recv(m_sub, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK)) != 0)
    {
        if(rv == NNG_EAGAIN)
            return;
    }

    result.append(buf, static_cast<int>(sz));
    qDebug() << "CLIENT: RECEIVED " << result;
    emit message(result);
    nng_free(buf, sz);
}


void QNngSubscriber::subscribe(const QByteArray &topic)
{
    int rv;
    //QByteArray top(topic.toLower());
    QByteArray top(topic);
    //top.replace("_",".");
    top.insert(0, "text.");
    qDebug() << "QNngSubscriber::subscribe(" << top << ")";
    if ((rv = nng_setopt(m_sub, NNG_OPT_SUB_SUBSCRIBE, top.data(), 0)) != 0)
    {
        qWarning("%s %i", "nng_setopt", rv);
    }
}
