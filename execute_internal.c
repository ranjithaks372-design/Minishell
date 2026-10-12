#include "minishell.h"

void execute_internal_commands(char *input_string)
{
    if (strcmp(input_string, "exit") == 0)
    {
        exit(0);
    }

    else if (strcmp(input_string, "pwd") == 0)
    {
        char path[100];

        getcwd(path, 100);

        printf("%s\n", path);
    }

    else if (strncmp(input_string, "cd ", 3) == 0)
    {
        chdir(input_string + 3);
    }

    else if (strncmp(input_string, "echo", 4) == 0)
    {
        echo(input_string, last_status);
    }
    else if (strcmp(input_string, "jobs") == 0)
    {
        print_jobs();
    }
    else if (strcmp(input_string, "fg") == 0)
    {
        if (head != NULL)
        {
            int status;
            pid_t child_pid = head->child_pid;

            printf("%s\n", head->process_name);
            pid = child_pid;
            kill(child_pid, SIGCONT);

            if (waitpid(child_pid, &status, WUNTRACED) > 0)
            {
                if (WIFEXITED(status)) last_status = WEXITSTATUS(status);
                else if (WIFSIGNALED(status)) last_status = 128 + WTERMSIG(status);

                if (WIFEXITED(status) || WIFSIGNALED(status))
                    delete_job(child_pid);
            }
            pid = 0;
        }
    }
    else if (strcmp(input_string, "bg") == 0)
    {
        if (head != NULL)
        {
            if (kill(head->child_pid, SIGCONT) == 0)
                printf("[%d] %s &\n", head->child_pid, head->process_name);
        }
    }
}
