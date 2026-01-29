#include "transactions_ui.h"
#include "ui_transactions_ui.h"
#include <algorithm>
#include <QVector>

Transactions_UI::Transactions_UI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Transactions_UI)
{
    ui->setupUi(this);

    //Käännös kääreet suodattimille
    ui->typeComboBox->addItem(tr("All types"), "All types");
    ui->typeComboBox->addItem(tr("Deposit"), "deposit");
    ui->typeComboBox->addItem(tr("Withdrawal"), "withdrawal");
    ui->typeComboBox->addItem(tr("Credit withdrawal"), "credit withdrawal");
    ui->typeComboBox->addItem(tr("Credit payment"), "credit payment");
    ui->dateComboBox->addItem(tr("Newest first"), "newest");
    ui->dateComboBox->addItem(tr("Oldest first"), "oldest");

    connect(ui->amountComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&Transactions_UI::updateTransactions);
    connect(ui->dateComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&Transactions_UI::updateTransactions);
    connect(ui->typeComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&Transactions_UI::updateTransactions);
}

Transactions_UI::~Transactions_UI()
{
    delete ui;
}

void Transactions_UI::setTransactionData(QByteArray array)
{
    transactionData = array;
    updateTransactions();
}

void Transactions_UI::updateTransactions()
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(transactionData);
    QJsonArray allTransactions = jsonDoc.array();

    // Suodattaa tyypin mukaan
    QString selectedType = ui->typeComboBox->currentData().toString();
    QJsonArray filteredByType = filterTransactionsByType(allTransactions, selectedType);

    // Järjestää uusin/vanhin ensin
    QString selectedOrder = ui->dateComboBox->currentText();
    QJsonArray sortedTransactions = sortTransactions(filteredByType, selectedOrder);

    // Rajoitaa määrän 10 riviin
    int rowLimit = -1;
    if (ui->amountComboBox->currentText() == tr("Show 10")) {
        rowLimit = 10;
    }

    QJsonArray displayedTransactions;
    if (rowLimit > 0 && sortedTransactions.size() > rowLimit) {
        for (int i = 0; i < rowLimit; ++i) {
            displayedTransactions.append(sortedTransactions[i]);
        }
    } else {
        displayedTransactions = sortedTransactions;
    }

    // Päivittää taulukon
    transactionTable(displayedTransactions);
}

void Transactions_UI::transactionTable(const QJsonArray& data)
{
    //QJsonDocument jsonDoc = QJsonDocument::fromJson(transactionData);
    //QJsonArray jsonArray = jsonDoc.array();
    QStandardItemModel *table_model = new QStandardItemModel(0, 3);
    ui->tableView_transactions->setModel(table_model);
    table_model->setHorizontalHeaderLabels({tr("Transaction Type"), tr("Amount"), tr("Occur Date")});

    // Taulukon sarakkeiden venytys
    ui->tableView_transactions->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView_transactions->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView_transactions->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    int row = 0;
    for (const QJsonValue& value : data) {
        QJsonObject jsonObj = value.toObject();
        QString transactionType = jsonObj["transaction_type"].toString();
        QString amount = jsonObj["amount"].toString();
        QString dateTime = jsonObj["occurdate"].toString();
        QDateTime deleteTime = QDateTime::fromString(dateTime, Qt::ISODate);
        QString occurDate = deleteTime.date().toString("dd/MM/yyyy");

        QStandardItem *typeOf = new QStandardItem(transactionType);
        table_model->setItem(row, 0, typeOf);
        QStandardItem *moneyNumber = new QStandardItem(amount);
        table_model->setItem(row, 1, moneyNumber);
        QStandardItem *date = new QStandardItem(occurDate);
        table_model->setItem(row, 2, date);
        row+=1;
    }
}

QJsonArray Transactions_UI::sortTransactions(QJsonArray data, const QString&)
{
    QVector<QJsonObject> objectList;
    for (const QJsonValue& value : data) {
        objectList.append(value.toObject());
    }

    std::sort(objectList.begin(), objectList.end(), [&](const QJsonObject& a, const QJsonObject& b) {
        QDateTime dateTimeA = QDateTime::fromString(a["occurdate"].toString(), Qt::ISODate);
        QDateTime dateTimeB = QDateTime::fromString(b["occurdate"].toString(), Qt::ISODate);
        QString selectedOrder = ui->dateComboBox->currentData().toString();
        if (selectedOrder == "newest") {
            return dateTimeA > dateTimeB;
        } else { // Oldest first
            return dateTimeA < dateTimeB;
        }
    });

    QJsonArray sortedData;
    for (const QJsonObject& object : objectList) {
        sortedData.append(object);
    }

    return sortedData;
}

QJsonArray Transactions_UI::filterTransactionsByType(QJsonArray data, const QString& type)
{
    if (type == "All types") {
        return data;
    }
    QJsonArray filteredData;
    for (const QJsonValue& value : data) {
        QJsonObject jsonObj = value.toObject();
        if (jsonObj["transaction_type"].toString().compare(type, Qt::CaseInsensitive) == 0) {
            filteredData.append(value);
        }
    }
    return filteredData;
}

void Transactions_UI::changeEvent(QEvent *change)
{
    if (change->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);

        ui->typeComboBox->clear();
        ui->typeComboBox->addItem(tr("All types"), "All types");
        ui->typeComboBox->addItem(tr("Deposit"), "deposit");
        ui->typeComboBox->addItem(tr("Withdrawal"), "withdrawal");
        ui->typeComboBox->addItem(tr("Credit withdrawal"), "credit withdrawal");
        ui->typeComboBox->addItem(tr("Credit payment"), "credit payment");

        ui->dateComboBox->clear();
        ui->dateComboBox->addItem(tr("Newest first"), "newest");
        ui->dateComboBox->addItem(tr("Oldest first"), "oldest");

        updateTransactions();
    }
    QDialog::changeEvent(change);
}
