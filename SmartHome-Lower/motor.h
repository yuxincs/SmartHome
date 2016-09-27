#ifndef MOTOR_H
#define MOTOR_H
#include <QObject>
#include <QTimer>
#include "model.h"

class Motor : public Model 
{
    Q_OBJECT

public:
    Motor(unsigned short io8255, Interface * parent);
    ~Motor();
    void setup();
    void changeSpeed(unsigned char rank);

private:
    unsigned short io8255;
    unsigned char outputBuffer;
    QTimer *timer;
    bool isRankToUpdate;
    unsigned char rank;
    void run();
};

#endif