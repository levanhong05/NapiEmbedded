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
    char buffer[1024] = {0};

    _client->read(buffer, _client->bytesAvailable());

    QString data = QString(buffer);

    qDebug() << "Receive data: " << data;

    if (data.startsWith("aip=")) {
        data = data.remove("\r").remove("\n");
        Android::Instance().setAddress(data.split("=", QString::SkipEmptyParts)[1]);
        Android::Instance().setSender(_client);
    } else if (data.startsWith("iip=")) {
        data = data.remove("\r").remove("\n");
        Client::Instance().setAddress(data.split("=", QString::SkipEmptyParts)[1]);
    } else {
        QStringList datas = data.split(QRegExp("[\\n\\r]"), QString::SkipEmptyParts);

        foreach (QString value, datas) {
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
        }

        _client->close();
    }
}
