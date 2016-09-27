#include <windows.h>
#include <QDebug>
#include "motor.h"

Motor::Motor(unsigned short io8255, Interface * parent) : Model(parent)
{
    this->io8255 = io8255;
    this->isRankToUpdate = false;
}

Motor::~Motor() 
{
    
}

void Motor::setup()
{
    writePort(io8255 + 3, 0x80);
    outputBuffer = 0x33;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Motor::run);
    timer->start(50);
}

void Motor::changeSpeed(unsigned char rank)
{
    if (this->rank != rank)
    {
        this->rank = rank;
        this->isRankToUpdate = true;
    }
}

void Motor::run()
{
    if (isRankToUpdate)
    {
        timer->setInterval(100 * rank / ((rank + 1) * (rank + 1)));
        isRankToUpdate = false;
    }
    writePort(io8255, outputBuffer);
    outputBuffer = (outputBuffer << 1) | (outputBuffer >> 3);
}
