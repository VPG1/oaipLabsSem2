#include "my_func.h"

void *my_memcpy(void *dest, const void *src, size_t count)
{
    assert(dest && src);

    char *p = (char *)dest;
    char *q = (char *)src;


    while (count--)
    {
        *(p++) = *(q++);
    }

    return dest;
}

void *my_memmove(void *dest, const void *src, size_t count)
{
    assert(dest && src);



    if(dest < src){ // пишем слева направо
        char *p = (char *)dest;
        char *q = (char *)src;
        while(count--){
            *(p++) = *(q++);
        }
    }
    else{ // пишем справа налево
        char *p = (char *)dest + count;
        char *q = (char *)src + count;
        while(count--){
            *(--p) = *(--q);
        }

    }

    return dest;
}

char *my_strcpy(char *dest, const char *src){
    if(!dest)
        return nullptr;

    char *ptr = dest;

    while((*dest++ = *src++) != '\0');

    return ptr;
}

char *my_strncpy(char *dest, const char *src, size_t count)
{
    if(!dest)
        return nullptr;

    char *ptr = dest;

    while(*src && count != 0){
//        std::cout << count << " ";
        *dest = *src;
        ++dest;
        ++src;
        --count;
    }


    return ptr;
}

char *my_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while(*dest){
        ++dest;
    }

    while(*src){
        *dest++ = *src++;
    }

    *dest = '\0';

    return ptr;
}

char *my_strncat(char *dest, const char *src, size_t count)
{
    char *ptr = dest;
    while(*dest){
        ++dest;
    }

    while(*src && count--){
        *dest++ = *src++;
    }

    *dest = '\0';

    return ptr;
}

int my_memcpm(const void *lhs, const void *rhs, size_t count)
{
    unsigned char *s1 = (unsigned char*)lhs;
    unsigned char *s2 = (unsigned char*)rhs;

    while(count-- > 0){
        if(*s1++ != *s2++){
            return s1[-1] < s2[-1] ? -1 : 1;
        }
    }

    return 0;
}

int my_strcmp(const char *lhs, const char *rhs)
{
    while(*lhs && (*lhs == *rhs)){
        ++lhs;
        ++rhs;
    }
    return *(const unsigned char *)lhs - *(const unsigned char *)rhs;
}

int my_strncmp(const char *lhs, const char *rhs, size_t count)
{
    unsigned char u1, u2;
    while(count--){
        u1 = (unsigned char) *lhs++;
        u2 = (unsigned char) *rhs++;
        if(u1 != u2)
            return u1 - u2;
        if(u1 == '\0')
            return 0;
    }

    return 0;
}

int my_strcoll(const char *lhs, const char *rhs)
{
    return my_strcmp(lhs, rhs);
}

char *my_strtok(char *str, char *delim)
{
    static char *input;

    if(!str)
        str = input;

    if(!str)
        return nullptr;

    while(true){
        if(is_delim(*str, delim)){
            ++str;
            continue;
        }
        if(*str == '\0'){
            return nullptr;
        }
        break;
    }

    char * ret = str;
    while(true){
        if(*str == '\0'){
            input = str;
            return ret;
        }
        if(is_delim(*str, delim)){
            *str = '\0';
            input = str + 1;
            return ret;
        }
        ++str;
    }
}

bool is_delim(char c, char *delim){
    while(*delim != '\0')
        if(c == *(delim++))
            return true;


    return false;
}

void *my_memset(void *memptr, int val, size_t num)
{

    unsigned char *ptr = (unsigned char*)memptr;
    while(num--){
        *ptr++ = (unsigned char)val;
    }

    return memptr;
}

size_t my_strlen(const char *str)
{
    size_t res = 0;
    while(*(str++))
        ++res;
    return res;
}
