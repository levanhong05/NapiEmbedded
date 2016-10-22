#include "tcpclient.h"

#include <QHostAddress>
#include <QNetworkInterface>

TCPClient::TCPClient(QObject *parent) :
    QObject(parent)
{
    socket = 0;
    connected = false;
}

void TCPClient::tryConnect()
{
    if (connected) {
        return;
    }

    qDebug() << "try connect";

    if (socket == 0) {
        socket = new QTcpSocket();
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    }

    socket->connectToHost("192.168.1.1", 16103);

    if (socket->waitForConnected(1000)) {
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i) {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                    ipAddressesList.at(i).toIPv4Address()) {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }

        qDebug() << "myIP = " << ipAddress;

        QString data = "myip=" + ipAddress;
        socket->write(data.toLatin1());
        connected = true;
    } else {
        qDebug() << "not connected";
    }
}

void TCPClient::disconnected()
{
    qDebug() << "disconnected";

    socket = 0;

    connected = false;
}
