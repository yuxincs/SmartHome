#ifndef INTERFACE_H
#define INTERFACE_H
#include <QObject>
#include "model.h"
#include "serialcommunicator.h"
#include "adc.h"
#include "motor.h"
#include "light.h"


class Interface : public QObject
{
    Q_OBJECT

public:
    Interface(unsigned short io8251, unsigned short io8253, unsigned short io8255, unsigned short io0809);
    ~Interface();
    void setup();

signals:
    void log(const QString & message);
    void fatal(const QString & message);
    void send(unsigned char data);
    void changeSpeed(unsigned char rank);
    void changeLightStatus(unsigned char data);
    
private:
    unsigned short io8251, io8253, io8255, io0809;
    SerialCommunicator * communicator;
    ADC * adc;
    Motor * motor;
    Light * light;
    void handleReceived(unsigned char receivedData);
    void handleCollected(unsigned char collectedData);
};

#endif
