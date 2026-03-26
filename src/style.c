#include "ush.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void update_promt()
{
    struct passwd *pw = getpwuid(geteuid());
    if (pw == NULL)
    {
        fprintf(stderr, "ush: cannot find user name for UID. %d\n", getuid());
        username=malloc(sizeof(char)*13);
        strcpy(username, "unknown-user");
    }
    else
    {
        username = strdup(pw->pw_name);
    }

    // get host name
    if (gethostname(host, sizeof(host)) != 0)
    {
        fprintf(stderr, "ush: cannot find host name.\n");
        strcpy(host, "unknown-host");
    }

    // get Current Working Directory
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        fprintf(stderr, "ush: cannot get current working directory. \n");
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
    char *readable = absPathToMoreReadable(cwd);
    if (readable) {
        strncpy(cwd, readable, sizeof(cwd) - 1);
        cwd[sizeof(cwd) - 1] = '\0'; 
        free(readable); 
    }
}

char *absPathToMoreReadable(char *abspath) {
    char *home = getenv("HOME");
    
    if (home == NULL || strncmp(abspath, home, strlen(home)) != 0) {
        return strdup(abspath); 
    }
    char *path = malloc(PATH_MAX);
    if (!path) return NULL;
    char *relative_part = abspath + strlen(home);
    snprintf(path, PATH_MAX, "~%s", relative_part);
    
    return path;
}