#include "inputamount.h"
#include "ui_inputamount.h"
#include <QCloseEvent>

inputAmount::inputAmount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inputAmount)
{
    ui->setupUi(this);
    connect(ui->btnEnter,&QPushButton::clicked,this,&inputAmount::enterButtonHandler);
    connect(ui->btnClear,&QPushButton::clicked,this,&inputAmount::clearButtonHandler);
    connect(ui->btn1,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn2,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn3,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn4,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn5,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn6,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn7,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn8,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn9,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
    connect(ui->btn0,&QPushButton::clicked,this,&inputAmount::numberButtonsHandler);
}

inputAmount::~inputAmount()
{
    delete ui;
}

void inputAmount::numberButtonsHandler()
{

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button){
        QString buttonText = button->text();
        ui->amountField->setText(ui->amountField->text()+ buttonText);
    }
}

void inputAmount::enterButtonHandler()
{
    amount = ui->amountField->text();
    emit sendAmount(amount);
    ui->amountField->clear();
}

void inputAmount::clearButtonHandler()
{
    QString currentText = ui->amountField->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        ui->amountField->setText(currentText);
    }
}

void inputAmount::closeEvent(QCloseEvent *event)
{
    ui->amountField->clear();
    event->accept();
}

void inputAmount::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}


