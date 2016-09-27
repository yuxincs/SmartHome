#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H
#include <QObject>
#include <QTimer>
#include <QMutex>
#include "model.h"

class SerialCommunicator : public Model 
{
    Q_OBJECT

public:
    SerialCommunicator(unsigned short io8251, unsigned short io8253, Interface * parent);
    ~SerialCommunicator();
    void setup();
    void send(unsigned char data);
    bool isBusy();

signals:
    void received(unsigned char data);
    
private:
    unsigned short io8251, io8253;
    bool isReceiveCommandSet;
    bool isWorking;
    void receive();
};

#endif