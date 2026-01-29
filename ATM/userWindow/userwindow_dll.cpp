#include "userwindow_dll.h"
#include "ui_userwindow_dll.h"

userWindow_dll::userWindow_dll(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::userWindow_dll)
{
    ui->setupUi(this);
    connect(ui->balanceButton,&QPushButton::clicked,this,&userWindow_dll::balanceButtonHandler);
    connect(ui->depositButton,&QPushButton::clicked,this,&userWindow_dll::depositButtonHandler);
    connect(ui->logoutButton,&QPushButton::clicked,this,&userWindow_dll::logoutButtonHandler);
    connect(ui->withdrawButton,&QPushButton::clicked,this,&userWindow_dll::withdrawButtonHandler);
    connect(ui->transactionButton,&QPushButton::clicked,this,&userWindow_dll::transactionButtonHandler);
    connect(ui->transferButton,&QPushButton::clicked,this,&userWindow_dll::transferButtonHandler);
    connect(ui->creditWithdrawBtn,&QPushButton::clicked,this,&userWindow_dll::creditWithdrawButtonHandler);
    connect(ui->creditPaymentBtn,&QPushButton::clicked,this,&userWindow_dll::creditPaymentButtonHandler);
}

userWindow_dll::~userWindow_dll()
{
    delete ui;
}

void userWindow_dll::setWebToken(const QByteArray token)
{
    webToken = token;
}

void userWindow_dll::setClientName(const QString fname, const QString lname)
{
    ui->fname->setText(fname);
    ui->lname->setText(lname);
}

void userWindow_dll::balanceButtonHandler()
{
    emit balanceClickSignal();
}

void userWindow_dll::logoutButtonHandler()
{
    webToken.clear();
    this->close();
}

void userWindow_dll::depositButtonHandler()
{
    emit depositClickSignal();
}

void userWindow_dll::withdrawButtonHandler()
{
    emit withdrawClickSignal();
}

void userWindow_dll::transactionButtonHandler()
{
    emit transactionClickSignal();
}

void userWindow_dll::transferButtonHandler()
{
    emit transferClickSignal();
}

void userWindow_dll::creditWithdrawButtonHandler()
{
    emit creditWithdrawClickSignal();
}

void userWindow_dll::creditPaymentButtonHandler()
{
    emit creditPaymentClickSignal();
}

void userWindow_dll::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
