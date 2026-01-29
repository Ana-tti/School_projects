#ifndef WITHDRAW_GLOBAL_H
#define WITHDRAW_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QDialog>
#include <QObject>

#if defined(WITHDRAW_LIBRARY)
#define WITHDRAW_EXPORT Q_DECL_EXPORT
#else
#define WITHDRAW_EXPORT Q_DECL_IMPORT
#endif

#endif // WITHDRAW_GLOBAL_H
