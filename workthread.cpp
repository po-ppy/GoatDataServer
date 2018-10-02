#include "workthread.h"

WorkThread::WorkThread()
{
    runFlag = true;
    msgcount = 0;
}

WorkThread::~WorkThread(){
    qDebug() << "gg??";
    stopThread();
    //quit();
    //wait();
}

void WorkThread::run(){
    qDebug() << runFlag;
    //while(runFlag){
     //   dataProcessing();
    //}
}

void WorkThread::startThread(){
    runFlag = true;
    connect(client,SIGNAL(readyRead()),this,SLOT(dataProcessing()));
    this->start();
}

void WorkThread::stopThread(){
    //qDebug() << "stop ???";
    runFlag = false;
    disconnect(client,SIGNAL(readyRead()),this,SLOT(dataProcessing()));
    this->quit();
    this->wait();
}

void WorkThread::dataProcessing(){
    //qDebug() << "start dataProcessing!";
    //QSqlQuery query(db);
    //if (runFlag && client->isReadable()) {
       // 数据处理
        //qDebug() << "inter!!";
        QByteArray receiveInfo = client->readAll().trimmed().replace("\n","").replace('\x01',"");
        //qDebug() << "is there nothing?";
        //qDebug() << receiveInfo;
        QList<QByteArray> tempDataList = receiveInfo.split('$');
        tempDataList.removeAll(" ");
        tempDataList.removeAll("");
        int allLength = tempDataList.length();
        qDebug() << allLength;
        int len = 0;
        while(len+5 < allLength){
            //DataPorcessingThread tempThread(tempDataList.mid(len,len+10));
            len += 5;
            //tempThread.setObjectName(QString::number(len));
            //tempThread.start();
            //extern void testData( QList<QByteArray> todoList);
            QtConcurrent::run(this,&WorkThread::testData,tempDataList.mid(len,5),QSqlDatabase::cloneDatabase(this->db,QString::number(QDateTime::currentMSecsSinceEpoch()+len)));
            sleep(1);
        }
        sleep(1);
        //DataPorcessingThread tempThread(tempDataList.mid(len));
        //tempThread.setObjectName(QString::number(len));
        //tempThread.start();
        //extern void testData(QList<QByteArray> todoList);
        QtConcurrent::run(this,&WorkThread::testData,tempDataList.mid(len),QSqlDatabase::cloneDatabase(this->db,QString::number(QDateTime::currentMSecsSinceEpoch()+len))).waitForFinished();
        //void someFunction(int arg1, double arg2);

        //tempThread.moveToThread(this);
//        if(tempDataList.length() < 11){
//            DataPorcessingThread tempThread(tempDataList);
//            tempThread.start();
//        }else{
//            int len = tempDataList.length() / 10;
//            for(int i = 0;i < len;i++){
//                int startPos = i*len;
//                if(startPos+len > tempDataList.length()){
//                    break;
//                }
//                DataPorcessingThread tempThread(tempDataList.mid(i*len,len));
//            }
//        }


//        for(int i = 0;i < tempDataList.length();i++){
//            QList<QByteArray> datalist = tempDataList.at(i).split('*');
//            datalist.removeAll(" ");
//            datalist.removeAll("");
//            // qDebug() << datalist.size();
//            if(datalist.size() < 4){
//                return;
//            }
//            // qDebug() << "datalist.size=" ;
//            // qDebug() << datalist.size();
//            for(int k = 0; k < datalist.size();k++){
//                switch (k) {
//                case 0:
//                    receiveTime = datalist.at(0).trimmed();
//                    break;
//                case 1:
//                    temperature = datalist.at(1).trimmed();
//                    break;
//                case 2:
//                    humidity = datalist.at(2).trimmed();
//                    break;
//                case 3:
//                {
//                    QList<QByteArray> goats = datalist.at(3).trimmed().split('#');
//                    //qDebug() << goats.size();
//                    for(int i = 0;i < goats.size();i++){
//                        //qDebug() <<goats.at(i);
//                        QList<QByteArray> tempgoat = goats.at(i).trimmed().split(' ');
//                        tempgoat.removeAll(" ");
//                        tempgoat.removeAll("");
//                        if(tempgoat.size() != 7){
//                            continue;
//                        }
//                        //qDebug() << "tempgot.size = ";
//                        //qDebug() << tempgoat.size();
//                        query.prepare("insert into sportData(goatid,datatimem,sportx,sporty,sportz,anglex,angley,anglez,status) values(?,?,?,?,?,?,?,?,?)");
//                        //query.bindValue(1,QDateTime::fromMSecsSinceEpoch(receiveTime.toLongLong()));
//                        query.bindValue(1,receiveTime);
//                        query.bindValue(8,"unknown");
//                        for(int j = 0 ;j < tempgoat.size();j++){
//                            if(j == 0){
//                                query.bindValue(0,tempgoat.at(0));
//                                //qDebug() << tempgoat.at(0);
//                            }else{
//                                query.bindValue(j+1,tempgoat.at(j));
//                                // qDebug() << tempgoat.at(j) ;
//                                // qDebug() << "null???";
//                                // qDebug() << j;
//                            }
//                        }
//                        if(!query.exec()){
//                             qDebug() << "数据库插入失败！";
//                            qDebug() << query.lastQuery();
//                              QSqlError err;
//                            err= query.lastError();
//                             qDebug() << err.text();
//                        }else{
//                            //if(i == goats.size()-1){
//                            if(msgcount == 5){
//                                //QString temp = receiveTime+"#"+temperature+"#"+humidity;
//                                //QString temp = receiveTime+"#"+"23.4"+"#"+"45.6";
//                                //qDebug() << temp;
//                                query.prepare("insert into houseData(houseId,datatimem,wendu,anqi) values(:houseId,:datatimem,:wendu,:anqi);");
//                                query.bindValue(":houseId",tempgoat.at(0).trimmed());
//                                query.bindValue(":datatimem",receiveTime);
//                                query.bindValue(":wendu",temperature);
//                                query.bindValue(":anqi",humidity);
//                                //qDebug() << temperature;
//                                if(!query.exec()){
//                                    qDebug() << "houseData数据库插入失败！";
//                                   qDebug() << query.lastQuery();
//                                     QSqlError err;
//                                   err= query.lastError();
//                                    qDebug() << err.text();
//                                }
//                                //emit saveOk(temp);
//                            }

//                        }
//                    }

//                }
//                    if(msgcount == 5){
//                        msgcount = 0;
//                    }else{
//                        msgcount++;
//                    }

//                    break;
//                default:
//                    qDebug() << "有些意料之外的事发生了,数据分拣!";
//                    break;
//                }
//            }
//        }

   // }
}

void WorkThread::setDB(QSqlDatabase &inDB){
    this->db = inDB;
}

bool WorkThread::setClient(QTcpSocket *inClient){
    if(inClient->isOpen()){
        return this->client = inClient;
    }
    return false;
}
void WorkThread::testData(QList<QByteArray> todoList,QSqlDatabase &inDB){
    QTime time;
    time.start();
    qDebug() << QThread::currentThreadId();
    //qDebug() << QThread::currentThread()->objectName() << "  start";
    QString receiveTime = "";
    QString temperature = "";
    QString humidity = "";
    int msgcount = 0;
    inDB.open();
    QSqlQuery query(inDB);

    for(int i = 0;i<todoList.length();i++){
        QList<QByteArray> datalist = todoList.at(i).split('*');
        datalist.removeAll(" ");
        datalist.removeAll("");
        // qDebug() << datalist.size();
        if(datalist.size() < 4){
            return;
        }
        // qDebug() << "datalist.size=" ;
        // qDebug() << datalist.size();
        for(int k = 0; k < datalist.size();k++){
            switch (k) {
            case 0:
                receiveTime = datalist.at(0).trimmed();
                break;
            case 1:
                temperature = datalist.at(1).trimmed();
                break;
            case 2:
                humidity = datalist.at(2).trimmed();
                break;
            case 3:
            {
                QList<QByteArray> goats = datalist.at(3).trimmed().split('#');
                //qDebug() << goats.size();
                for(int i = 0;i < goats.size();i++){
                    //qDebug() <<goats.at(i);
                    QList<QByteArray> tempgoat = goats.at(i).trimmed().split(' ');
                    tempgoat.removeAll(" ");
                    tempgoat.removeAll("");
                    if(tempgoat.size() != 7){
                        continue;
                    }
                    //qDebug() << "tempgot.size = ";
                    //qDebug() << tempgoat.size();
                    query.prepare("insert into sportData(goatid,datatimem,sportx,sporty,sportz,anglex,angley,anglez,status) values(?,?,?,?,?,?,?,?,?)");
                    //query.bindValue(1,QDateTime::fromMSecsSinceEpoch(receiveTime.toLongLong()));
                    query.bindValue(1,receiveTime);
                    query.bindValue(8,"unknown");
                    for(int j = 0 ;j < tempgoat.size();j++){
                        if(j == 0){
                            query.bindValue(0,tempgoat.at(0));
                            //qDebug() << tempgoat.at(0);
                        }else{
                            query.bindValue(j+1,tempgoat.at(j));
                            // qDebug() << tempgoat.at(j) ;
                            // qDebug() << "null???";
                            // qDebug() << j;
                        }
                    }
                    if(!query.exec()){
                         qDebug() << "数据库插入失败！";
                        qDebug() << query.lastQuery();
                          QSqlError err;
                        err= query.lastError();
                         qDebug() << err.text();
                    }else{
                        //if(i == goats.size()-1){
                        if(msgcount == 5){
                            //QString temp = receiveTime+"#"+temperature+"#"+humidity;
                            //QString temp = receiveTime+"#"+"23.4"+"#"+"45.6";
                            //qDebug() << temp;
                            query.prepare("insert into houseData(houseId,datatimem,wendu,anqi) values(:houseId,:datatimem,:wendu,:anqi);");
                            query.bindValue(":houseId",tempgoat.at(0).trimmed());
                            query.bindValue(":datatimem",receiveTime);
                            query.bindValue(":wendu",temperature);
                            query.bindValue(":anqi",humidity);
                            //qDebug() << temperature;
                            if(!query.exec()){
                                qDebug() << "houseData数据库插入失败！";
                               qDebug() << query.lastQuery();
                                 QSqlError err;
                               err= query.lastError();
                                qDebug() << err.text();
                            }
                            //emit saveOk(temp);
                        }

                    }
                }

            }
                if(msgcount == 5){
                    msgcount = 0;
                }else{
                    msgcount++;
                }

                break;
            default:
                qDebug() << "有些意料之外的事发生了,数据分拣!";
                break;
            }
        }
    }
    //qDebug() << QThread::currentThread()->objectName() << "  stop";
    inDB.close();
    qDebug() << time.elapsed()/1000.0 << "s";
}


