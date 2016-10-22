#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

#include "singleton.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = 0);
    ~TCPServer();

private slots:
    void acceptConnection();

    void readyRead();

signals:
    void requestSetupUI(QString chipID, QString widgetID, QString key, QString value);

    void dataChanged(QString data);

private:
    QTcpSocket *_client;

};

typedef Singleton<TCPServer> Server;

#endif // TCPSERVER_H
