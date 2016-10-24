#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QObject>
#include <QProcess>
#include <QThread>

class NetworkThread : public QObject
{
    Q_OBJECT
public:
    explicit NetworkThread(QObject *parent = 0);

public slots:
    virtual void execute(QString cmd);

    void start();

    void readyReadOutput();
    void readyReadError();

    void checkServices();

    void tryReconnect();

    void scanNetwork();

private slots:
    void finished(int exitcode);

signals:
    void ready(int exitcode);
    void messageChange(QString msg);

    void error(QString msg);

private:
    QProcess *m_process;
    QThread *m_thread;

    bool m_isRunning;

    bool m_isCheckService;

    bool m_isConnected;

};

#endif // NETWORKTHREAD_H
