#include "ush.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void executeAst(ASTNode* node)
{
    if (!node) return;
    
    if (node->type==NODE_COMMAND)
    {
        
            //Child Process
        if (execvp(node->data.cmd.args[0],node->data.cmd.args)==-1)
        {
            perror("ush");
        }
        exit(EXIT_FAILURE);
        
    }

    else if (node->type==NODE_PIPE)
    {
        int pipefd[2];
        if (pipe(pipefd)==-1){
            perror("ush: pipe");
            return;
        }
        pid_t left_pid=fork();
        if (left_pid==0)
        {
            dup2(pipefd[1],STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            executeAst(node->data.pipe.left);
            exit(EXIT_SUCCESS);
        }
        pid_t right_pid=fork();
        if (right_pid==0)
        {
            dup2(pipefd[0],STDIN_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            executeAst(node->data.pipe.right);
            exit(EXIT_SUCCESS);
        }

        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(left_pid,NULL,0);
        waitpid(right_pid,NULL,0);

    }
}