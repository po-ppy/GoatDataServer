#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QSql>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <workthread.h>
#include <QtNetwork/QtNetwork>
#include <QList>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void startServer();
    void stopServer();
    void minimumWindow();
    void showWindow();
    void exitWindow();
    void activedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void disableInput();
    void enableInput();
    void messageShow(QString msg ,QString color);
    void acceptConnect();
    void initSQL();
signals:
    void startSignal(QString);
    void stopSignal();

private slots:
    void on_startButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    //WorkThread *workThread;
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *cmenu;
    QAction *showAction;
    QAction *exitAction;
    bool runFlag;
    QSqlDatabase db;
    QTcpServer *server;
    QList<QTcpSocket *> *clientList;
    QList<WorkThread *> *threadList;
    QThread wthread;
};

#endif // MAINWINDOW_H
