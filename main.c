#include "minishell.h"
char *external_commands[200];
pid_t pid;
int last_status = 0;
struct node *head = NULL;
int main()
{
    char input_string[100];
    char prompt[30] = "minishell$";

    
    system("clear");
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
/* Child status is collected by waitpid in foreground/jobs code. */
    extract_external_commands(external_commands);

    scan_input(prompt, input_string);

    return 0;
}