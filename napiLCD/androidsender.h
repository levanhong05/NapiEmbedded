#ifndef ANDROIDSENDER_H
#define ANDROIDSENDER_H

#include <QTcpSocket>

#include "singleton.h"

class AndroidSender : public QObject
{
    Q_OBJECT
public:
    explicit AndroidSender(QObject *parent = 0);

    QTcpSocket *sender() const;
    void setSender(QTcpSocket *sender);

private slots:
    void onDataChanged(QString data);

private:
    QTcpSocket *_sender;

};

typedef Singleton<AndroidSender> Android;

#endif // ANDROIDSENDER_H

