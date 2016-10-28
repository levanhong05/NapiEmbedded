#include "androidsender.h"

#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>

AndroidSender::AndroidSender(QObject *parent) :
    QObject(parent)
{
    _ipAddress == "";

    _sender = 0;
}

void AndroidSender::onDataChanged(QString data)
{
    QStringList values = data.split(" ", QString::SkipEmptyParts);

    if (values.size() >= 4) {
        if (values[values.size() - 2] == "dh") {
            _distanceHorzi = values.join("");
        } else if (values[values.size() - 2] == "dv") {
            _distanceVerti = values.join("");
        } else if (values[values.size() - 2] == "ah") {
            _alignHorzi = values.join("");
        } else if (values[values.size() - 2] == "av") {
            _alignVerti = values.join("");
        } else if (values[values.size() - 2] == "p") {
            _pressure = values.join("");
        }
    }
//    if (_ipAddress == "") {
//        qDebug() << "Android IP address is empty, cant connect.";
//        return;
//    }

//    QTcpSocket *socket = new QTcpSocket();

//    socket->connectToHost(_ipAddress, 16103);

//    if (socket->waitForConnected()) {
//        qDebug() << "Send data to Android: " << data << "; to IP: " << _ipAddress;

//        socket->write(QString(data + "\n").toLatin1());
//    } else {
//        qDebug() << "Unable send data to Android";
//    }

//    socket->close();

    if (_sender == 0) {
        return;
    }

    qDebug() << "Send data to Android " << data << "IP: " << _sender->peerAddress().toString();

    _sender->write(QString(data + "\n").toLatin1());
}

QTcpSocket *AndroidSender::sender() const
{
    return _sender;
}

void AndroidSender::setSender(QTcpSocket *sender)
{
    _sender = sender;

    QStringList parts = sender->peerAddress().toString().split(":", QString::SkipEmptyParts);

    if (parts.size() > 1) {
        parts.removeFirst();
    }

    qDebug() << "Set sender Android IP: " << parts[0];

    if (_sender) {
        if (_distanceHorzi != "") {
            _sender->write(QString(_distanceHorzi + "\n").toLatin1());
        }

        if (_distanceVerti != "") {
            _sender->write(QString(_distanceVerti + "\n").toLatin1());
        }

        if (_alignHorzi != "") {
            _sender->write(QString(_alignHorzi + "\n").toLatin1());
        }

        if (_alignVerti != "") {
            _sender->write(QString(_alignVerti + "\n").toLatin1());
        }

        if (_pressure != "") {
            _sender->write(QString(_pressure + "\n").toLatin1());
        }
    }
}

void AndroidSender::setAddress(QString ipAddress)
{
    _ipAddress = ipAddress;

    qDebug() << "Android IP: " << ipAddress;
}
