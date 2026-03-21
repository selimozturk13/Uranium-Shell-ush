#pragma once

#define PROGRAM_VERSION "v0.1.0"
#define MAX_ARGS 64

#include <limits.h>

typedef enum
{
  NODE_COMMAND,
  NODE_PIPE,
  NODE_REDIR,
} NodeType;

typedef struct ASTNode
{
  NodeType type;

  union
  {
    struct
    {
      char **args;
    } cmd;

    struct
    {
      struct ASTNode *left;
      struct ASTNode *right;
    } pipe;

    struct
    {
      struct ASTNode *child;
      char *file;
      int fd;
    } redir;
  } data;
} ASTNode;

typedef enum
{
  TOKEN_WORD,
  TOKEN_PIPE,
  TOKEN_REDIR,
} TokenType;
  
typedef struct
{
  TokenType type;
  char *value;
} Token;

extern char cwd[PATH_MAX];
extern char host[256];
extern char *username;

void cli_loop(void);
Token *tokenize(char *line);
void free_tokens(Token* tokens);
ASTNode *parse_pipeline(Token *tokens,int *pos);
void free_ast(ASTNode* node);
void executeAst(ASTNode* node);