#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QDebug>
//#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QtNetwork/QtNetwork>
#include <QList>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <dataporcessingthread.h>

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread();
    ~WorkThread();
    void run();
signals:
    void threadStopSignal();
    void messageBack(QString msg,QString color);
public slots:
    void startThread();
    void stopThread();
    void dataProcessing();
    //void acceptConnect();
    void setDB(QSqlDatabase &inDB);
    bool setClient(QTcpSocket *inClient);
    void testData(QList<QByteArray> todoList,QSqlDatabase &inDB);

private:
    bool runFlag;
    QSqlDatabase db;
    QTcpSocket *client;

   QString receiveTime;
   QString NH3;
   QString CO2;
   QString temperature;
   QString humidity;
public:
   int msgcount;
   QThread wthread;
};

#endif // WORKTHREAD_H
