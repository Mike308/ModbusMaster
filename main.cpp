#include <QCoreApplication>
#include "modbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Modbus mb;

    mb.connectToSlave("COM2",19200);
    mb.executeReadRequest(10,100,4);

    return a.exec();
}
