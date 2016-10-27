#include "networkthread.h"

#include <QApplication>

#include <QDebug>

NetworkThread::NetworkThread(QObject *parent) :
    QObject(parent)
{
    this->m_process = new QProcess();

    m_isConnected = false;

#ifdef Q_OS_WIN
    this->m_process->setProgram("cmd.exe");

#else
    this->m_process->setProgram("/bin/bash");
#endif

    connect(this->m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadOutput()));
    connect(this->m_process, SIGNAL(readyReadStandardError()), this, SLOT(readyReadError()));
    connect(this->m_process, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

void NetworkThread::execute(QString cmd)
{
    this->m_process->write((cmd + "\n").toUtf8());
}

void NetworkThread::start()
{
    this->m_process->start(QIODevice::ReadWrite);
}

void NetworkThread::readyReadOutput()
{
    QThread::currentThread()->msleep(2000);

    QString output = QString::fromUtf8(this->m_process->readAllStandardOutput());

    output.remove('\r');
    QStringList lines = output.split('\n', QString::SkipEmptyParts);

    foreach (QString line, lines) {
        if (line.contains("*AR") && line.contains("SATECODAQ")) {
            m_isConnected = true;

            qDebug() << "Wifi network is connected";

            return;
        } else if (line.contains("Retry (yes/no) ?")) {
            m_process->write(QString("no\n").toUtf8());
            break;
        } else if (line.contains("SATECODAQ")) {
            tryReconnect();

            break;
        } else if (line.contains("Connected") && line.contains("wifi_001f1fe4aadd_53415445434f444151_managed_psk")) {
            m_isConnected = true;

            qDebug() << "Wifi network is connected";

            return;
        }
    }

    m_isConnected = false;

    qDebug() << "Wifi is not connected";

    scanNetwork();
}

void NetworkThread::readyReadError()
{
    scanNetwork();
}

void NetworkThread::tryReconnect()
{
    qDebug() << "Try reconnect wifi";

    this->m_process->write(QString("sudo connmanctl agent on\n").toUtf8());
    this->m_process->write(QString("sudo connmanctl connect wifi_001f1fe4aadd_53415445434f444151_managed_psk\n").toUtf8());
}

void NetworkThread::scanNetwork()
{
    qDebug() << "Scan wifi network";

    this->m_process->write(QString("sudo connmanctl scan wifi\n").toUtf8());
    this->m_process->write(QString("sudo connmanctl services\n").toUtf8());
}

void NetworkThread::finished(int exitcode)
{
    emit ready(exitcode);
}
