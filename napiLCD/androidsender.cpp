#include "androidsender.h"
#include <QHostAddress>

#include <QDebug>

AndroidSender::AndroidSender(QObject *parent) :
    QObject(parent)
{
    this->_sender = 0;
}

void AndroidSender::onDataChanged(QString data)
{
    if (this->_sender == 0) {
        return;
    }

    qDebug() << "Data changed: " << data << "; IP: " << _sender->peerAddress().toString();

    _sender->write(QString(data + "\n").toLatin1());
}

void AndroidSender::addAddressIP(QString address)
{
    qDebug() << "add Address: " << address;

    if (!_addressIPs.contains(address)) {
        _addressIPs.append(address);
    }
}

void AndroidSender::disconnect()
{
    this->_addressIPs.clear();
}

QTcpSocket *AndroidSender::sender() const
{
    return _sender;
}

void AndroidSender::setSender(QTcpSocket *sender)
{
    QStringList parts = sender->peerAddress().toString().split(":", QString::SkipEmptyParts);

    if (parts.size() > 1) {
        parts.removeFirst();
    }

    qDebug() << "Android IP: " << parts[0];
    //if (_addressIPs.contains(parts[0])) {
    _sender = sender;
    connect (sender, SIGNAL(disconnected()), this, SLOT(disconnect()));
    //}
}
