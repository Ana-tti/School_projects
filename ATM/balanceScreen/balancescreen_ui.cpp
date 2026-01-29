#include "balancescreen_ui.h"
#include "ui_balancescreen_ui.h"

balanceScreen_UI::balanceScreen_UI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::balanceScreen_UI)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);
}

balanceScreen_UI::~balanceScreen_UI()
{
    delete ui;
}

void balanceScreen_UI::setBalance(const QString balance)
{

    ui->labelBalance->setText("Balance: " + balance + " €");
}

void balanceScreen_UI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
