#ifndef TRANSACTIONS_UI_H
#define TRANSACTIONS_UI_H

#include <QDialog>
#include "transactionsWindow_global.h"
#include <QObject>
#include <QStandardItemModel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTableView>
#include <QString>
#include <QJsonArray>
#include <QComboBox>
#include <QDateTime>

namespace Ui {
class Transactions_UI;
}

class TRANSACTIONSWINDOW_EXPORT Transactions_UI : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit Transactions_UI(QWidget *parent = nullptr);
    ~Transactions_UI();
    void setTransactionData(QByteArray);

private slots:
    void updateTransactions();

private:
    Ui::Transactions_UI *ui;
    QString occurDate;
    QString amount;
    QString transactionType;
    QByteArray transactionData;

    void transactionTable(const QJsonArray& data);
    QJsonArray sortTransactions(QJsonArray data, const QString&);
    QJsonArray filterTransactionsByType(QJsonArray data, const QString& type);

};

#endif // TRANSACTIONS_UI_H
