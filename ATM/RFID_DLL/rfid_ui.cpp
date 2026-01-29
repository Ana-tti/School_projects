#include "rfid_ui.h"
//#include "ui_rfid_ui.h"

rfid_UI::rfid_UI(QWidget *parent)
    : QDialog(parent)
     //,ui(new Ui::rfid_UI)
{
    //ui->setupUi(this);
    port = new QSerialPort(this);
    connect(port,&QSerialPort::readyRead,
            this,&rfid_UI::handleReader);
    //show();
}

rfid_UI::~rfid_UI()
{
    //delete ui;
}

bool rfid_UI::openPort()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        port->setPortName(portInfo.portName());
    }
    if(port->portName() == ""){

        return false;
    }

    if(port->open(QIODeviceBase::ReadOnly)==false){

        return false;
    }


    return true;
}

void rfid_UI::closePort()
{

    port->close();
}

void rfid_UI::handleReader()
{

    QByteArray byteArray = port->readAll();
    QByteArray subArray = byteArray.mid(3, byteArray.size() - 6);
    QString str = QString::fromUtf8(subArray);
    emit sendRfidToExe(str);
}
