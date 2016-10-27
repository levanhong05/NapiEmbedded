#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = 0);

public slots:
    void disconnected();

    void sendData(QString data);

private slots:
    void tryConnect();

private:
    QTcpSocket *socket;
    bool connected;

};

#endif // TCPCLIENT_H
