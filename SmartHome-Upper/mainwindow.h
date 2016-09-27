#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Interface.h"

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
    void temperatureChanged(unsigned char newValue);
    void brightnessChanged(unsigned char newValue);
    void rankChanged(unsigned char newValue);
    void log(const QString & message);
    void fatal(const QString & message);

protected:
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);

private:
    Interface * inter;
    Ui::MainWindow *ui;
    QPoint origin;
    bool isDragging;
    void setupProgressBar();
};

#endif // MAINWINDOW_H
