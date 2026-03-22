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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void executeAst(ASTNode *node)
{
    if (!node)
        return;

    if (node->type == NODE_COMMAND)
    {
        if (!(node->data.cmd.args != NULL && node->data.cmd.args[0] != NULL)) return;

        if (!strcmp(node->data.cmd.args[0], "cd"))
        {
            if (node->data.cmd.args[1] != NULL)
            {
                if (chdir(node->data.cmd.args[1]))
                    perror("ush: chdir");
            }
            else
            {
                if (chdir(getenv("HOME")))
                {
                    perror("ush: chdir");
                }
            }
            return;
        }

        else if (!strcmp(node->data.cmd.args[0], "exit"))
        {
            if (node->data.cmd.args[1] != NULL)
            {
                if (atoi(node->data.cmd.args[1]) > 255)
                {
                    pexit = atoi(node->data.cmd.args[1]) % 256;
                }
                else
                {
                    pexit = atoi(node->data.cmd.args[1]);
                }
            }
            else
            {
                pexit = 0;
            }
            return;
        }

        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // Child Process
                if (execvp(node->data.cmd.args[0], node->data.cmd.args) == -1)
                {
                    perror("ush");
                }
                exit(EXIT_FAILURE);
            }
            else if (pid < 0)
            {
                perror("ush: fork");
            }
            else
            {
                waitpid(pid, NULL, 0);
            }
        }
    }

    else if (node->type == NODE_PIPE)
    {
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            perror("ush: pipe");
            return;
        }
        pid_t left_pid = fork();
        if (left_pid == 0)
        {
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            executeAst(node->data.pipe.left);
            exit(EXIT_SUCCESS);
        }
        pid_t right_pid = fork();
        if (right_pid == 0)
        {
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            executeAst(node->data.pipe.right);
            exit(EXIT_SUCCESS);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(left_pid, NULL, 0);
        waitpid(right_pid, NULL, 0);
    }
}