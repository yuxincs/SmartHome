#include "serialcommunicator.h"
#include <QTimer>
#include <qDebug>


SerialCommunicator::SerialCommunicator(unsigned short io8251, unsigned short io8253, Interface * parent)
    :Model(parent)
{
    this->io8251 = io8251;
    this->io8253 = io8253;
    this->isReceiveCommandSet = false;
    this->isWorking = false;
}

SerialCommunicator::~SerialCommunicator() 
{
	
}

void SerialCommunicator::setup()
{
    // initialize 8253 with 3 method
    writePort(this->io8253 + 3, 0x36);
    writePort(this->io8253, 0x30);
    writePort(this->io8253, 0x00);

    // poll to receive
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SerialCommunicator::receive);
    timer->start(50);
}


void SerialCommunicator::receive()
{
    // prepare to receive
    if (!isReceiveCommandSet)
    {
        writePort(io8251 + 1, 0x00);
        writePort(io8251 + 1, 0x40);
        writePort(io8251 + 1, 0xcf);
        writePort(io8251 + 1, 0x14);
        this->isReceiveCommandSet = true;
    }

    // check status
    unsigned char temp = 0;
    readPort(io8251 + 1, &temp);
    if (!(temp & 0x02))
        return;

    // do receive
    readPort(io8251, &temp);
    emit log("Received " + QString::number(temp, 16));

    isReceiveCommandSet = false;

    emit received(temp);
}

void SerialCommunicator::send(unsigned char data)
{
    // prepare to send
    writePort(io8251 + 1, 0x00);
    writePort(io8251 + 1, 0x40);

    // prepare to send
    writePort(io8251 + 1, 0xcf);   // Method Command Word
    writePort(io8251 + 1, 0x37);   // Work Command Word

    unsigned char temp = 0;
    // check if it's ready to send
    do
    {
        readPort(io8251 + 1, &temp);
    } while (!(temp & 0x01));

    // do send
    writePort(io8251, data);

    emit log(QString::number(data, 16) + " Sent.");
    
}

bool SerialCommunicator::isBusy()
{
    return this->isWorking;
}
