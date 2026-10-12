#include "minishell.h"

void insert_job(char *process_name, int child_pid)
{
    struct node *new = malloc(sizeof(struct node));

    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    snprintf(new->process_name, sizeof(new->process_name), "%s", process_name);
    new->child_pid = child_pid;
    new->link = head;
    head = new;
}
