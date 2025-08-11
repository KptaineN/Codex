#include "../../include/minishell.h"

/* ----- utils: strip quotes & expansion flag for heredoc delimiter ----- */
t_delim parse_delim(const char *raw)
{
    t_delim d;
    size_t i;
    size_t j;

    d.raw = (char *)raw;
    d.quoted = 0;
    if (!raw)
    {
        d.clean = NULL;
        return d;
    }
    d.clean = malloc(ft_strlen(raw) + 1);
    if (!d.clean)
        return d;
    i = 0;
    j = 0;
    while (raw[i])
    {
        if (raw[i] == '\'' || raw[i] == '"')
        {
            d.quoted = 1;
            i++;
            continue;
        }
        d.clean[j++] = raw[i++];
    }
    d.clean[j] = '\0';
    return d;
}

/* ----- expansion simple pour heredoc non quoté ----- */
char *expand_vars_in_line(const char *line, t_shell *sh)
{
    char *tmp;
    char *res;

    if (!line)
        return NULL;
    tmp = replace_exit_code(line, sh->exit_status);
    res = replace_variables(tmp, sh);
    free(tmp);
    return res;
}

/* helpers for filename expansion / ambiguity */
static void ambiguous(const char *original)
{
    ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
    ft_putstr_fd((char *)original, STDERR_FILENO);
    ft_putstr_fd((char *)": ambiguous redirect\n", STDERR_FILENO);
}

static int is_ambiguous(const char *fname)
{
    int i;

    if (!fname || *fname == '\0')
        return 1;
    i = 0;
    while (fname[i])
    {
        if (fname[i] == ' ')
            return 1;
        i++;
    }
    return 0;
}

static char *expand_filename_if_needed(char *arg, t_shell *sh)
{
    char *tmp;
    char *res;

    tmp = replace_exit_code(arg, sh->exit_status);
    res = replace_variables(tmp, sh);
    free(tmp);
    return res;
}

/* ----- création d’un pipe heredoc et remplissage via get_next_line ----- */
int build_heredoc_fd(t_delim d, t_shell *sh)
{
    int     hd[2];
    pid_t   pid;

    if (pipe(hd) < 0)
    {
        perror("pipe");
        return -1;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(hd[0]);
        close(hd[1]);
        return -1;
    }
    if (pid == 0)
    {
        char    *line;
        size_t  n;

        signal(SIGINT, SIG_DFL);
        close(hd[0]);
        while (1)
        {
            line = get_next_line(STDIN_FILENO);
            if (!line)
                break;
            n = ft_strlen(line);
            if (n && line[n - 1] == '\n')
                line[n - 1] = '\0';
            if (ft_strcmp(line, d.clean) == 0)
            {
                free(line);
                break;
            }
            if (!d.quoted)
            {
                char *exp = expand_vars_in_line(line, sh);
                free(line);
                line = exp;
            }
            write(hd[1], line, ft_strlen(line));
            write(hd[1], "\n", 1);
            free(line);
        }
        close(hd[1]);
        _exit(0);
    }
    close(hd[1]);
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        close(hd[0]);
        return -2;
    }
    return hd[0];
}

/* ----- appliquer redirections dans l’enfant du maillon ----- */
int apply_redirs_in_child(t_cmd *c, t_shell *sh)
{
    int i;
    int fd;

    i = 0;
    while (i < c->r_count)
    {
        t_redir *r = &c->r[i];
        if (r->type == R_IN)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_RDONLY);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (r->type == R_OUT_TRUNC)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_OUT_APPEND)
        {
            char *file = expand_filename_if_needed(r->arg, sh);
            if (is_ambiguous(file))
            {
                ambiguous(r->arg);
                free(file);
                return 1;
            }
            fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
            free(file);
            if (fd < 0)
            {
                perror(r->arg);
                return 1;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_HEREDOC)
        {
            t_delim d = parse_delim(r->arg);
            int hfd = build_heredoc_fd(d, sh);
            free(d.clean);
            if (hfd == -2)
                exit(130);
            if (hfd < 0)
                return 1;
            dup2(hfd, STDIN_FILENO);
            close(hfd);
        }
        i++;
    }
    return 0;
}

/* placeholders for external helpers */
static int run_builtin(t_cmd *c, t_shell *sh)
{
    (void)c;
    (void)sh;
    return 0;
}

static char *resolve_path(const char *cmd, t_shell *sh)
{
    (void)sh;
    return (char *)cmd;
}

/* ----- intégration enfant maillon ----- */
void child_exec_maillon(t_cmd *c, t_shell *sh, int i, int ncmd, int p[][2])
{
    if (i > 0)
        dup2(p[i - 1][0], STDIN_FILENO);
    if (i < ncmd - 1)
        dup2(p[i][1], STDOUT_FILENO);
    for (int k = 0; k < ncmd - 1; k++)
    {
        close(p[k][0]);
        close(p[k][1]);
    }
    if (apply_redirs_in_child(c, sh))
        _exit(1);
    if (c->is_builtin)
        _exit(run_builtin(c, sh));
    char **envp = env_to_envp(sh->env);
    execve(resolve_path(c->argv[0], sh), c->argv, envp);
    perror("execve");
    _exit(127);
}

