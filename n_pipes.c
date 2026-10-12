#include "minishell.h"

void n_pipes(char **cmd_with_options, int pipe_count)
{
    int fd[2];
    int i = 0;
    int input_fd = 0;
    int status;
    pid_t pid;

    while (cmd_with_options[i] != NULL)
    {
        if (strcmp(cmd_with_options[i], "|") == 0)
        {
            i++;
            continue;
        }

        char *args[20];
        int j = 0;

        while (cmd_with_options[i] != NULL &&
               strcmp(cmd_with_options[i], "|") != 0)
        {
            args[j] = cmd_with_options[i];
            j++;
            i++;
        }

        args[j] = NULL;

        if (cmd_with_options[i] != NULL)
        {
            pipe(fd);

            pid = fork();

            if (pid == 0)
            {
                if (input_fd != 0)
                {
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                }

                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);

                execvp(args[0], args);
                exit(1);
            }

            close(fd[1]);

            if (input_fd != 0)
                close(input_fd);

            input_fd = fd[0];
        }
        else
        {
            pid = fork();

            if (pid == 0)
            {
                if (input_fd != 0)
                {
                    dup2(input_fd, STDIN_FILENO);
                    close(input_fd);
                }

                execvp(args[0], args);
                exit(1);
            }

            if (input_fd != 0)
                close(input_fd);

            waitpid(pid, &status, 0);
        }
    }
}