#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <stdlib.h>
#include <string.h>

bool escape_check(const char *str, int idx)
{
    bool toggle = true;
    while (idx > 0 && str[--idx] == '\\')
        toggle = !toggle;
    return toggle;
}

int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    if (!arr || !arr->arr || !arg)
        return -1;
    for (int i = 0; i < arr->len; i++)
    {
        t_dic *dic = (t_dic *)arr->arr[i];
        if (dic && dic->key)
        {
            size_t len_key = ft_strlen(dic->key);
            if (ft_strncmp(dic->key, arg, len_key) == 0)
                return i;
        }
    }
    return -1;
}

static t_shell init_shell(void)
{
    static t_dic in = {"<", NULL};
    static t_dic out = {">", NULL};
    static void *op_arr[] = {&in, &out};
    static t_arr oper = {op_arr, 2};
    t_shell shell = {0};
    shell.oper = &oper;
    return shell;
}

static void free_tokens_arr(t_arr *tokens)
{
    if (!tokens)
        return;
    for (int i = 0; i < tokens->len; i++)
        free(tokens->arr[i]);
    free(tokens->arr);
    free(tokens);
}

Test(custom_split, redir_double_quotes_without_space)
{
    t_shell shell = init_shell();
    t_arr *tokens = custom_split("<\"file\"", &shell);
    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->len, 2);
    cr_assert_str_eq(tokens->arr[0], "<");
    cr_assert_str_eq(tokens->arr[1], "\"file\"");
    free_tokens_arr(tokens);
}

Test(custom_split, redir_single_quotes_without_space)
{
    t_shell shell = init_shell();
    t_arr *tokens = custom_split(">'file'", &shell);
    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->len, 2);
    cr_assert_str_eq(tokens->arr[0], ">");
    cr_assert_str_eq(tokens->arr[1], "'file'");
    free_tokens_arr(tokens);
}

Test(custom_split, redir_plain_without_space)
{
    t_shell shell = init_shell();
    t_arr *tokens = custom_split(">outfile", &shell);
    cr_assert_not_null(tokens);
    cr_assert_eq(tokens->len, 2);
    cr_assert_str_eq(tokens->arr[0], ">");
    cr_assert_str_eq(tokens->arr[1], "outfile");
    free_tokens_arr(tokens);
}
