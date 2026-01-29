#include "transferreceiverwindow.h"
#include "ui_transferreceiverwindow.h"
#include <QCloseEvent>

transferReceiverWindow::transferReceiverWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transferReceiverWindow)
{
    ui->setupUi(this);
    connect(ui->numButton0,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton1,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton2,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton3,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton4,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton5,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton6,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton7,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton8,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->numButton9,&QPushButton::clicked,this,&transferReceiverWindow::numButtonHandler);
    connect(ui->eraseButton,&QPushButton::clicked,this,&transferReceiverWindow::eraseButtonHandler);
    connect(ui->enterButton,&QPushButton::clicked,this,&transferReceiverWindow::enterButtonHanlder);
}

transferReceiverWindow::~transferReceiverWindow()
{
    delete ui;
}

void transferReceiverWindow::numButtonHandler()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonText = button->text();
        ui->accountNumberField->setText(ui->accountNumberField->text() + buttonText);
    }
}

void transferReceiverWindow::eraseButtonHandler()
{
    ui->accountNumberField->clear();
}

void transferReceiverWindow::enterButtonHanlder()
{
    QString accountNumber = ui->accountNumberField->text();
    emit sendAccountNumber(accountNumber);
    this->close();
}

void transferReceiverWindow::closeEvent(QCloseEvent *event)
{
    ui->accountNumberField->clear();
    event->accept();
}

void transferReceiverWindow::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
