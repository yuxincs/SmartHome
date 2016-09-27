#ifndef ADC_H
#define ADC_H

#include <QObject>
#include <QTimer>
#include "model.h"

class ADC : public Model 
{
    Q_OBJECT

public:
    ADC(unsigned short io0809, Interface * parent);
    ~ADC();
    void setup();

signals:
    void collected(unsigned char data);
    
private:
    enum CollectType
    {
        IN0, IN1, IN2
    };
    unsigned short io0809;
    CollectType nextToCollect;
    void collect();
};

#endif