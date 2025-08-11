
#include "libft.h"

char *ft_strcpy(char *dest, const char *src)
{
    char *ret;

    if (!dest || !src)
        return NULL;

    ret = dest;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return ret;
}