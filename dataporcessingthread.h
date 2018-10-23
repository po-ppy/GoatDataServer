#ifndef DATAPORCESSINGTHREAD_H
#define DATAPORCESSINGTHREAD_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QSqlQuery>
#include <QDebug>
#include <QByteArray>
#include <QSqlError>
#include <QTime>
#include <QSqlDatabase>

class DataPorcessingThread : public QThread
{
private:
    QList<QByteArray> todoList;
    QSqlDatabase db;
public:
    //DataPorcessingThread(QList<QString> inList);
    DataPorcessingThread(QList<QByteArray> inList);
    DataPorcessingThread(QList<QByteArray> inList,QSqlDatabase &inDB);
    ~DataPorcessingThread();
    void run();
    void setDB(QSqlDatabase &inDB);
};

#endif // DATAPORCESSINGTHREAD_H
