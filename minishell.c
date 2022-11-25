/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:50:02 by szubair           #+#    #+#             */
/*   Updated: 2022/11/25 16:17:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc minishell.c -lreadline

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

int main(int ac, char** av)
{
  char* buf;
  (void)ac;
  (void)av;

  while (1)
  {
	buf = readline("minishell> ");
	if (!buf)
		exit(EXIT_FAILURE);
    if (strlen(buf) > 0)
      add_history(buf);

    printf("[%s]\n", buf);
  }

  return 0;
}