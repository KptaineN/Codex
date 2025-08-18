


#include "../libft.h"

char *ft_strndup(const char *src, size_t n)
{
    char *dup = malloc(n + 1);
    if (!dup)
        return NULL;
    ft_memcpy(dup, src, n);
    dup[n] = '\0';
    return dup;
}
