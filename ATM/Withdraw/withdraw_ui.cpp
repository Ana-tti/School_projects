#include "withdraw_ui.h"
#include "ui_withdraw_ui.h"

Withdraw_UI::Withdraw_UI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Withdraw_UI)
{
    ui->setupUi(this);
    ptrInput = new inputAmount(this);
    connect(ui->btn20,&QPushButton::clicked,this,&Withdraw_UI::handlebtn20Click);
    connect(ui->btn40,&QPushButton::clicked,this,&Withdraw_UI::handlebtn40Click);
    connect(ui->btn60,&QPushButton::clicked,this,&Withdraw_UI::handlebtn60Click);
    connect(ui->btn100,&QPushButton::clicked,this,&Withdraw_UI::handlebtn100Click);
    connect(ui->btnOther,&QPushButton::clicked,this,&Withdraw_UI::handlebtnOtherClick);
    connect(ptrInput,&inputAmount::sendAmount,this,&Withdraw_UI::inputSignalHandler);
}

Withdraw_UI::~Withdraw_UI()
{
    delete ui;
}

void Withdraw_UI::handlebtn20Click()
{
    amount = "20";

    emit withdrawReq(amount);
}

void Withdraw_UI::handlebtn40Click()
{
    amount = "40";
    emit withdrawReq(amount);
}

void Withdraw_UI::handlebtn60Click()
{
    amount = "60";
    emit withdrawReq(amount);
}

void Withdraw_UI::handlebtn100Click()
{
    amount = "100";
    emit withdrawReq(amount);
}

void Withdraw_UI::handlebtnOtherClick()
{
    ptrInput->open();
}

void Withdraw_UI::inputSignalHandler(QString s)
{
    amount = s;
    emit withdrawReq(amount);
    ptrInput->close();
}

void Withdraw_UI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
