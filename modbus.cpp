#include "modbus.h"

Modbus::Modbus()
{

}


bool Modbus::connectToSlave(QString port, int baud){


    if (!modbusSlave) return false;

    if (modbusSlave->state() != QModbusDevice::ConnectedState){

        modbusSlave->setConnectionParameter(QModbusDevice::SerialPortNameParameter,port);
        modbusSlave->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);
        modbusSlave->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,baud);
        modbusSlave->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
        modbusSlave->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);
        modbusSlave->setTimeout(1000);
        modbusSlave->setNumberOfRetries(3);

    }

    if (!modbusSlave->connectDevice()){

        return false;
    }else{

        return true;

    }


}

QModbusDataUnit Modbus::prepareRequest(int regAdress, int regType){

    return QModbusDataUnit(regType, regAdress);

}

void Modbus::executeReadRequest(int slaveAdress, int regAdress, int regType){

    if (!modbusSlave) return;

    if (auto *reply = modbusSlave->sendReadRequest(prepareRequest(regAdress,regType),slaveAdress)){

        if (!reply->isFinished())

            //TODO: need connect signal to slot

            else

            delete reply;



    }else{

        qDebug () << "Error: " << modbusSlave->errorString();

    }

}








