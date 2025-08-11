#include "../../include/minishell.h"

static int  run_builtin_cmd(t_shell *sh, char **argv)
{
    if (ft_strcmp(argv[0], "echo") == 0)
        return (builtin_echo(sh, argv));
    if (ft_strcmp(argv[0], "cd") == 0)
        return (builtin_cd(sh, argv));
    if (ft_strcmp(argv[0], "pwd") == 0)
        return (builtin_pwd(sh, argv));
    if (ft_strcmp(argv[0], "export") == 0)
        return (builtin_export(sh, argv));
    if (ft_strcmp(argv[0], "unset") == 0)
        return (builtin_unset(sh, argv));
    if (ft_strcmp(argv[0], "env") == 0)
        return (builtin_env(sh, argv));
    if (ft_strcmp(argv[0], "exit") == 0)
        return (builtin_exit(sh, argv));
    return (1);
}

static void exec_child(t_shell *sh, t_list *node, int i, int n, int (*p)[2])
{
    t_token *tok;
    char    **argv;
    char    *path;
    char    **envp;
    int     k;

    if (i > 0)
        dup2(p[i - 1][0], STDIN_FILENO);
    if (i < n - 1)
        dup2(p[i][1], STDOUT_FILENO);
    k = 0;
    while (k < n - 1)
    {
        close(p[k][0]);
        close(p[k][1]);
        k++;
    }
    tok = (t_token *)node->content;
    argv = expand_cmd(tok, sh->env);
    if (!argv || !argv[0])
        _exit(1);
    if (is_builtin(argv[0]))
    {
        k = run_builtin_cmd(sh, argv);
        free_tab(argv);
        _exit(k);
    }
    path = find_command_path(argv[0], sh->env);
    envp = list_to_envp(sh->env);
    execve(path, argv, envp);
    perror("execve");
    free(path);
    free_tab(envp);
    free_tab(argv);
    _exit(127);
}

void    launch_process(t_shell *sh)
{
    int     (*p)[2];
    pid_t   *pids;
    t_list  *node;
    int     i;
    int     status;

    if (sh->n_cmd <= 0)
        return ;
    p = NULL;
    if (sh->n_cmd > 1)
    {
        p = malloc(sizeof(int [2]) * (sh->n_cmd - 1));
        if (!p)
            return ;
    }
    pids = malloc(sizeof(pid_t) * sh->n_cmd);
    if (!pids)
        return ;
    node = sh->cmd_head;
    i = -1;
    while (++i < sh->n_cmd)
    {
        if (i < sh->n_cmd - 1 && pipe(p[i]) < 0)
            return (perror("pipe"));
        pids[i] = fork();
        if (pids[i] < 0)
            return (perror("fork"));
        if (pids[i] == 0)
            exec_child(sh, node, i, sh->n_cmd, p);
        if (i > 0)
            close(p[i - 1][0]);
        if (i < sh->n_cmd - 1)
            close(p[i][1]);
        node = node->next;
    }
    i = 0;
    while (i < sh->n_cmd)
    {
        waitpid(pids[i], &status, 0);
        i++;
    }
    sh->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    free(pids);
    if (p)
        free(p);
}

