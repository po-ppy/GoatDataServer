#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    workThread = new WorkThread();
    mSysTrayIcon = new QSystemTrayIcon(this);
    cmenu = new QMenu(this);
    showAction = cmenu->addAction("显示主界面");
    cmenu->addSeparator();
    exitAction = cmenu->addAction("退出");

    mSysTrayIcon->setIcon(QIcon(":/nu.png"));
    mSysTrayIcon->setToolTip("运动分析服务");
    mSysTrayIcon->setContextMenu(cmenu);
    mSysTrayIcon->show();
    connect(this,SIGNAL(startSignal(QString)),workThread,SLOT(startThread()));
    connect(this,SIGNAL(stopSignal()),workThread,SLOT(stopThread()));
    connect(mSysTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(activedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    connect(showAction,SIGNAL(triggered(bool)),this,SLOT(showWindow()));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(exitWindow()));

    connect(workThread,SIGNAL(dbOpenSiganl()),this,SLOT(disableInput()));
    connect(workThread,SIGNAL(threadStopSignal()),this,SLOT(enableInput()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    startServer();
}

void MainWindow::on_closeButton_clicked()
{
    if(workThread->isRunning()){
        emit stopSignal();
    }
}

void MainWindow::startServer(){
    emit startSignal("ggg");
    minimumWindow();
}

void MainWindow::minimumWindow(){
    this->hide();
}

void MainWindow::activedSysTrayIcon(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        //单击
        mSysTrayIcon->showMessage("帮助","这是奶山羊运动数据分析服务！",QSystemTrayIcon::Information,1500);
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击
        showWindow();
        break;
    default:
        break;
    }
}

void MainWindow::showWindow(){
    this->show();
}

void MainWindow::exitWindow(){
    exit(0);
}

void MainWindow::disableInput(){
    ui->serverIp->setDisabled(true);
    ui->serverPassword->setDisabled(true);
    ui->serverUser->setDisabled(true);
}

void MainWindow::enableInput(){
    ui->serverIp->setEnabled(true);
    ui->serverUser->setEnabled(true);
    ui->serverPassword->setEnabled(true);
}
