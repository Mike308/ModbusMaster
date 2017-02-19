#include <QCoreApplication>
#include "modbus.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Modbus * mb = new Modbus();

    mb->connectToSlave("COM2",19200);
    mb->executeReadRequest(10,100,Modbus::HoldingRegisters);
    mb->executeWriteRequest(10,10,Modbus::Coils,1);


   // mb.connectToSlave("COM2",19200);
   // mb.executeReadRequest(10,100,Modbus::HoldingRegisters);

    return a.exec();
}
