#ifndef ANDROIDSENDER_H
#define ANDROIDSENDER_H

#include <QTcpSocket>

#include "singleton.h"

class AndroidSender : public QObject
{
    Q_OBJECT
public:
    explicit AndroidSender(QObject *parent = 0);

    QTcpSocket *sender() const;
    void setSender(QTcpSocket *sender);

private slots:
    void onDataChanged(QString data);

    void addAddressIP(QString address);
    void disconnect();

private:
    QTcpSocket *_sender;

    QStringList _addressIPs;

};

typedef Singleton<AndroidSender> Sender;

#endif // ANDROIDSENDER_H

