#include "../../include/minishell.h"

/*
 * Execute a pipeline of commands stored in shell->cmd_head.
 * For each command we fork, redirect using dup2 and close
 * unused descriptors in both parent and child processes.
 */
void    execute_pipeline(t_shell *shell)
{
    t_list  *curr;
    int     prev_fd;
    int     pipe_fd[2];
    int     i;

    curr = shell->cmd_head;
    prev_fd = -1;
    i = 0;
    while (curr)
    {
        if (curr->next != NULL)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                return ;
            }
        }
        shell->pids[i] = fork();
        if (shell->pids[i] < 0)
        {
            perror("fork");
            return ;
        }
        if (shell->pids[i] == 0)
        {
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    perror("dup2");
                close(prev_fd);
            }
            if (curr->next != NULL)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                    perror("dup2");
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            execute_cmd(shell, (t_token *)curr->content);
            exit(EXIT_FAILURE);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (curr->next != NULL)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        else
            prev_fd = -1;
        curr = curr->next;
        i++;
    }
    // Parent waits for children and updates exit_status
    int status;
    while (--i >= 0)
    {
        waitpid(shell->pids[i], &status, 0);
        if (i == 0)
        {
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->exit_status = 128 + WTERMSIG(status);
        }
    }
}

