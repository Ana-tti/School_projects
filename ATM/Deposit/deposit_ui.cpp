#include "deposit_ui.h"
#include "ui_deposit_ui.h"

deposit_ui::deposit_ui(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::d)
{
    ui->setupUi(this);
    ptrInput = new inputAmount(this);

    connect(ui->btn20,&QPushButton::clicked,this,&deposit_ui::handlebtn20Click);
    connect(ui->btn40,&QPushButton::clicked,this,&deposit_ui::handlebtn40Click);
    connect(ui->btn60,&QPushButton::clicked,this,&deposit_ui::handlebtn60Click);
    connect(ui->btn100,&QPushButton::clicked,this,&deposit_ui::handlebtn100Click);
    connect(ui->btnOther,&QPushButton::clicked,this,&deposit_ui::handlebtnOtherClick);
    connect(ptrInput,&inputAmount::sendAmount,this,&deposit_ui::inputSignalHandler);
}

deposit_ui::~deposit_ui()
{
    delete ui;
}

void deposit_ui::inputSignalHandler(QString a)
{
    amount = a;
    emit depositReq(amount);
    ptrInput->close();
}

void deposit_ui::handlebtn20Click()
{
    amount = "20";
    emit depositReq(amount);
}

void deposit_ui::handlebtn40Click()
{
    amount = "40";
    emit depositReq(amount);
}

void deposit_ui::handlebtn60Click()
{
    amount = "60";
    emit depositReq(amount);
}

void deposit_ui::handlebtn100Click()
{
    amount = "100";
    emit depositReq(amount);
}

void deposit_ui::handlebtnOtherClick()
{

    ptrInput->open();
}

void deposit_ui::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
