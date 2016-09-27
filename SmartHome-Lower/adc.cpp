#include "adc.h"


ADC::ADC(unsigned short io0809, Interface * parent)
    :Model(parent)
{
    this->io0809 = io0809;
    this->nextToCollect = CollectType::IN0;
}

ADC::~ADC()
{
    
}

void ADC::setup()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ADC::collect);
    timer->start(1000);
}

void ADC::collect()
{
    if (nextToCollect == CollectType::IN0)
    {
        unsigned char in0CollectedData = 0;
        writePort(io0809, 0x00);
        readPort(io0809, &in0CollectedData);
        in0CollectedData = float(in0CollectedData) / 255 * 127 + 0.5;
        in0CollectedData = in0CollectedData | (1 << 7);

        emit collected(in0CollectedData);
        nextToCollect = CollectType::IN1;
    }
    else if (nextToCollect == CollectType::IN1)
    {
        unsigned char in1CollectedData = 0;
        writePort(io0809 + 1, 0x00);
        readPort(io0809 + 1, &in1CollectedData);
        in1CollectedData = in1CollectedData - 0x80;

        emit collected(in1CollectedData);
        nextToCollect = CollectType::IN0;
    }
}
