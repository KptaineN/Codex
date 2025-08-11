

#include "echo.h"


static int handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
{
    char *val;
    int  nb = 0;

    val = get_dollar_value(arg, i, sh);
    if (val)
    {
        ft_strcpy(res, val);
        nb = ft_strlen(val);
        free(val);
    }
    return nb;
}

static void toggle_quotes(char c, bool *in_sq, bool *in_dq)
{
    if (c == '\'' && !(*in_dq))
        *in_sq = !(*in_sq);
    else if (c == '"' && !(*in_sq))
        *in_dq = !(*in_dq);
}

static int process_dollar(char *dst, const char *arg, int *i, t_shell *sh)
{
    int written = handle_dollar(dst, arg, i, sh);
    if (written > 0)
        return written;
    dst[0] = arg[(*i)++];
    return 1;
}

char *replace_variables(const char *arg, t_shell *sh)
{
    int  i = 0, j = 0;
    bool in_sq = false, in_dq = false;
    char *res = malloc(ft_strlen(arg) * 50 + 1);
    if (!res) return NULL;

    while (arg[i])
    {
        toggle_quotes(arg[i], &in_sq, &in_dq);

        if (arg[i] == '$' && !in_sq)
            j += process_dollar(&res[j], arg, &i, sh);
        else
            res[j++] = arg[i++];
    }

    res[j] = '\0';
    return res;
}
