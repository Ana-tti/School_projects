#ifndef PIN_UI_H
#define PIN_UI_H

#include <QDialog>
#include "PIN_global.h"

namespace Ui {
class PIN_UI;
}
class PIN_EXPORT PIN_UI : public QDialog
{
    Q_OBJECT

public:
    explicit PIN_UI(QWidget *parent = nullptr);
    ~PIN_UI();

    void numberButtons();
    void clearButton();


protected:
    void changeEvent(QEvent *change) override;
    void showEvent(QShowEvent *timer) override;
    void closeEvent(QCloseEvent *close) override;

signals:
    void sendPinToExe(const QString &pin);

private slots:
    void sendPin();
    void timeout();
    void startTimer();
    void resetPinUI();

private:
    Ui::PIN_UI *ui;
    QTimer *pQTimer;
    QTimer *progressTimer;
    int elapsedSeconds;
    short setPinTime;
};

#endif // PIN_UI_H
