/*
 * Copyright (C) 2025 Selim Öztürk
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
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void cli_loop(void)
{
  char *input;
  char userpromt[1024 + PATH_MAX];
  snprintf(userpromt, sizeof(userpromt), "%s@%s %s $", username, host, cwd);

  while (1)
  {
    input = readline(userpromt);
    if (input == NULL)
    {
      printf("\nExiting...\n");
      break;
    }

    if (input != 0)
    {
      add_history(input);
    }

    free(input);
  }
}
