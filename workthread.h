#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
    ~WorkThread();
    void run();
signals:
    void dbOpenSiganl();
    void threadStopSignal();
public slots:
    void startThread();
    void stopThread();

private:
    bool runFlag;
    QSqlDatabase db;
    QString userName;
    QString userPassword;
    QString mysqlIp;
};

#endif // WORKTHREAD_H
