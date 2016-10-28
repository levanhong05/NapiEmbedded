#include "tcpclient.h"

#include <QDebug>

TCPClient::TCPClient(QObject *parent) :
    QObject(parent)
{
    _ipAddress == "";
}

void TCPClient::onDataChanged(QString data)
{
    if (_ipAddress == "") {
        qDebug() << "Client IP address is empty, cant connect.";
        return;
    }

    QTcpSocket *socket = new QTcpSocket();

    socket->connectToHost(_ipAddress, 16103);

    if (socket->waitForConnected()) {
        qDebug() << "Send data to client: " << data << "; to IP: " << _ipAddress;

        socket->write(QString(data + "\n").toLatin1());
    } else {
        qDebug() << "Unable send data to client";
    }

    socket->close();
}

void TCPClient::setAddress(QString ipAddress)
{
    _ipAddress = ipAddress;

    qDebug() << "Client IP: " << ipAddress;
}

