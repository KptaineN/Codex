




#include "../libft.h"

size_t ft_strcspn(const char *s, const char *reject)
{
    size_t count;
    const char *p;
    const char *r;

    count = 0;
    p = s;
    while (*p != '\0')
    {
        r = reject;
        while (*r != '\0')
        {
            if (*p == *r)
            {
                return count;
            }
            r++;
        }
        count++;
        p++;
    }
    return count;
}
