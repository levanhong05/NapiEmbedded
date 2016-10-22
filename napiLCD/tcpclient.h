#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QThread>
#include <QTcpSocket>

class TCPClient : public QThread
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = 0);

public slots:
    void disconnected();

protected:
    virtual void run();

private:
    QTcpSocket *socket;
    bool connected;

private slots:
    void tryConnect();

};

#endif // TCPCLIENT_H
