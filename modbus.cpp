#include "modbus.h"

Modbus::Modbus(){

    modbusSlave = new QModbusRtuSerialMaster(this);


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

    return QModbusDataUnit( (QModbusDataUnit::RegisterType)regType, regAdress,1);

}

void Modbus::executeReadRequest(int slaveAdress, int regAdress, int regType){

    if (!modbusSlave) return;

    if (auto *reply = modbusSlave->sendReadRequest(prepareRequest(regAdress,regType),slaveAdress)){

        if (!reply->isFinished())

            //TODO: need connect signal to slot
            connect(reply,&QModbusReply::finished,this,&Modbus::readReady);


            else

            delete reply;



    }else{

        qDebug () << "Error: " << modbusSlave->errorString();

    }

}

void Modbus::readReady(){

    auto reply = qobject_cast<QModbusReply*>(sender());

    if (!reply) return;

    if (reply->error()==QModbusDevice::NoError){

        const QModbusDataUnit modbusDataUnit = reply->result();

        for (uint i=0; i<modbusDataUnit.valueCount();i++){

            qDebug () << "Value: " << modbusDataUnit.value(i);

        }

    }

    else if (reply->error()==QModbusDevice::ProtocolError){

        qDebug () << "Protocol error: " << reply->errorString();

    }else {

        qDebug () << "Error: " << reply->errorString();

    }


}








