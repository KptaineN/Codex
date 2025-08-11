



#include <stddef.h>  // pour size_t
#include "libft.h"
/**
 * my_strcspn - retourne la position du premier caractère de s
 *               qui figure dans reject.
 * s:      chaîne à scanner.
 * reject: chaîne contenant les caractères interdits.
 *
 * Parcourt s caractère par caractère. Pour chacun, on vérifie
 * s’il est égal à l’un de ceux de reject. Dès qu’on trouve
 * un « interdit », on renvoie l’indice actuel. Sinon on continue.
 * Si jamais on arrive au '\0' sans rencontrer d'interdit,
 * on renvoie la longueur totale de s.
 */
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
