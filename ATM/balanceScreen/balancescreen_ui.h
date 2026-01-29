#ifndef BALANCESCREEN_UI_H
#define BALANCESCREEN_UI_H

#include <QDialog>
#include "balanceScreen_global.h"

namespace Ui {
class balanceScreen_UI;
}

class BALANCESCREEN_EXPORT balanceScreen_UI : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit balanceScreen_UI(QWidget *parent = nullptr);
    ~balanceScreen_UI();
    void setBalance(const QString);

private:
    Ui::balanceScreen_UI *ui;
};

#endif // BALANCESCREEN_UI_H
