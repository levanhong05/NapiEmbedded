#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "singleton.h"

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = 0);

    void setAddress(QString ipAddress);

public slots:
    void onDataChanged(QString data);

private:
    QString _ipAddress;

};

typedef Singleton<TCPClient> Client;

#endif // TCPCLIENT_H
