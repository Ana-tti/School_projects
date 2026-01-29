#include "creditpaymentui.h"
#include "ui_creditpaymentui.h"

creditPaymentUI::creditPaymentUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditPaymentUI)
{
    ui->setupUi(this);
    ptrInput = new inputAmount(this);

    connect(ui->btnChooseAmount,&QPushButton::clicked,
            this,&creditPaymentUI::chooseAmount);
    connect(ui->btnPayAll,&QPushButton::clicked,
            this,&creditPaymentUI::payAll);
    connect(ptrInput,&inputAmount::sendAmount,
            this,&creditPaymentUI::inputSignalHandler);

}

creditPaymentUI::~creditPaymentUI()
{
    delete ui;
}

void creditPaymentUI::setCreditBalance(const QString creditBalance)
{

    ui->creditLimba->setText(creditBalance + " €");
}

void creditPaymentUI::setCreditLimit(const QString creditLimit)
{

    ui->Limba->setText(creditLimit + " €");
}


void creditPaymentUI::payAll()
{
    amount = ui->creditLimba->text().split(" ").first();
    double balance = amount.toDouble();
    QString amountToPay = QString::number(-balance, 'f', 2);
    emit creditPaymentReq(amountToPay);
}

void creditPaymentUI::chooseAmount()
{

    ptrInput->open();
}

void creditPaymentUI::inputSignalHandler(QString a)
{
    amount = a;
    emit creditPaymentReq(amount);
    ptrInput->close();
}

void creditPaymentUI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
