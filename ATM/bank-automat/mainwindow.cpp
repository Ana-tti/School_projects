#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrRfid_dll = new rfid_UI(this);
    ptrPin_dll = new PIN_UI(this);
    ptrRest = new rest;
    ptrUserWindow = new userWindow_dll(this);
    ptrWithdraw = new Withdraw_UI(this);
    ptrCreditWithdraw = new creditWithdraw_UI(this);
    ptrCreditPayment = new creditPaymentUI(this);
    ptrDeposit = new deposit_ui(this);
    ptrTransactions = new Transactions_UI(this);
    ptrTransferReceiver = new transferReceiverWindow(this);
    ptrInputAmount = new inputAmount(this);
    ptrBalance = new balanceScreen_UI(this);

    ptrRfid_dll->openPort();

    languageComboBox = ui->languageComboBox;
    connect(languageComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::changeLanguage);
    changeLanguage(0);
    connect(ptrRest,&rest::loginSuccess,this,&MainWindow::loginSuccessHandler);
    connect(ptrRest,&rest::loginFailed,this,&MainWindow::loginFailHandler);
    connect(ptrRfid_dll,&rfid_UI::sendRfidToExe,this,&MainWindow::rfidSignalHandler);
    connect(ptrPin_dll,&PIN_UI::sendPinToExe,this,&MainWindow::pinSignalHandler);
    connect(ptrRest,&rest::withdrawSuccess,this,&MainWindow::withdrawSuccessHandler);
    connect(ptrRest,&rest::depositSuccess,this,&MainWindow::depositSuccessHandler);
    connect(ptrRest,&rest::sendTransactionData,this,&MainWindow::transactionDataReceiver);
    connect(ptrWithdraw,&Withdraw_UI::withdrawReq,this,&MainWindow::withdrawRequestHandler);
    connect(ptrDeposit,&deposit_ui::depositReq,this,&MainWindow::depositRequestHandler);
    connect(ptrTransferReceiver,&transferReceiverWindow::sendAccountNumber,this,&MainWindow::receiverNumberSignalHandler);
    connect(ptrUserWindow,&userWindow_dll::withdrawClickSignal,this,&MainWindow::withdrawSignalHandler);
    connect(ptrUserWindow,&userWindow_dll::depositClickSignal,this,&MainWindow::depositSignalHandler);
    connect(ptrUserWindow,&userWindow_dll::transferClickSignal,this,&MainWindow::transferSignalHandler);
    connect(ptrUserWindow,&userWindow_dll::transactionClickSignal,this,&MainWindow::transactionSignalHandler);

    connect(ptrUserWindow,&userWindow_dll::creditWithdrawClickSignal,this,&MainWindow::creditWithdrawSignalHandler);
    connect(ptrCreditWithdraw,&creditWithdraw_UI::creditWithdrawReq,this,&MainWindow::creditWithdrawRequestHandler);
    connect(ptrRest,&rest::creditWithdrawSuccess,this,&MainWindow::creditWithdrawSuccesHandler);

    connect(ptrUserWindow,&userWindow_dll::creditPaymentClickSignal,this,&MainWindow::creditPaymentSignalHandler);
    connect(ptrCreditPayment,&creditPaymentUI::creditPaymentReq,this,&MainWindow::creditPaymentRequestHandler);
    connect(ptrRest,&rest::creditPaymentSuccess,this,&MainWindow::creditPaymentSuccessHandler);

    connect(ptrInputAmount,&inputAmount::sendAmount,this,&MainWindow::transferAmountHAndler);
    connect(ptrUserWindow,&userWindow_dll::balanceClickSignal,this,&MainWindow::balanceSignalHandler);
    connect(ptrRest,&rest::balanceReady,this,&MainWindow::balanceReadyHandler);

    connect(ptrRest,&rest::creditBalanceReady,this,&MainWindow::creditBalanceReadyHandler);
    connect(ptrRest,&rest::creditLimitReady,this,&MainWindow::creditLimitReadyHandler);

    connect(ptrRest,&rest::clientInfoReady,this,&MainWindow::clienInfoReadyHandler);
    connect(ptrRest,&rest::sendDebitNumber,this,&MainWindow::debitNumberHandler);
    connect(ptrRest,&rest::sendCreditNumber,this,&MainWindow::creditNumberHandler);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rfidSignalHandler(const QString n)
{
    cardNumber = n;
    ptrPin_dll->open();
}

void MainWindow::pinSignalHandler(const QString p)
{
    PinNumber = p;
    ptrRest->login(cardNumber,PinNumber);
}

void MainWindow::loginSuccessHandler()
{
    loginAttempts = 0;
    ptrPin_dll->close();
    ptrUserWindow->open();
    ptrRest->getCardInfo(cardNumber);
    ptrRest->defineDebit(cardNumber);
    ptrRest->defineCredit(cardNumber);
}

void MainWindow::loginFailHandler()
{
    loginAttempts +=1;
    if(loginAttempts == 3){
        QMessageBox messageBox;
        messageBox.setText(tr("Card locked!"));
        messageBox.exec();
        loginAttempts = 0;
    }
}

void MainWindow::withdrawSuccessHandler()
{
    ptrWithdraw->close();
}

void MainWindow::depositSuccessHandler()
{
    ptrDeposit->close();
}

void MainWindow::depositSignalHandler()
{
    if(debitNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Debit not available"));
        messageBox.exec();
        return;
    }
    ptrDeposit->open();
}

void MainWindow::depositRequestHandler(const QString r)
{
    QString amount =r;
    ptrRest->deposit(amount);
}

void MainWindow::withdrawSignalHandler()
{
    if(debitNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Debit not available"));
        messageBox.exec();
        return;
    }
    ptrWithdraw->open();
}

void MainWindow::withdrawRequestHandler(const QString r)
{
    QString amount = r;
    ptrRest->withdraw(amount);
}

void MainWindow::transferSignalHandler()
{
    if(debitNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Debit not available"));
        messageBox.exec();
        return;
    }
    ptrTransferReceiver->open();
}

void MainWindow::receiverNumberSignalHandler(const QString s)
{
    transferReceiver = s;
    ptrInputAmount->open();
}

void MainWindow::transferAmountHAndler(const QString s)
{
    QString transferAmount = s;
    ptrInputAmount->close();
    ptrRest->transfer(transferReceiver,transferAmount);
}

void MainWindow::transferSuccessHandler()
{
}

void MainWindow::transactionSignalHandler()
{
    ptrRest->getTransactions();
}

void MainWindow::transactionDataReceiver(QByteArray receivedArray)
{
    ptrTransactions->open();
    ptrTransactions->setTransactionData(receivedArray);
}

void MainWindow::creditWithdrawSignalHandler()
{
    if(creditNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Credit not available"));
        messageBox.exec();
        return;
    }
    ptrCreditWithdraw->open();
}

void MainWindow::creditWithdrawRequestHandler(const QString r)
{
    QString amount = r;
    ptrRest->creditWithdraw(amount);
}

void MainWindow::creditWithdrawSuccesHandler()
{
    ptrCreditWithdraw->close();
}

void MainWindow::creditPaymentSuccessHandler()
{
    ptrCreditPayment->close();
}

void MainWindow::creditPaymentSignalHandler()
{
    if(creditNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Credit not available"));
        messageBox.exec();
        return;
    }
    ptrRest->getCreditBalance();
    ptrRest->getCreditLimit();
    ptrCreditPayment->open();
}

void MainWindow::creditPaymentRequestHandler(const QString v)
{
    QString amount = v;
    ptrRest->creditPayment(amount);
}


void MainWindow::changeLanguage(int index)
{
    QApplication::removeTranslator(&translator);
    QString locale = (index == 1) ? "fi_FI" : "en_US";

    if (translator.load(":/translations/Kaannos_" + locale + ".qm")) {
        QApplication::installTranslator(&translator);
    }

    ui->retranslateUi(this);
}

void MainWindow::clienInfoReadyHandler(const QString fname, const QString lname)
{
    ptrUserWindow->setClientName(fname, lname);
}

void MainWindow::balanceSignalHandler()
{
    if(debitNumber == "0"){
        QMessageBox messageBox;
        messageBox.setText(tr("Debit not available"));
        messageBox.exec();
        return;
    }
    ptrRest->getBalance();
}

void MainWindow::balanceReadyHandler(const QString balance)
{
    ptrBalance->setBalance(balance);
    ptrBalance->open();

}

void MainWindow::creditBalanceSignalHandler()
{
    ptrRest->getCreditBalance();
}

void MainWindow::creditBalanceReadyHandler(const QString creditBalance)
{
    ptrCreditPayment->setCreditBalance(creditBalance);
}

void MainWindow::creditLimitSignalHandler()
{
    ptrRest->getCreditLimit();
}

void MainWindow::creditLimitReadyHandler(const QString creditLimit)
{
    ptrCreditPayment->setCreditLimit(creditLimit);
}

void MainWindow::debitNumberHandler(QString debit)
{
    debitNumber = debit;
}

void MainWindow::creditNumberHandler(QString credit)
{
    creditNumber = credit;
}
