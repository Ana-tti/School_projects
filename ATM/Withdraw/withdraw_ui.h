#ifndef WITHDRAW_UI_H
#define WITHDRAW_UI_H

#include "Withdraw_global.h"
#include "inputamount.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QObject>

namespace Ui {
class Withdraw_UI;
}

class WITHDRAW_EXPORT Withdraw_UI : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit Withdraw_UI(QWidget *parent = nullptr);
    ~Withdraw_UI();


signals:
    void withdrawReq(QString);

private:
    Ui::Withdraw_UI *ui;
    QString amount;
    inputAmount *ptrInput;

private slots:
    void handlebtn20Click();
    void handlebtn40Click();
    void handlebtn60Click();
    void handlebtn100Click();
    void handlebtnOtherClick();
    void inputSignalHandler(QString);
};

#endif // WITHDRAW_UI_H
