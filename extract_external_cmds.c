#include "minishell.h"

void extract_external_commands(char **external_commands)
{
    FILE *fptr;
    char command[100];
    int i = 0;

    fptr = fopen("external_cmds.txt", "r");

    if (fptr == NULL)
    {
        printf("File not found\n");
        return;
    }

    while (i < 199 && fscanf(fptr, "%99s", command) == 1)
    {
        external_commands[i] = malloc(strlen(command) + 1);
        if (external_commands[i] == NULL)
            break;

        strcpy(external_commands[i], command);

        i++;
    }

    external_commands[i] = NULL;

    fclose(fptr);
}