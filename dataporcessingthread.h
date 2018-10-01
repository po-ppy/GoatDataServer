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

class DataPorcessingThread : public QThread
{
private:
    QList<QByteArray> todoList;
public:
    //DataPorcessingThread(QList<QString> inList);
    DataPorcessingThread(QList<QByteArray> inList);
    ~DataPorcessingThread();
    void run();
};

#endif // DATAPORCESSINGTHREAD_H
