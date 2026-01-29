#ifndef USERWINDOW_DLL_H
#define USERWINDOW_DLL_H

#include <QDialog>
#include "userWindow_global.h"

namespace Ui {
class userWindow_dll;
}

class USERWINDOW_EXPORT userWindow_dll : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit userWindow_dll(QWidget *parent = nullptr);
    ~userWindow_dll();
    void setWebToken(const QByteArray);
    void setClientName(const QString, const QString);

signals:
    void depositClickSignal();
    void withdrawClickSignal();
    void balanceClickSignal();
    void transactionClickSignal();
    void transferClickSignal();
    void logoutClickSignal();
    void creditWithdrawClickSignal();
    void creditPaymentClickSignal();


private slots:
   void balanceButtonHandler();
   void logoutButtonHandler();
   void depositButtonHandler();
   void withdrawButtonHandler();
   void transactionButtonHandler();
   void transferButtonHandler();
   void creditWithdrawButtonHandler();
   void creditPaymentButtonHandler();


private:
    Ui::userWindow_dll *ui;
    QByteArray webToken;

};

#endif // USERWINDOW_DLL_H
