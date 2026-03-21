#include "ush.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Token *tokenize(char *line)
{
  Token *tokenized_line = malloc(sizeof(Token) * MAX_ARGS);
  char *ptr = line;
  char *start = ptr;
  int in_quote = 0;
  int lenght = 0;
  int token_count = 0;

  while (*ptr && isspace(*ptr))
    ptr++;

  start=ptr;

  while (*ptr)
  {

    // Save the word that came BEFORE the symbol
    if (!in_quote && (*ptr == '|' || *ptr == '<' || *ptr == '>'))
    {
      if (lenght > 0)
      {
        tokenized_line[token_count].type = TOKEN_WORD;
        tokenized_line[token_count++].value = strndup(start, lenght);
        lenght = 0;
      }

      // Save the symbol ()
      tokenized_line[token_count].type =
          (*ptr == '|') ? TOKEN_PIPE : TOKEN_REDIR;
      
      if (tokenized_line[token_count].type==TOKEN_REDIR)
      {
        fprintf(stderr,"There is not redirect support in this version (%s). \nIt'll come soon.\n",PROGRAM_VERSION);
        return NULL;
      }
      tokenized_line[token_count++].value = strndup(ptr, 1);
      ptr++;
      start = ptr;
      continue;
    }

    if (!in_quote && isspace(*ptr))
    {
      if (lenght > 0)
      {
        tokenized_line[token_count].type = TOKEN_WORD;
        tokenized_line[token_count++].value = strndup(start, lenght);
        lenght = 0;
      }

      ptr++;
      while (*ptr && isspace(*ptr)) ptr++;
      start = ptr;
      continue;
    }

    if (*ptr == '\"')
    {
      if (in_quote)
      {
        tokenized_line[token_count].type = TOKEN_WORD;

        tokenized_line[token_count++].value = strndup(start, lenght);

        in_quote = 0;
        lenght = 0;
        ptr++;
        start = ptr;
        continue;
      }
      else
      {
        in_quote = 1;
        start = ++ptr;
        lenght = 0;
      }
      continue;
    }

    if (lenght == 0 && !in_quote) start = ptr;
    lenght++;
    ptr++;
  }

  if (lenght > 0)
  {
    tokenized_line[token_count].type = TOKEN_WORD;
    tokenized_line[token_count++].value = strndup(start, lenght);
  }

  tokenized_line[token_count].value = NULL;

  return tokenized_line;
}

void free_tokens(Token* tokens)
{
  if (tokens==NULL)
  {
    return;
  }

  for (int i=0;tokens[i].value!=NULL;i++)
  {
    free(tokens[i].value);
  }

  free(tokens);
}