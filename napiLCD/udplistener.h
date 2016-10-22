#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QUdpSocket>

class UDPListener : public QObject
{
    Q_OBJECT
public:
    explicit UDPListener(QObject *parent = 0);

public slots:
    void processPendingDatagrams();

signals:
    void newAddressIP(QString address);

private:
    QUdpSocket *_udpSocket;
};

#endif // UDPLISTENER_H
