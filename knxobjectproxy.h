#ifndef KNXOBJECTPROXY_H
#define KNXOBJECTPROXY_H

#include <QObject>
class KnxObject;

class KnxObjectProxy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString object READ id WRITE setId NOTIFY idChanged)

private:
    KnxObject *_obj;

public:
    explicit KnxObjectProxy(QObject *parent = nullptr);

    QString value() const;
    void setValue(const QString &val);

    QString unit() const;
    void setUnit(const QString &unit);

    QString id() const;
    void setId(const QString &id);

signals:
    void idChanged();
    void valueChanged();
    void unitChanged();

public slots:
    void changeValue(QString val);
};

#endif // KNXOBJECTPROXY_H
