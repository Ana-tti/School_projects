#ifndef REST_H
#define REST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QMessageBox>
#include "environment.h"

class rest : public QObject
{
    Q_OBJECT
public:
    rest();
    ~rest();

    void login(const QString, const QString);
    void getCardInfo(const QString);
    void getAccountInfo(const QString);
    void getClientInfo(const QString);
    void deposit(const QString);
    void withdraw(const QString);
    void transfer(const QString, const QString);
    void getTransactions();
    void getBalance();
    void getCreditBalance();
    void getCreditLimit();
    void creditWithdraw(const QString);
    void creditPayment(const QString);
    void defineDebit(const QString);
    void defineCredit(const QString);

signals:
   void loginSuccess();
   void loginFailed();
   void withdrawSuccess();
   void depositSuccess();
   void creditWithdrawSuccess();
   void creditPaymentSuccess();
   void sendTransactionData(QByteArray);
   void transferSuccess();
   void clientInfoReady(QString, QString);
   void balanceReady(QString);
   void creditBalanceReady(QString);
   void creditLimitReady(QString);
   void sendDebitNumber(QString);
   void sendCreditNumber(QString);

private slots:
    void loginSlot();
    void balanceSlot(QNetworkReply *reply);
    void creditBalanceSlot(QNetworkReply *reply);
    void creditLimitSlot(QNetworkReply *reply);
    void cardInfoSlot(QNetworkReply *reply);
    void accountInfoSlot(QNetworkReply *reply);
    void clientInfoSlot(QNetworkReply *reply);
    void depositSlot(QNetworkReply *reply);
    void withdrawSlot(QNetworkReply *reply);
    void transactionSlot(QNetworkReply *reply);
    void transferSlot(QNetworkReply *reply);
    void creditWithdrawSLot(QNetworkReply *reply);
    void creditPaymentSlot(QNetworkReply *reply);
    void defineDebitSlot(QNetworkReply *reply);
    void defineCreditSlot(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QNetworkReply * reply;

    QByteArray webToken;
    QString accountId;
    QString clientId;
    QString fname;
    QString lname;
    QString balance;
    QString creditBalance;
    QString creditLimit;
    QString debitAccount;
    QString creditAccount;

};

#endif // REST_H
