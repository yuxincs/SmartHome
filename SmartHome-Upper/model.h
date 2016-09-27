#ifndef MODEL_H
#define MODEL_H
#include <QObject>
#include <QMutex>
#include <QList>

class Interface;

class Model : public QObject 
{
    Q_OBJECT

public:
    Model(Interface * parent);
    ~Model();
    static bool start();
    static void clean();
signals:
    void log(const QString & message);
    void fatal(const QString & message);

protected:
    void readPort(unsigned short address, unsigned char * data);
    void writePort(unsigned short address, unsigned char data);

private:
    void sleep(unsigned long msec);
};

#endif
