#include "minishell.h"

void scan_input(char *prompt, char *input_string)
{
    while (1)
    {
        printf("%s", prompt);

        memset(input_string, '\0', 100);

        if (fgets(input_string, 100, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        copy_change(prompt, input_string);

        if (input_string[0] == '\0')
            continue;

        if (strncmp(input_string, "PS1=", 4) == 0)
        {
            snprintf(prompt, 30, "%s", input_string + 4);
        }
        else
        {
            char *command;
            int type;

            command = get_command(input_string);

            if (command == NULL)
            {
                printf("Memory allocation failed\n");
                continue;
            }

            type = check_command_type(command);

            if (type == BUILTIN)
            {
                execute_internal_commands(input_string);
            }
            else if (type == EXTERNAL)
            {
              //  printf("After wait, head = %p\n", (void *)head);
                pid = fork();

                if (pid == -1)
                {
                    printf("Fork failed\n");
                }
                else if (pid == 0)
                {
                    signal(SIGINT, SIG_DFL);
                    signal(SIGTSTP, SIG_DFL);
                    signal(SIGCHLD, SIG_DFL);

                    execute_external_cmd(input_string);

                    exit(0);
                }
                else
                {
                    int status;

                    pid_t foreground_pid = pid;
                    if (waitpid(foreground_pid, &status, WUNTRACED) > 0)
                    {
                        if (WIFEXITED(status)) last_status = WEXITSTATUS(status);
                        else if (WIFSIGNALED(status)) last_status = 128 + WTERMSIG(status);
                        //printf("After wait, head = %p\n", (void *)head);
                        if (WIFSTOPPED(status))
                        {
                            printf("\n[%d] stopped\n", pid);

                            insert_job(input_string, foreground_pid);
                        }
                    }
                    pid = 0;
                }
            }
            else
            {
                printf("Command not found\n");
                last_status = 127;
            }

            free(command);
        }
    }
}