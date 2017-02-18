#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QModbusDataUnit>
#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QDebug>

class QModbusReply;
class QModbusClient;


class Modbus : public QObject
{

    Q_OBJECT

public:
    Modbus();
    bool connectToSlave(QString port, int baud);
    void executeReadRequest(int slaveAdress, int regAdress, int regType); //passing adress of slave, adress of register and register type

private:
    QModbusReply *modbusReply;
    QModbusClient *modbusSlave;

    QModbusDataUnit prepareRequest(int regAdress, int regType);

private slots:
    void readReady();








};

#endif // MODBUS_H
