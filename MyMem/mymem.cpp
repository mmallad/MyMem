#include "mymem.h"
#include "ui_mymem.h"

MyMem::MyMem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMem)
{
    ui->setupUi(this);
    setWindowTitle(tr("Find Memory Usage :)"));
    this->isClose = false;
    this->createActions();
    this->createTrayMenu();
    //Lets just disable show menu first
    this->showAction->setDisabled(true);
    ui->total->setText("");
    ui->free->setText("");
    setGeometry(0,0,0,0);
    //Lets remove everything around the window and make it appear topmost of all window.
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->progressBar->setValue(0);
    //Lets read initial memory info.
    this->readFile();
    //Lets create timer
    this->timer = new QTimer(this);
    //Connect to slot wth timeout signal.
    connect(this->timer,SIGNAL(timeout()),this,SLOT(letsRun()));
    //Lets start timer with 1000 millisecond
    this->timer->start(1000);
}
void MyMem::letsRun()
{
    this->readFile();
}

void MyMem::readFile()
{
    try
    {

        QProcess p;
        //First lets us read total memory frm file /proc/meminfo
        p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
        p.waitForFinished();
        QString totalMem = p.readAllStandardOutput();
        long tM = totalMem.toLong() / 1024;
        ui->progressBar->setMaximum(tM);
        ui->total->setText(QString::number(tM) + " MB");
        //Lets us now read free memory.
        p.start("awk", QStringList() << "/MemFree/ { print $2 }" << "/proc/meminfo");
        p.waitForFinished();
        QString freeMem = p.readAllStandardOutput();
        long fM = freeMem.toLong() / 1024;
        ui->free->setText(QString::number(fM) + " MB");
        p.close();
        ui->progressBar->setValue(tM - fM);
        //For MAC :)
        //p.start("sysctl", QStringList() << "kern.version" << "hw.physmem");

    }
    catch(QString ex)
    {
        QMessageBox::critical(this,"Error",ex);
    }
}
void MyMem::hideTrayWindow()
{
    this->hideAction->setDisabled(true);
    this->showAction->setDisabled(false);
    hide();
}

void MyMem::closeEvent(QCloseEvent *evt)
{
    if(this->isClose)
    {
        evt->accept();
        return;
    }
    if(this->tray->isVisible())
    {
        hide();
        //This is prevent from closing the window. Unless Exit menu is clicked. :)
        evt->ignore();
    }
}
void MyMem::showTrayWindow()
{
    this->isClose = false;
    this->showAction->setDisabled(true);
    this->hideAction->setDisabled(false);
    show();
}
void MyMem::closeTrayWindow()
{
    this->isClose = true;
    close();
}

void MyMem::createActions()
{
    this->showAction = new QAction(tr("&Show"),this);
    connect(this->showAction,SIGNAL(triggered()),this,SLOT(showTrayWindow()));
    this->hideAction = new QAction(tr("&Hide"),this);
    connect(this->hideAction,SIGNAL(triggered()),this,SLOT(hideTrayWindow()));
    this->closeAction = new QAction(tr("&Exit"),this);
    connect(this->closeAction,SIGNAL(triggered()),this,SLOT(closeTrayWindow()));
}
void MyMem::createTrayMenu()
{
    QMenu *menu = new QMenu(this);
    //Lest us put all actions on menu.
    menu->addAction(this->showAction);
    menu->addAction(this->hideAction);
    menu->addAction(this->closeAction);
    this->tray = new QSystemTrayIcon(this);
    this->tray->setContextMenu(menu);
    this->tray->setIcon(QIcon(":/new/prefix1/images/icon.png"));
    this->tray->setToolTip(tr("Find your memory usage :)"));
    //Lets us show tray.
    this->tray->show();
}
MyMem::~MyMem()
{
    delete ui;
}
