#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QDebug>
#include <QElapsedTimer>
#include "serialcommunicator.h"
#include "light.h"

class Interface : public QObject
{
    Q_OBJECT
public:
    Interface(unsigned short io8251, unsigned short io8253, unsigned short io8255);
    ~Interface();
    void startup();

signals:
    void log(const QString & message);
    void fatal(const QString & message);
    void temperatureChanged(unsigned char newValue);
    void brightnessChanged(unsigned char newValue);
    void rankChanged(unsigned char newValue);
    void changeLightStatus(unsigned char data);
    void send(unsigned char data);
    
private:
    SerialCommunicator * communicator;
    Light * light;
    unsigned short io8251, io8253, io8255;
    unsigned char command;
    void handleReceived(unsigned char receivedData);
};

#endif
