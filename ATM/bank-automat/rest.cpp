#include "rest.h"

rest::rest() {}

rest::~rest()
{
    delete manager;
}

void rest::login(const QString cardnum, const QString pin)
{
    QJsonObject jsonObject;
    jsonObject.insert("cardnumber",cardnum);
    jsonObject.insert("pin",pin);
    QString site_url = "http://localhost:3000/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager;
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
    connect(reply,&QNetworkReply::finished,this,&rest::loginSlot);
}

void rest::getBalance()
{
    QString site_url = environment::base_url()+"/account/balance/"+debitAccount;
    QNetworkRequest request(site_url);
    request.setRawHeader("Authorization", webToken);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&rest::balanceSlot);
    reply = manager->get(request);
}

void rest::getCreditBalance()
{
    QString site_url = environment::base_url()+"/account/creditbalance/"+creditAccount;
    QNetworkRequest request(site_url);
    request.setRawHeader("Authorization", webToken);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&rest::creditBalanceSlot);
    reply = manager->get(request);
}

void rest::getCreditLimit()
{
    QString site_url = environment::base_url()+"/account/creditlimit/"+creditAccount;
    QNetworkRequest request(site_url);
    request.setRawHeader("Authorization", webToken);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&rest::creditLimitSlot);
    reply = manager->get(request);
}

void rest::creditWithdraw(const QString amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("account_id",creditAccount);
    jsonObject.insert("amount",amount);
    QString site_url=environment::base_url()+"/transactions/creditWithdraw";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::creditWithdrawSLot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::creditPayment(const QString amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("account_id",creditAccount);
    jsonObject.insert("amount",amount);
    QString site_url=environment::base_url()+"/transactions/creditPayment";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::creditPaymentSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::defineDebit(const QString cardnumber)
{
    QJsonObject jsonObject;
    jsonObject.insert("card_number",cardnumber);
    QString site_url=environment::base_url()+"/account/defineDebit";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::defineDebitSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::defineCredit(const QString cardnumber)
{
    QJsonObject jsonObject;
    jsonObject.insert("card_number",cardnumber);
    QString site_url=environment::base_url()+"/account/defineCredit";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::defineCreditSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::getCardInfo(const QString cardnum)
{
    QString site_url=environment::base_url()+"/card/"+cardnum;
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::cardInfoSlot);
    reply = manager->get(request);
}

void rest::getAccountInfo(const QString accountid)
{
    QString site_url=environment::base_url()+"/account/"+accountid;
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::accountInfoSlot);
    reply = manager->get(request);
}

void rest::getClientInfo(const QString clientId)
{

    QString site_url=environment::base_url()+"/client/"+clientId;
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::clientInfoSlot);
    reply = manager->get(request);
}

void rest::deposit(const QString amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("account_id",debitAccount);
    jsonObject.insert("amount",amount);
    QString site_url=environment::base_url()+"/transactions/deposit";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::depositSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::withdraw(const QString amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("account_id",debitAccount);
    jsonObject.insert("amount",amount);
    QString site_url=environment::base_url()+"/transactions/withdraw";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::withdrawSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::transfer(const QString receiverNumber, const QString amount)
{
    QJsonObject jsonObject;
    jsonObject.insert("first_id",debitAccount);
    jsonObject.insert("second_id",receiverNumber);
    jsonObject.insert("amount",amount);
    QString site_url=environment::base_url()+"/transactions/transfer";
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::transferSlot);
    reply = manager->post(request,QJsonDocument(jsonObject).toJson());
}

void rest::getTransactions()
{
    QString site_url=environment::base_url()+"/transactions/"+accountId;
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished, this,&rest::transactionSlot);
    reply = manager->get(request);
}

void rest::loginSlot()
{
    QByteArray response_data = reply->readAll();
    reply->deleteLater();
    reply = nullptr;

    if (response_data.length() < 2 || response_data == "db_error")
    {
    }
    else if (response_data == "false")
    {
        QMessageBox messageBox;
        messageBox.setText(tr("Incorrect pin"));
        messageBox.exec();
        emit loginFailed();
    }

    else if(response_data == "Card is locked")
    {
        QMessageBox messageBox;
        messageBox.setText(tr("Login not allowed. Contact support"));
        messageBox.exec();
    }

    else
    {
        webToken = "Bearer " + response_data;
        emit loginSuccess();
    }
}

void rest::balanceSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    balance = (jsonObj["balance"].toString());
    emit balanceReady(balance);
}

void rest::creditBalanceSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    if (response_data == "\"Account not found\""){
        return;
    }

    creditBalance = jsonObj["creditbalance"].toString();
    emit creditBalanceReady(creditBalance);

}

void rest::creditLimitSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();

    creditLimit = jsonObj["creditlimit"].toString();
    emit creditLimitReady(creditLimit);

}

void rest::cardInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    accountId = QString::number(jsonObj["idaccount"].toInt());
    clientId = QString::number(jsonObj["idclient"].toInt());
    getClientInfo(clientId);
}

void rest::accountInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();

}

void rest::clientInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    fname = jsonObj["fname"].toString();
    lname = jsonObj["lname"].toString();
    emit clientInfoReady(fname, lname);
}

void rest::depositSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QMessageBox messageBox;
    if(response_data == "0"){

        messageBox.setText(tr("Deposit failed"));
        messageBox.exec();
    }
    else{
        messageBox.setText(tr("Deposit successful"));
        messageBox.exec();
        emit depositSuccess();
    }
}

void rest::withdrawSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QMessageBox messageBox;

    if(response_data == "0"){

        messageBox.setText(tr("Insufficient funds"));
        messageBox.exec();
    }
    else{
        messageBox.setText(tr("Withdraw successful"));
        messageBox.exec();
        emit withdrawSuccess();
    }
}

void rest::transactionSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    emit sendTransactionData(response_data);
}

void rest::transferSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QMessageBox messageBox;
    if(response_data == "0"){

        messageBox.setText(tr("Insufficient funds or wrong receiver account"));
        messageBox.exec();
    }
    else{
        messageBox.setText(tr("Transfer successful"));
        messageBox.exec();
        emit transferSuccess();
    }
}

void rest::creditWithdrawSLot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QMessageBox messageBox;
    if(response_data == "0"){

        messageBox.setText(tr("Credit limit reached"));
        messageBox.exec();
    }
    else{
        messageBox.setText(tr("Credit withdraw successful"));
        messageBox.exec();
        emit creditWithdrawSuccess();
    }
}

void rest::creditPaymentSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QMessageBox messageBox;
    if(response_data == "0"){

        messageBox.setText(tr("Insufficient funds"));
        messageBox.exec();
    }
    else{
        messageBox.setText(tr("Credit payment successful"));
        messageBox.exec();
        emit creditPaymentSuccess();
    }
}

void rest::defineDebitSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObj = jsonArray.first().toObject();
    debitAccount = QString::number(jsonObj["idaccount"].toInt());
    emit sendDebitNumber(debitAccount);
}

void rest::defineCreditSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonArray jsonArray = jsonDoc.array();
    QJsonObject jsonObj = jsonArray.first().toObject();
    creditAccount = QString::number(jsonObj["idaccount"].toInt());
    emit sendCreditNumber(creditAccount);
    getCreditBalance();
    getCreditLimit();
}
