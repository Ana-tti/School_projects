#include "creditwithdraw_ui.h"
#include "ui_creditwithdraw_ui.h"

creditWithdraw_UI::creditWithdraw_UI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditWithdraw_UI)
{
    ui->setupUi(this);
    ptrInput = new inputAmount(this);
    connect(ui->btn20,&QPushButton::clicked,this,&creditWithdraw_UI::handlebtn20Click);
    connect(ui->btn40,&QPushButton::clicked,this,&creditWithdraw_UI::handlebtn40Click);
    connect(ui->btn60,&QPushButton::clicked,this,&creditWithdraw_UI::handlebtn60Click);
    connect(ui->btn100,&QPushButton::clicked,this,&creditWithdraw_UI::handlebtn100Click);
    connect(ui->btnOther,&QPushButton::clicked,this,&creditWithdraw_UI::handlebtnOtherClick);
    connect(ptrInput,&inputAmount::sendAmount,this,&creditWithdraw_UI::inputSignalHandler);
}

creditWithdraw_UI::~creditWithdraw_UI()
{
    delete ui;
}

void creditWithdraw_UI::handlebtn20Click()
{

    amount = "20";
    emit creditWithdrawReq(amount);
}

void creditWithdraw_UI::handlebtn40Click()
{
    amount = "40";
    emit creditWithdrawReq(amount);
}

void creditWithdraw_UI::handlebtn60Click()
{
    amount = "60";
    emit creditWithdrawReq(amount);
}

void creditWithdraw_UI::handlebtn100Click()
{
    amount = "100";
    emit creditWithdrawReq(amount);
}

void creditWithdraw_UI::handlebtnOtherClick()
{
    ptrInput->open();
}

void creditWithdraw_UI::inputSignalHandler(QString c)
{
    amount = c;
    emit creditWithdrawReq(amount);
    ptrInput->close();
}

void creditWithdraw_UI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QDialog::changeEvent(change);
}
