#ifndef RFID_UI_H
#define RFID_UI_H

#include <QDialog>
#include "RFID_global.h"
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class rfid_UI;
}

class RFID_EXPORT rfid_UI : public QDialog
{
    Q_OBJECT

public:
    explicit rfid_UI(QWidget *parent = nullptr);
    ~rfid_UI();
    bool openPort();
    void closePort();
signals:
    void sendRfidToExe(QString);
private slots:
    void handleReader();

private:
    Ui::rfid_UI *ui;
    QSerialPort * port;
};

#endif // RFID_UI_H
