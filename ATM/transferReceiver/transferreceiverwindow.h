#ifndef TRANSFERRECEIVERWINDOW_H
#define TRANSFERRECEIVERWINDOW_H

#include "transferReceiver_global.h"
#include <QDialog>

namespace Ui {
class transferReceiverWindow;
}

class TRANSFERRECEIVER_EXPORT transferReceiverWindow : public QDialog
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *close) override;
    void changeEvent(QEvent *change) override;

public:
    explicit transferReceiverWindow(QWidget *parent = nullptr);
    ~transferReceiverWindow();

signals:
    void sendAccountNumber(QString);

private:
    Ui::transferReceiverWindow *ui;
    void numButtonHandler();
    void eraseButtonHandler();
    void enterButtonHanlder();
};

#endif // TRANSFERRECEIVERWINDOW_H
