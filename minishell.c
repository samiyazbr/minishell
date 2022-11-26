/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:50:02 by szubair           #+#    #+#             */
/*   Updated: 2022/11/26 12:42:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc minishell.c -lreadline

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
#include <unistd.h>	/* needed to define getpid() */

int main(int ac, char** av)
{
  char* buf;
  (void)ac;
  (void)av;

//  while (1)
//  {
//	buf = readline("minishell> ");
//	if (!buf)
//		exit(EXIT_FAILURE);
//    if (strlen(buf) > 0)
//      add_history(buf);

//    printf("[%s]\n", buf);
//  }
	char *args[] = {"ls","-la", "/", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	//printf("About to run /bin/ls\n");
	execve("/bin/ls", args, env);
	perror("execve");	/* if we get here, execve failed */
	exit(1);

  return 0;
}
