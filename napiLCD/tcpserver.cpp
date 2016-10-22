#include "tcpserver.h"
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
    char buffer[1024] = {0};

    _client->read(buffer, _client->bytesAvailable());

    QString data = QString(buffer);

    qDebug() << "Receive data: " << data;

    if (data.startsWith("aip=")) {
        Android::Instance().setSender(_client);
    } else {
        data.remove("\n").remove("\r");

        QStringList values = data.split(" ", QString::SkipEmptyParts);

        if (values.size() >= 4) {
            QString chipID = values[0];
            QString widgetID = values[1];
            QString key = values[values.size() - 2];
            QString value = values[values.size() - 1];

            emit requestSetupUI(chipID, widgetID, key, value);
        }

        emit dataChanged(values.join(" "));
    }

    _client->close();


}
