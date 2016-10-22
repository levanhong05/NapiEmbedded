#include "networkthread.h"

#include <QApplication>

NetworkThread::NetworkThread(QObject *parent) :
    QObject(parent)
{
    this->m_thread = new QThread();
    this->m_thread->start();

    this->m_process = new QProcess();

#ifdef Q_OS_WIN
    this->m_process->setProgram("cmd.exe");
#else
    this->m_process->setProgram("/bin/bash");
#endif

    connect(this->m_process, SIGNAL(readyRead()), this, SLOT(readyRead()));
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

void NetworkThread::readyRead()
{
    while (this->m_process->canReadLine()) {
        QString line = QString::fromUtf8(this->m_process->readLine());
        line.remove('\r');
        line.chop(1);

        emit messageChange(line);
    }
}

void NetworkThread::readyReadError()
{
    QString all = QString::fromUtf8(this->m_process->readAllStandardError());
    all.remove('\r');
    QStringList lines = all.split('\n', QString::SkipEmptyParts);

    foreach (QString line, lines) {
        line = line.trimmed();

        emit error(line);
    }
}

void NetworkThread::finished(int exitcode)
{
    emit ready(exitcode);
}
