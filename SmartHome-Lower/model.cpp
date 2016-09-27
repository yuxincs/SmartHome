#include "model.h"
#include "ApiEx.h"
#include <QtCore>
#include "interface.h"
#pragma comment(lib, "ApiEx.lib")

Model::Model(Interface * parent)
{
    connect(this, &Model::log, parent, &Interface::log);
    connect(this, &Model::fatal, parent, &Interface::fatal);
}

Model::~Model() 
{
    
}

bool Model::start()
{
    return Startup();
}

void Model::clean()
{
    Cleanup();
}

void Model::readPort(unsigned short address, unsigned char * data)
{
    PortReadByte(address, data);
    sleep(20);
}

void Model::writePort(unsigned short address, unsigned char data)
{
    PortWriteByte(address, data);
    sleep(20);
}

void Model::sleep(unsigned long msec)
{
    QElapsedTimer timer;
    while (timer.elapsed() < msec)
        QCoreApplication::processEvents();
}
