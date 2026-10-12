#include"minishell.h"
int check_command_type(char *command)
{
    char *internal_commands[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
						"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
						"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","jobs","fg","bg", NULL};

    int i = 0;

    while (internal_commands[i] != NULL)
    {
        if (strcmp(command, internal_commands[i]) == 0)
        {
            return BUILTIN;
        }

        i++;
    }

    i = 0;

    while (external_commands[i] != NULL)
    {
        if (strcmp(command, external_commands[i]) == 0)
        {
            return EXTERNAL;
        }

        i++;
    }

    return NO_COMMAND;
}