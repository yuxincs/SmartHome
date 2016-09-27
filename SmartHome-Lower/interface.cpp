#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QThread>
#include "interface.h"


void Interface::handleReceived(unsigned char receivedData)
{
    unsigned char motorRank = receivedData & 0x07;
    emit changeSpeed(motorRank);
    emit log("Motor Speed Changed to : " + QString::number(motorRank));

    unsigned char lightSwitch = (receivedData & 0x10) >> 4;
    emit changeLightStatus(lightSwitch);
}


void Interface::handleCollected(unsigned char collectedData)
{
    // simply send the collected data out
    emit send(collectedData);
}


Interface::Interface(unsigned short io8251, unsigned short io8253, unsigned short io8255, unsigned short io0809)
{
    this->io8251 = io8251;
    this->io8253 = io8253;
    this->io0809 = io0809;
    this->io8255 = io8255;
}

Interface::~Interface()
{
    Model::clean();
    delete communicator;
    delete adc;
    delete motor;
    delete light;
}

void Interface::setup()
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

    adc = new ADC(io0809, this);
    QThread * adcThread = new QThread;
    adc->moveToThread(adcThread);
    connect(adcThread, &QThread::started, adc, &ADC::setup);
    connect(adc, &ADC::collected, this, &Interface::handleCollected);
    adcThread->start();

    motor = new Motor(io8255, this);
    QThread * motorThread = new QThread;
    motor->moveToThread(motorThread);
    connect(motorThread, &QThread::started, motor, &Motor::setup);
    connect(this, &Interface::changeSpeed, motor, &Motor::changeSpeed);
    motorThread->start();

    light = new Light(io8255, this);
    QThread * lightThread = new QThread;
    light->moveToThread(lightThread);
    connect(lightThread, &QThread::started, light, &Light::setup);
    connect(this, &Interface::changeLightStatus, light, &Light::changeStatus);
    lightThread->start();
}



