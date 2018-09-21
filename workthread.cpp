#include "workthread.h"

WorkThread::WorkThread()
{
    runFlag = true;
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    userName = userPassword = mysqlIp = "";
}

WorkThread::~WorkThread(){
    stopThread();
    quit();
    wait();
}

void WorkThread::run(){
    runFlag = true;
    if(db.isOpen()){
        db.close();
    }
    db.setHostName(mysqlIp);
    db.setUserName(userName);
    db.setPassword(userPassword);
    db.setDatabaseName("goatdb");
    db.open();
    if(db.isOpen()){
        emit dbOpenSiganl();
        while (runFlag) {
            msleep(500);
            qDebug() << "ddd";
        }
    }else{
        //数据库打开失败的处理
    }
}

void WorkThread::startThread(){
    this->start();
}

void WorkThread::stopThread(){
    runFlag = false;
    this->quit();
    this->wait();
    if(!db.isOpen()){
        emit threadStopSignal();
    }

}


