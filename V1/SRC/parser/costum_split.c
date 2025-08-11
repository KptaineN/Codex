

#include "../../include/minishell.h"

/* =============================
 * Compte le nombre d'arguments
 * ============================= */
static int count_arg(const char *str, t_shell *shell)
{
    int   count = 0;
    bool  in_single_quote = false;
    bool  in_double_quote = false;
    bool  in_word = false;
    int   idx_oper;
    int   i = 0;

    while (str[i])
    {
        idx_oper = is_in_t_arr_dic_str(shell->oper, (char *)&str[i]);

        if (str[i] == '\'' && !in_double_quote && escape_check(str, i))
            in_single_quote = !in_single_quote;
        else if (str[i] == '"' && !in_single_quote && escape_check(str, i))
            in_double_quote = !in_double_quote;
        else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
        {
            if (in_word)
            {
                in_word = false;
                count++;
            }
        }
        else if (idx_oper != -1 && !in_single_quote && !in_double_quote)
        {
            if (in_word)
            {
                count++;
                in_word = false;
            }
            count++;
            i += ft_strlen((char *)((t_dic *)shell->oper->arr[idx_oper])->key) - 1;
        }
        else if (!in_word)
        {
            in_word = true;
        }
        i++;
    }
    if (in_word)
        count++;
    return count;
}

/* =============================
 * Extrait un argument (token)
 * ============================= */
static char *extract_arg(const char *str, int *start, t_shell *shell)
{
    bool  in_single_quote = false;
    bool  in_double_quote = false;
    int   token_start = *start;
    int   token_end;
    int   idx_oper_one;
    int   oper_ad = 0;
    char  *token;

    // Skip espaces
    while (str[token_start] && str[token_start] == ' ')
        token_start++;
    if (!str[token_start])
        return NULL;

    token_end = token_start;
    while (str[token_end])
    {
        if (str[token_end] == '\'' && !in_double_quote && escape_check(str, token_end))
            in_single_quote = !in_single_quote;
        else if (str[token_end] == '"' && !in_single_quote && escape_check(str, token_end))
            in_double_quote = !in_double_quote;
        else if (!in_single_quote && !in_double_quote)
        {
            if (str[token_end] == ' ')
                break;
            idx_oper_one = is_in_t_arr_dic_str(shell->oper, &str[token_end]);
            if (idx_oper_one != -1)
            {
                oper_ad = ft_strlen((const char *)((t_dic *)shell->oper->arr[idx_oper_one])->key);
                break;
            }
            if (str[token_end + 1] && is_in_t_arr_dic_str(shell->oper, &str[token_end + 1]) != -1)
            {
                oper_ad = 1;
                break;
            }
        }
        token_end++;
    }
    token_end += oper_ad;
    *start = token_end;

    token = malloc((token_end - token_start) + 1);
    if (!token)
        return NULL;
    strncpy(token, str + token_start, token_end - token_start);
    token[token_end - token_start] = '\0';
    return token;
}

/* =============================
 * Découpe la chaîne en tokens
 * ============================= */
t_arr *custom_split(const char *str, t_shell *shell)
{
    t_arr   *result;
    int     pos = 0;
    int     token_index = 0;

    if (!str)
        return NULL;

    result = malloc(sizeof(t_arr));
    if (!result)
        return NULL;

    result->len = count_arg(str, shell);
    if (result->len <= 0)
    {
        free(result);
        return NULL;
    }

    result->arr = malloc(sizeof(char *) * (result->len + 1));
    if (!result->arr)
        return (free(result), NULL);

    while (token_index < result->len)
    {
        result->arr[token_index] = extract_arg(str, &pos, shell);
        if (!result->arr[token_index])
        {
            for (int i = 0; i < token_index; i++)
                free(result->arr[i]);
            free(result->arr);
            free(result);
            return NULL;
        }
        token_index++;
    }
    result->arr[result->len] = NULL;
    return result;
}
