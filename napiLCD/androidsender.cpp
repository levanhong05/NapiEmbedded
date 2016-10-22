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

    qDebug() << "Send data to android: " << data << "; to IP: " << _sender->peerAddress().toString();

    _sender->write(QString(data + "\n").toLatin1());
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

    _sender = sender;
}
