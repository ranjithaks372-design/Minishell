#include "minishell.h"

void copy_change(char *prompt, char *input_string)
{
    int i = 0;

    while (input_string[i] != '\0')
    {
        if (input_string[i] == '\n')
        {
            input_string[i] = '\0';
            break; 
        }
        i++;
    }
}