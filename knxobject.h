#ifndef KNXOBJECT_H
#define KNXOBJECT_H

#include <QObject>
class KnxInterface;

class KnxObject: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString object READ id WRITE setId NOTIFY idChanged)

private:
    KnxInterface *_knxiface;
    QString _id;
    QString _val;
    QString _unit;

public:
    KnxObject();
    KnxObject(QString id, KnxInterface *knxiface);
    QString value() const;
    void setValue(const QString &val);

    QString unit() const;
    void setUnit(const QString &unit);

    QString id() const;
    void setId(const QString &id);

public slots:
    void changeValue(QString val);

signals:
    void idChanged();
    void valueChanged();
    void unitChanged();
};

#endif // KNXOBJECT_H
