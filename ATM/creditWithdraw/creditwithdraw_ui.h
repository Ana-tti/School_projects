#ifndef CREDITWITHDRAW_UI_H
#define CREDITWITHDRAW_UI_H

#include <QDialog>
#include "creditWithdraw_global.h"
#include "inputamount.h"
#include <QObject>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class creditWithdraw_UI;
}

class CREDITWITHDRAW_EXPORT creditWithdraw_UI : public QDialog
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *change) override;

public:
    explicit creditWithdraw_UI(QWidget *parent = nullptr);
    ~creditWithdraw_UI();

signals:
    void creditWithdrawReq(QString);

private:
    Ui::creditWithdraw_UI *ui;   
    QString amount;

    inputAmount *ptrInput;

private slots:
    void inputSignalHandler(QString);
    void handlebtn20Click();
    void handlebtn40Click();
    void handlebtn60Click();
    void handlebtn100Click();
    void handlebtnOtherClick();
};

#endif // CREDITWITHDRAW_UI_H
