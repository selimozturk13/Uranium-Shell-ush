#include "ush.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ASTNode *parse_command(Token *tokens, int *pos)
{
  // malloc the node and data parts
  ASTNode *node = malloc(sizeof(ASTNode));
  if (!node)
    return NULL;
  node->type = NODE_COMMAND;
  node->data.cmd.args = malloc(sizeof(char *) * MAX_ARGS);

  int i = 0;
  while (tokens[*pos].value != NULL && tokens[*pos].type == TOKEN_WORD &&
         i < MAX_ARGS - 1)
  {
    node->data.cmd.args[i++] = strdup(tokens[*pos].value);
    (*pos)++;
  }

  // NULL for exec
  node->data.cmd.args[i] = NULL;
  return node;
}

ASTNode *parse_pipeline(Token *tokens, int *pos)
{
  ASTNode *current_node = parse_command(tokens, pos);

  while (tokens[*pos].value != NULL && tokens[*pos].type == TOKEN_PIPE)
  {
    (*pos)++;

    ASTNode *right = parse_pipeline(tokens, pos);
    if (right == NULL || right->data.cmd.args[0] == NULL)
    {
      fprintf(stderr, "ush: syntax error near unexpected token '|'\n");
      free_ast(current_node);
      return NULL;
    }
    ASTNode *new_pipe = malloc(sizeof(ASTNode));
    if (!new_pipe)
      return current_node;
    new_pipe->type = NODE_PIPE;
    new_pipe->data.pipe.left = current_node;
    new_pipe->data.pipe.right = right;
    current_node = new_pipe;
  }
  return current_node;
}

void free_ast(ASTNode* node)
{
    if (node==NULL) return;

    switch (node->type)
    {
        case NODE_COMMAND:
            if (node->data.cmd.args)
            {
                for(int i=0;node->data.cmd.args[i]!=NULL;i++)
                {
                    free(node->data.cmd.args[i]);
                }
                free(node->data.cmd.args);
            }
            break;
        case NODE_PIPE:
            
            free_ast(node->data.pipe.left);
            free_ast(node->data.pipe.right);
            break;
        case NODE_REDIR:
            fprintf(stderr, "There is not redirect support at this version (%s).\n It'll come soon.\n",PROGRAM_VERSION);       
            break;
    }
    free(node);
}
