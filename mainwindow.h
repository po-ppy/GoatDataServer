#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <workthread.h>


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
    void minimumWindow();
    void showWindow();
    void exitWindow();
    void activedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void disableInput();
    void enableInput();
signals:
    void startSignal(QString);
    void stopSignal();

private slots:
    void on_startButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    WorkThread *workThread;
    QSystemTrayIcon *mSysTrayIcon;
    QMenu *cmenu;
    QAction *showAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
