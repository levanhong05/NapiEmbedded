#include "udplistener.h"

#include <QDebug>

UDPListener::UDPListener(QObject *parent) :
    QObject(parent)
{
    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::Any, 16102, QUdpSocket::ShareAddress);

    connect(_udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void UDPListener::processPendingDatagrams()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;

    while (_udpSocket->hasPendingDatagrams()) {
        datagram.resize(_udpSocket->pendingDatagramSize());
        _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    }

    qDebug() << datagram.data();

    QStringList address = sender.toString().split(":", QString::SkipEmptyParts);

    QString addressIP = address[0].trimmed();

    if (address.size() > 1) {
        addressIP = address[1].trimmed();
    }

    QByteArray data;
    data.append(addressIP);

    qDebug() << "UDP IP: " << addressIP;

    _udpSocket->writeDatagram(data, QHostAddress::Broadcast, 16101);

    emit newAddressIP(addressIP);
}
