#include "light.h"


Light::Light(unsigned short io8255, Interface * parent)
    :Model(parent)
{
    this->io8255 = io8255;
}

Light::~Light() 
{
    
}

void Light::setup()
{
    writePort(io8255 + 3, 0x80);
}

void Light::changeStatus(unsigned char data)
{
    writePort(io8255 + 1, data);
}
