#include "ush.h"
#include <pwd.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  // get username
  struct passwd *pw = getpwuid(geteuid());
  if (pw == NULL)
  {
    fprintf(stderr, "csfsh: cannot find user name for UID. %d\n", getuid());
    strcpy(username, "unknown-user");
  }
  else
  {
    username = strdup(pw->pw_name);
  }

  // get host name
  if (gethostname(host, sizeof(host)) != 0)
  {
    fprintf(stderr, "csfsh: cannot find host name.\n");
    strcpy(host, "unknown-host");
  }

  // get Current Working Directory
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    fprintf(stderr, "csfsh: cannot get current working directory. \n");
    char *pwd = getenv("PWD");
    if (pwd)
    {
      strncpy(cwd, pwd, sizeof(cwd) - 1);
    }
    else
    {
      strcpy(cwd, "?");
    }
  }

  cli_loop();

  return 0;
}
