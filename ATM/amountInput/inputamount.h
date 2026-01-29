#ifndef INPUTAMOUNT_H
#define INPUTAMOUNT_H

#include <QDialog>

#include "amountInput_global.h"

namespace Ui {
class inputAmount;
}

class AMOUNTINPUT_EXPORT inputAmount : public QDialog
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *close) override;
    void changeEvent(QEvent *change) override;

public:
    explicit inputAmount(QWidget *parent = nullptr);
    ~inputAmount();

private:
    Ui::inputAmount *ui;
    QString amount;

private slots:
    void numberButtonsHandler();
    void enterButtonHandler();
    void clearButtonHandler();

signals:
    void sendAmount(QString);
};

#endif // INPUTAMOUNT_H
