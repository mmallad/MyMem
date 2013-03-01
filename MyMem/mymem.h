#ifndef MYMEM_H
#define MYMEM_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <QTimer>

//Dpak Malla
//mmallad
//This is just to get total memory and free memory
//As I am developer I should get look around the memory :)

namespace Ui {
class MyMem;
}

class MyMem : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MyMem(QWidget *parent = 0);
    ~MyMem();
private slots:
    void showTrayWindow();
    void closeTrayWindow();
    void hideTrayWindow();
    void letsRun();
private:
    QTimer *timer;
    void readFile();
    void closeEvent(QCloseEvent *);
    QSystemTrayIcon *tray;
    void createActions();
    void createTrayMenu();
    QAction *showAction;
    QAction *closeAction;
    QAction *hideAction;
    bool isClose;
    Ui::MyMem *ui;
};

#endif // MYMEM_H
