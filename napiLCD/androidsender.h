#ifndef ANDROIDSENDER_H
#define ANDROIDSENDER_H

#include <QObject>
#include <QTcpSocket>

#include "singleton.h"

class AndroidSender : public QObject
{
    Q_OBJECT
public:
    explicit AndroidSender(QObject *parent = 0);

    void setAddress(QString ipAddress);

    QTcpSocket *sender() const;
    void setSender(QTcpSocket *sender);

public slots:
    void onDataChanged(QString data);

private:
    QString _ipAddress;

    QTcpSocket *_sender;

    QString _distanceHorzi;
    QString _distanceVerti;
    QString _alignHorzi;
    QString _alignVerti;
    QString _pressure;

};

typedef Singleton<AndroidSender> Android;

#endif // ANDROIDSENDER_H

