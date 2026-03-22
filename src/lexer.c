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
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *process_escape(const char *src, int len) {
    if (len < 0) len = 0;
    char *dest = malloc(len + 1);
    int i = 0, j = 0; 

    while (i < len) {
        if (src[i] == '\\' && i + 1 < len) {
            if (src[i + 1] == 'n') {
                dest[j++] = '\n';
                i += 2; 
            } else if (src[i + 1] == 't') {
                dest[j++] = '\t';
                i += 2;
            } else {
                dest[j++] = src[i++];
            }
        } else {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
    return dest;
}

Token *tokenize(char *line) {
    Token *tokenized_line = malloc(sizeof(Token) * MAX_ARGS);
    char *ptr = line;
    char *start = ptr;
    int in_quote = 0, in_apos = 0, lenght = 0, token_count = 0;

    while (*ptr && isspace(*ptr)) ptr++;
    start = ptr;

    while (*ptr) {
        // Save the word that came BEFORE the symbol
        if (!in_quote && !in_apos && (*ptr == '|' || *ptr == '<' || *ptr == '>')) {
            if (lenght > 0) {
                tokenized_line[token_count].type = TOKEN_WORD;
                tokenized_line[token_count++].value = process_escape(start, lenght);
                lenght = 0;
            }

            // Save the symbol ()
            tokenized_line[token_count].type = (*ptr == '|') ? TOKEN_PIPE : TOKEN_REDIR;

            if (tokenized_line[token_count].type == TOKEN_REDIR) {
                fprintf(stderr, "There is not redirect support in this version (%s). \nIt'll come soon.\n", PROGRAM_VERSION);
                return NULL;
            }
            tokenized_line[token_count++].value = strndup(ptr, 1);
            ptr++;
            start = ptr;
            continue;
        }

        if (!in_quote && !in_apos && isspace(*ptr)) {
            if (lenght > 0) {
                tokenized_line[token_count].type = TOKEN_WORD;
                tokenized_line[token_count++].value = process_escape(start, lenght);
                lenght = 0;
            }
            ptr++;
            while (*ptr && isspace(*ptr)) ptr++;
            start = ptr;
            continue;
        }

        if (*ptr == '\"' && !in_apos) {
            if (in_quote) {
                tokenized_line[token_count].type = TOKEN_WORD;
                tokenized_line[token_count++].value = process_escape(start, lenght);
                in_quote = 0; lenght = 0; ptr++; start = ptr;
                continue;
            } else {
                in_quote = 1; start = ++ptr; lenght = 0;
            }
            continue;
        }

        if (*ptr == '\'' && !in_quote) {
            if (in_apos) {
                /* Tek tırnak içindeysek: Kelimeyi bitir ve kaydet */
                tokenized_line[token_count].type = TOKEN_WORD;
                tokenized_line[token_count++].value = process_escape(start, lenght);
                in_apos = 0; lenght = 0; ptr++; start = ptr;
                continue;
            } else {
                /* Tek tırnak dışındaysak: İçeri gir */
                in_apos = 1; ptr++; start = ptr; lenght = 0;
            }
            continue;
        }

        if (lenght == 0 && !in_quote && !in_apos) start = ptr;
        lenght++;
        ptr++;
    }

    if (lenght > 0) {
        tokenized_line[token_count].type = TOKEN_WORD;
        tokenized_line[token_count++].value = process_escape(start, lenght);
    }

    tokenized_line[token_count].value = NULL;
    return tokenized_line;
}
void free_tokens(Token *tokens)
{
    if (tokens == NULL)
    {
        return;
    }

    for (int i = 0; tokens[i].value != NULL; i++)
    {
        free(tokens[i].value);
    }

    free(tokens);
}