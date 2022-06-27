#ifndef MY_FUNC_GLOBAL_H
#define MY_FUNC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MY_FUNC_LIBRARY)
#  define MY_FUNC_EXPORT Q_DECL_EXPORT
#else
#  define MY_FUNC_EXPORT Q_DECL_IMPORT
#endif

#endif // MY_FUNC_GLOBAL_H
