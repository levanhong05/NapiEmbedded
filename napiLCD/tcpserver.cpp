#include "tcpserver.h"

#include "tcpclient.h"
#include "androidsender.h"

#include <QDebug>

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    this->listen(QHostAddress::Any, 16103);
}

TCPServer::~TCPServer()
{
    this->close();
}

void TCPServer::acceptConnection()
{
    _client = this->nextPendingConnection();

    connect(_client, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void TCPServer::readyRead()
{
    QByteArray buffer(1024, '\0');

    if (_client->bytesAvailable() > 0) {
        buffer = _client->readAll();
    } else {
        return;
    }

    QString data = QString(buffer.data());

    qDebug() << "Receive data: " << data;

    if (data == "") {
        return;
    }

    QStringList datas = data.split(QRegExp("[\\n\\r]"), QString::SkipEmptyParts);

    foreach (QString value, datas) {
        if (value.startsWith("aip=")) {
            value = value.remove("\r").remove("\n");
            Android::Instance().setAddress(value.split("=", QString::SkipEmptyParts)[1]);
            Android::Instance().setSender(_client);
        } else if (value.startsWith("iip=")) {
            value = data.remove("\r").remove("\n");
            Client::Instance().setAddress(value.split("=", QString::SkipEmptyParts)[1]);
        } else {
            QStringList values = value.split(" ", QString::SkipEmptyParts);

            qDebug() << "Receive bbbb data: " << value;

            if (values.size() >= 4) {
                QString chipID = values[0];
                QString widgetID = values[1];
                QString key = values[values.size() - 2];
                QString value = values[values.size() - 1];

                emit requestSetupUI(chipID, widgetID, key, value);
            }

            emit dataChanged(values.join(" "));

            _client->close();
        }
    }
}
