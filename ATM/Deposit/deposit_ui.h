#ifndef DEPOSIT_UI_H
#define DEPOSIT_UI_H

#include "Deposit_global.h"
#include "inputamount.h"
#include <QDialog>
#include <QObject>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class d;
}

class DEPOSIT_EXPORT deposit_ui : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit deposit_ui(QWidget *parent = nullptr);
    ~deposit_ui();

signals:
    void depositReq(QString);

private slots:
    void inputSignalHandler(QString);
    void handlebtn20Click();
    void handlebtn40Click();
    void handlebtn60Click();
    void handlebtn100Click();
    void handlebtnOtherClick();

private:
    Ui::d *ui;
    QString amount;

    inputAmount *ptrInput;
};

#endif // DEPOSIT_UI_H
