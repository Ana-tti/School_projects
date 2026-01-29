#ifndef CREDITPAYMENTUI_H
#define CREDITPAYMENTUI_H

#include <QDialog>
#include "creditPayment_global.h"
#include "inputamount.h"
#include <QObject>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class creditPaymentUI;
}

class CREDITPAYMENT_EXPORT creditPaymentUI : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit creditPaymentUI(QWidget *parent = nullptr);
    ~creditPaymentUI();
    void setCreditBalance(const QString);
    void setCreditLimit(const QString);

private:
    Ui::creditPaymentUI *ui;
    QString amount;
    inputAmount *ptrInput;

signals:
    void creditPaymentReq(QString);

private slots:
    void payAll();
    void chooseAmount();
    void inputSignalHandler(QString);
};

#endif // CREDITPAYMENTUI_H
