#include <QThread>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inter = new Interface(0x2B8, 0x280, 0x288, 0x298);
    QThread * thread = new QThread;
    inter->moveToThread(thread);
    connect(thread, &QThread::started, inter, &Interface::setup);
    connect(qApp, &QApplication::aboutToQuit, thread, &QObject::deleteLater);
    thread->start();

    connect(inter, &Interface::log, this, &MainWindow::log);
    connect(inter, &Interface::fatal, this, &MainWindow::fatal);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log(const QString & message)
{
    this->ui->log->append(message);
}

void MainWindow::fatal(const QString & message)
{
    QMessageBox::warning(this, "Fatal Error!", message);
    qApp->quit();
}