#ifndef QBUILDING_GLOBAL_H
#define QBUILDING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QBUILDING_LIBRARY)
#  define QBUILDINGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QBUILDINGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QBUILDING_GLOBAL_H
