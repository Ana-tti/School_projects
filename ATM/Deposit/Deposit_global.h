#ifndef DEPOSIT_GLOBAL_H
#define DEPOSIT_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QDialog>

#if defined(DEPOSIT_LIBRARY)
#define DEPOSIT_EXPORT Q_DECL_EXPORT
#else
#define DEPOSIT_EXPORT Q_DECL_IMPORT
#endif

#endif // DEPOSIT_GLOBAL_H
