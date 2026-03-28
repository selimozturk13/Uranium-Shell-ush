/*
 * Copyright (C) 2026 Selim Öztürk
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "ush.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void update_prompt()
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