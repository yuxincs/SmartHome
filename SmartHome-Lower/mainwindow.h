#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void log(const QString & message);
    void fatal(const QString & message);
    
private:
    Ui::MainWindow *ui;
    Interface * inter;
};

#endif // MAINWINDOW_H
