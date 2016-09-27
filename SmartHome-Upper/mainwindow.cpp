#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupProgressBar();

    this->setWindowFlags(Qt::FramelessWindowHint);
    inter = new Interface(0x2B8, 0x280, 0x288);
    QThread * thread = new QThread;
    inter->moveToThread(thread);
    connect(thread, &QThread::started, inter, &Interface::startup);
    connect(qApp, &QApplication::aboutToQuit, thread, &QObject::deleteLater);
    thread->start();
    
    connect(inter, &Interface::temperatureChanged, this, &MainWindow::temperatureChanged);
    connect(inter, &Interface::brightnessChanged, this, &MainWindow::brightnessChanged);
    connect(inter, &Interface::rankChanged, this, &MainWindow::rankChanged);
    this->ui->temperature->setRange(0, 127);
    this->ui->brightness->setRange(0, 127);
    this->ui->rank->setRange(0, 7);

    connect(inter, &Interface::log, this, &MainWindow::log);
    connect(inter, &Interface::fatal, this, &MainWindow::fatal);
    
    connect(this->ui->closeButton, &QPushButton::clicked, qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::temperatureChanged(unsigned char newValue)
{
    this->ui->temperature->setValue(newValue);
    float ratio = float(newValue) / 127;
    if (ratio < 0.33)
        this->ui->temperature->setStyleSheet(QString("QProgressBar::chunk { background-color: rgb(15, 170, 209) }"));
    else if (ratio >= 0.33 && ratio < 0.66)
        this->ui->temperature->setStyleSheet(QString("QProgressBar::chunk { background-color: rgb(0, 179, 80) }"));
    else
        this->ui->temperature->setStyleSheet(QString("QProgressBar::chunk { background-color: rgb(253, 96, 45) }"));
}

void MainWindow::brightnessChanged(unsigned char newValue)
{
    this->ui->brightness->setValue(newValue);
}

void MainWindow::rankChanged(unsigned char newValue)
{
    this->ui->rank->setValue(newValue);
}

void MainWindow::log(const QString & message)
{
    qDebug() << message;
}

void MainWindow::fatal(const QString & message)
{
    QMessageBox::warning(this, "Fatal Error!", message);
    qApp->quit();
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if (ui->titleWidget->rect().contains(event->pos()))
    {
        isDragging = true;
        origin = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * event)
{
    if ((event->buttons() & Qt::LeftButton) && isDragging)
        move(event->globalX() - origin.x(), event->globalY() - origin.y());
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    isDragging = false;
}

void MainWindow::setupProgressBar()
{
    this->ui->rank->setArcPen(QPen(QColor(252, 192, 53), 8, Qt::SolidLine));
    this->ui->rank->setValuePen(QPen(QColor(252, 192, 53), 4, Qt::SolidLine));
    this->ui->rank->setValueFont(QFont("Segoe UI", 48, 5));
    this->ui->rank->setTitlePen(QPen(Qt::white, 2, Qt::SolidLine));
    this->ui->rank->setTitleFont(QFont("Segoe UI", 14, 2));
    this->ui->rank->setTitle("Fan Speed");
}
