#include "minishell.h"

void signal_handler(int sig_num)
{
    if (sig_num == SIGINT)
    {
        if (pid == 0)
        {
            printf("\nminishell$");
        }
    }

    if (sig_num == SIGTSTP)
    {
        if (pid == 0)
        {
            printf("\nminishell$");
        }
    }
    else if (sig_num == SIGCHLD)
{
    int status;
    pid_t child_pid;

    child_pid = waitpid(-1, &status, WNOHANG);

    if (child_pid > 0)
    {
        if (WIFEXITED(status))
        {
            delete_job(child_pid);
        }
    }
}
}