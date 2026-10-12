#include"minishell.h"
char *get_command(char *input_string)
{
    char *command;
    int i = 0;

    command = malloc(strlen(input_string) + 1);
    if (command == NULL)
        return NULL;

    while (input_string[i] != ' ' &&
           input_string[i] != '\0' &&
           input_string[i] != '\n')
    {
        command[i] = input_string[i];
        i++;
    }

    command[i] = '\0';

    return command;
}