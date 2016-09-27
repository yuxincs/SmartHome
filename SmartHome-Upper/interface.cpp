#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QThread>
#include "interface.h"

void Interface::handleReceived(unsigned char receivedData)
{
    // if it's reporting for temperature
    if ((receivedData & 0x80) == 0x80)
    {
        unsigned char temperature = receivedData & ~0x80;
        emit temperatureChanged(temperature);
        float ratio = float(temperature) / 127;
        if (ratio < 0.33)
        {
            command &= ~0xC0;
            command |= 0x30;
        }
        else if (ratio >= 0.33 && ratio <= 0.66)
        {
            command &= ~0xA8;
            command |= 0x40;
        }
        else
        {
            command &= ~0x60;
            command |= 0x88;
        }

        command &= ~0x07;
        unsigned int rank = float(temperature) / 127 * 7 + 0.5;
        command |= rank;
        emit rankChanged(rank);
    }
    else
    {
        unsigned char brightness = receivedData & ~0x80;
        float ratio = float(brightness) / 127;
        emit brightnessChanged(brightness);
        if (ratio <= 0.5)
            command |= 0x10;
        else
            command &= ~0x10;
    }

    // write the new command to 8255
    emit changeLightStatus(command);

    emit send(command);
}


Interface::Interface(unsigned short io8251, unsigned short io8253, unsigned short io8255)
{
    this->io8253 = io8253;
    this->io8251 = io8251;
    this->io8255 = io8255;
}

Interface::~Interface()
{
    Model::clean();
}

void Interface::startup()
{
    emit log("Starting up...");
    if (!Model::start())
        emit fatal("Error! Cannot open device.");

    communicator = new SerialCommunicator(io8251, io8253, this);
    QThread * communicatorThread = new QThread;
    communicator->moveToThread(communicatorThread);
    connect(communicatorThread, &QThread::started, communicator, &SerialCommunicator::setup);
    connect(this, &Interface::send, communicator, &SerialCommunicator::send);
    connect(communicator, &SerialCommunicator::received, this, &Interface::handleReceived);
    communicatorThread->start();

    light = new Light(io8255, this);
    QThread * lightThread = new QThread;
    light->moveToThread(lightThread);
    connect(lightThread, &QThread::started, light, &Light::setup);
    connect(this, &Interface::changeLightStatus, light, &Light::changeStatus);
    lightThread->start();

    this->command = 0x30;

    emit send(this->command);
}
