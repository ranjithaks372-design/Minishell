#include "minishell.h"

void delete_job(int child_pid)
{
    struct node *temp = head;
    struct node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->child_pid == child_pid)
        {
            if (prev == NULL)
                head = temp->link;
            else
                prev->link = temp->link;

            free(temp);
            return;
        }

        prev = temp;
        temp = temp->link;
    }
}