#ifndef XVLOG_GLOBAL_H
#define XVLOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(XVLOG_LIBRARY)
#  define XVLOGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define XVLOGSHARED_EXPORT Q_DECL_IMPORT
#endif

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    #pragma execution_character_set("utf-8")
#endif

#endif // XVLOG_GLOBAL_H
