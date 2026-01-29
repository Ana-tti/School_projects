#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QMessageBox>
#include <QComboBox>
#include <QTranslator>
#include "rfid_ui.h"
#include "pin_ui.h"
#include "rest.h"
#include "withdraw_ui.h"
#include "userwindow_dll.h"
#include "deposit_ui.h"
#include "transactions_ui.h"
#include "transferreceiverwindow.h"
#include "balancescreen_ui.h"
#include "creditwithdraw_ui.h"
#include "creditpaymentui.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void rfidSignalHandler(const QString);
    void pinSignalHandler(const QString);
    void loginSuccessHandler();
    void loginFailHandler();
    void withdrawSuccessHandler();
    void depositSuccessHandler();
    void creditWithdrawSuccesHandler();
    void creditPaymentSuccessHandler();

    void depositSignalHandler();
    void depositRequestHandler(const QString);

    void withdrawSignalHandler();
    void withdrawRequestHandler(const QString);

    void transferSignalHandler();
    void receiverNumberSignalHandler(const QString);
    void transferAmountHAndler(const QString);
    void transferSuccessHandler();

    void transactionSignalHandler();
    void transactionDataReceiver(QByteArray);

    void creditWithdrawSignalHandler();
    void creditWithdrawRequestHandler(const QString);

    void creditPaymentSignalHandler();
    void creditPaymentRequestHandler(const QString);

    void changeLanguage(int index);
    void clienInfoReadyHandler(const QString, const QString);

    void balanceSignalHandler();
    void balanceReadyHandler(const QString);

    void creditBalanceSignalHandler();
    void creditBalanceReadyHandler(const QString);

    void creditLimitSignalHandler();
    void creditLimitReadyHandler(const QString);

    void debitNumberHandler(QString);
    void creditNumberHandler(QString);


private:
    Ui::MainWindow *ui;
    QComboBox *languageComboBox;
    rfid_UI *ptrRfid_dll;
    PIN_UI *ptrPin_dll;
    rest *ptrRest;
    userWindow_dll *ptrUserWindow;
    Withdraw_UI *ptrWithdraw;
    creditWithdraw_UI *ptrCreditWithdraw;
    creditPaymentUI *ptrCreditPayment;
    deposit_ui *ptrDeposit;
    Transactions_UI *ptrTransactions;
    transferReceiverWindow *ptrTransferReceiver;
    inputAmount *ptrInputAmount;
    balanceScreen_UI *ptrBalance;

    QString cardNumber;
    QString PinNumber;
    QByteArray webToken;
    QTranslator translator;
    int loginAttempts = 0;
    QString transferReceiver;
    QString debitNumber;
    QString creditNumber;





};
#endif // MAINWINDOW_H
