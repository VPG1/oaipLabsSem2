#ifndef MY_FUNC_H
#define MY_FUNC_H

#include "my_func_global.h"


#include <cassert>

MY_FUNC_EXPORT void *my_memcpy(void *dest, const void *src, size_t count);

MY_FUNC_EXPORT void *my_memmove(void *dest, const void *src, size_t count);

MY_FUNC_EXPORT char *my_strcpy(char *dest, const char *src);

MY_FUNC_EXPORT char *my_strncpy(char *dest, const char *src, size_t count);

MY_FUNC_EXPORT char *my_strcat(char *dest, const char *src);

MY_FUNC_EXPORT char *my_strncat(char *dest, const char *src, size_t count);

MY_FUNC_EXPORT int my_memcpm(const void *lhs, const void *rhs, size_t count);

MY_FUNC_EXPORT int my_strcmp(const char *lhs, const char *rhs);

MY_FUNC_EXPORT int my_strcoll(const char *lhs, const char *rhs);

MY_FUNC_EXPORT int my_strncmp(const char *lhs, const char *rhs, size_t count);

MY_FUNC_EXPORT bool is_delim(char c, char *delim);

MY_FUNC_EXPORT char *my_strtok(char *str, char *delim);

MY_FUNC_EXPORT size_t my_strlen(const char *str);

MY_FUNC_EXPORT void *my_memset(void *memptr, int val, size_t num);



#endif // MY_FUNC_H
