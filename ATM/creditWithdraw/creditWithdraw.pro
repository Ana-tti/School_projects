QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += CREDITWITHDRAW_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditwithdraw_ui.cpp

HEADERS += \
    creditWithdraw_global.h \
    creditwithdraw_ui.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    creditwithdraw_ui.ui



win32: LIBS += -L$$PWD/../amountInput/build/Desktop_Qt_6_9_0_MinGW_64_bit-Debug/debug/ -lamountInput

INCLUDEPATH += $$PWD/../amountInput
DEPENDPATH += $$PWD/../amountInput

win32: LIBS += -L$$PWD/../amountInput/build/debug/ -lamountInput

INCLUDEPATH += $$PWD/../amountInput
DEPENDPATH += $$PWD/../amountInput
