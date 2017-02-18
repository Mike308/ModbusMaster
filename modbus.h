#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QModbusDataUnit>
#include <QModbusRtuSerialMaster>
#include <QSerialPort>
#include <QDebug>


class Modbus : public QObject
{

    Q_OBJECT

public:
    Modbus();
    bool connectToSlave(QString port, int baud);

private:
    QModbusReply *modbusReply;
    QModbusClient *modbusSlave;




};

#endif // MODBUS_H
