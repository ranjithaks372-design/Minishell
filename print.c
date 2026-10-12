#include "minishell.h"

void print_jobs(void)
{
    struct node *temp = head;
    struct node *prev = NULL;
    struct node *jobs[200];
    int count = 0;

    /* Remove jobs that have finished; do not block while listing jobs. */
    while (temp != NULL)
    {
        int status;
        pid_t result = waitpid(temp->child_pid, &status, WNOHANG);

        if (result == temp->child_pid)
        {
            struct node *finished = temp;
            if (prev == NULL) head = temp->link;
            else prev->link = temp->link;
            temp = temp->link;
            free(finished);
            continue;
        }

        if (count < 200) jobs[count++] = temp;
        prev = temp;
        temp = temp->link;
    }

    /* The list stores newest first; display oldest first like Bash. */
    while (count > 0)
    {
        temp = jobs[--count];
        printf("[%d]   Stopped                 %s\n",
               temp->child_pid, temp->process_name);
    }
}
