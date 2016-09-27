#pragma once
#include <QObject>
#include "model.h"

class Light : public Model 
{
	Q_OBJECT

public:
	Light(unsigned short io8255, Interface * parent);
	~Light();
    void setup();
    void changeStatus(unsigned char data);

private:
    unsigned char io8255;
};
