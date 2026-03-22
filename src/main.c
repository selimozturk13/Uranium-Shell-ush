#include "ush.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

void signal_handler(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    //  rl_replace_line("",0);
    rl_redisplay();
}

int main()
{
    signal(SIGINT, signal_handler);
    cli_loop();

    return pexit;
}
