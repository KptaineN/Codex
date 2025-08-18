
/*
** ft_sort_str_tab : tri à bulle d'un tableau de chaînes (NULL-terminé)
*/
#include "../libft.h"

static size_t get_tab_len(char **tab)
{
    size_t len = 0;
    while (tab[len])
        len++;
    return len;
}

void ft_bubble_str_sort(char **tab)
{
    size_t i = 0, j, len;

    if (!tab)
        return;
    len = get_tab_len(tab);
    while (i < len)
    {
        j = 0;
        while (j + 1 < len - i)
        {
            if (ft_strcmp(tab[j], tab[j + 1]) > 0)
                ft_swap_str(&tab[j], &tab[j + 1]);
            j++;
        }
        i++;
    }
}
