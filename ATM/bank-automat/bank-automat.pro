QT       += core gui
QT +=serialport
QT +=network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    environment.cpp \
    main.cpp \
    mainwindow.cpp \
    rest.cpp

HEADERS += \
    environment.h \
    mainwindow.h \
    rest.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
Kaannos_en_US.ts \
Kaannos_fi_FI.ts

RESOURCES += \
resource.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../amountInput/build/debug/ -lamountInput

INCLUDEPATH += $$PWD/../amountInput
DEPENDPATH += $$PWD/../amountInput

win32: LIBS += -L$$PWD/../balanceScreen/build/debug/ -lbalanceScreen

INCLUDEPATH += $$PWD/../balanceScreen
DEPENDPATH += $$PWD/../balanceScreen

win32: LIBS += -L$$PWD/../Deposit/build/debug/ -lDeposit

INCLUDEPATH += $$PWD/../Deposit
DEPENDPATH += $$PWD/../Deposit

win32: LIBS += -L$$PWD/../PIN_DLL/build/debug/ -lPIN

INCLUDEPATH += $$PWD/../PIN_DLL
DEPENDPATH += $$PWD/../PIN_DLL

win32: LIBS += -L$$PWD/../RFID_DLL/build/debug/ -lRFID

INCLUDEPATH += $$PWD/../RFID_DLL
DEPENDPATH += $$PWD/../RFID_DLL

win32: LIBS += -L$$PWD/../transactionsWindow/build/debug/ -ltransactionsWindow

INCLUDEPATH += $$PWD/../transactionsWindow
DEPENDPATH += $$PWD/../transactionsWindow

win32: LIBS += -L$$PWD/../transferReceiver/build/debug/ -ltransferReceiver

INCLUDEPATH += $$PWD/../transferReceiver
DEPENDPATH += $$PWD/../transferReceiver

win32: LIBS += -L$$PWD/../userWindow/build/debug/ -luserWindow

INCLUDEPATH += $$PWD/../userWindow
DEPENDPATH += $$PWD/../userWindow

win32: LIBS += -L$$PWD/../Withdraw/build/debug/ -lWithdraw

INCLUDEPATH += $$PWD/../Withdraw
DEPENDPATH += $$PWD/../Withdraw

win32: LIBS += -L$$PWD/../creditWithdraw/build/debug/ -lcreditWithdraw

INCLUDEPATH += $$PWD/../creditWithdraw
DEPENDPATH += $$PWD/../creditWithdraw

win32: LIBS += -L$$PWD/../creditPayment/build/debug/ -lcreditPayment

INCLUDEPATH += $$PWD/../creditPayment
DEPENDPATH += $$PWD/../creditPayment
