#include "pin_ui.h"
#include "ui_pin_ui.h"
#include <QRegularExpressionValidator>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>

PIN_UI::PIN_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PIN_UI)
    ,setPinTime(0)
{
    ui->setupUi(this);
    pQTimer = new QTimer(this);
    ui->pinInput->setEchoMode(QLineEdit::Password);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("\\d{4}"),this);
    ui->pinInput->setValidator(validator);

    connect(ui->pinOk,&QPushButton::clicked,this,&PIN_UI::sendPin);
    connect(ui->clearButt,&QPushButton::clicked,this,&PIN_UI::clearButton);
    connect(ui->button0,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button1,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button2,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button3,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button4,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button5,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button6,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button7,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button8,&QPushButton::clicked,this,&PIN_UI::numberButtons);
    connect(ui->button9,&QPushButton::clicked,this,&PIN_UI::numberButtons);

    connect(pQTimer,&QTimer::timeout,this,&PIN_UI::timeout);

    progressTimer = new QTimer(this);
    connect(progressTimer,&QTimer::timeout,this,[this]() {
        elapsedSeconds++;

        if (elapsedSeconds >= 7 && elapsedSeconds <= 10) {
            int remaining = 10 - elapsedSeconds;

            if (!ui->timeoutBar->isVisible())
                ui->timeoutBar->setVisible(true);

            ui->timeoutBar->setMaximum(3);
            ui->timeoutBar->setValue(remaining);
    }

        if (elapsedSeconds >= 10) {
            progressTimer->stop();
        }
    });

    ui->timeoutBar->setVisible(false);

}

PIN_UI::~PIN_UI()
{
    delete ui;
}

void PIN_UI::numberButtons()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonText = button->text();
        if (ui->pinInput->text().length() < 4) {
            ui->pinInput->setText(ui->pinInput->text() + buttonText);
            startTimer();
        }
    }
}

void PIN_UI::clearButton()
{
    ui->pinInput->clear();
    startTimer();
    elapsedSeconds = 0;
    ui->timeoutBar->setVisible(false);
    ui->timeoutBar->setMaximum(3);
    ui->timeoutBar->setValue(3);
}

void PIN_UI::sendPin()
{
    QString pin = ui->pinInput->text();
    if (pin.length() == 4) {
    emit sendPinToExe(pin);
    ui->pinInput->clear();
    pQTimer->stop();
    }
}

void PIN_UI::timeout()
{
    resetPinUI();
    this->close();
    QMessageBox::warning(this, tr("Error"), tr("Timeout"));
}

void PIN_UI::startTimer()
{
    pQTimer->start(10000);
    progressTimer->start(1000);
    elapsedSeconds = 0;
    ui->timeoutBar->setVisible(false);
    ui->timeoutBar->setMaximum(3);
    ui->timeoutBar->setValue(3);
}

void PIN_UI::resetPinUI()
{
    ui->pinInput->clear();
    pQTimer->stop();
    progressTimer->stop();
    elapsedSeconds = 0;
    ui->timeoutBar->setVisible(false);
    ui->timeoutBar->setValue(3);
}

void PIN_UI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}

void PIN_UI::showEvent(QShowEvent *timer)
{
    QDialog::showEvent(timer);
    startTimer();
}

void PIN_UI::closeEvent(QCloseEvent *event)
{
    ui->pinInput->clear();
    pQTimer->stop();
    event->accept();
}


