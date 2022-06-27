#ifndef MY_STRING_GLOBAL_H
#define MY_STRING_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MY_STRING_LIBRARY)
#  define MY_STRING_EXPORT Q_DECL_EXPORT
#else
#  define MY_STRING_EXPORT Q_DECL_IMPORT
#endif

#endif // MY_STRING_GLOBAL_H
