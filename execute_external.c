#include "minishell.h"

void execute_external_cmd(char *input_string)
{
    char *cmd_with_options[20];
    char command[50];
    
    int i = 0;
    int j = 0;
    int count = 0;
    int pipe_count = 0;

    while (input_string[i] != '\0')
    {
        if (input_string[i] == ' ')
        {
            if (j != 0)
            {
                command[j] = '\0';

                cmd_with_options[count] =
                    malloc(strlen(command) + 1);

                strcpy(cmd_with_options[count], command);

                count++;
                j = 0;
            }
        }

        else if (input_string[i] == '|')
{
    if (j != 0)
    {
        command[j] = '\0';

        cmd_with_options[count] =
            malloc(strlen(command) + 1);

        strcpy(cmd_with_options[count], command);

        count++;
        j = 0;
    }

    cmd_with_options[count] = malloc(2);
    strcpy(cmd_with_options[count], "|");
    count++;

    pipe_count++;
}
        else if (input_string[i] != '\n')
        {
            command[j] = input_string[i];
            j++;
        }

        i++;
    }

    if (j != 0)
    {
        command[j] = '\0';

        cmd_with_options[count] =
            malloc(strlen(command) + 1);

        strcpy(cmd_with_options[count], command);

        count++;
    }

    cmd_with_options[count] = NULL;

    if (pipe_count > 0)
    {
        n_pipes(cmd_with_options, pipe_count);
    }
    else
    {
        execvp(cmd_with_options[0], cmd_with_options);
    }
}