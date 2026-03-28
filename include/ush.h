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
extern int pexit;

void cli_loop(void);
Token *tokenize(char *line);
void free_tokens(Token *tokens);
ASTNode *parse_pipeline(Token *tokens, int *pos);
void free_ast(ASTNode *node);
void executeAst(ASTNode *node);
void update_prompt();
char *absPathToMoreReadable(char *abspath);