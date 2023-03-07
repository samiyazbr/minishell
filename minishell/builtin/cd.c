/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:01:18 by szubair           #+#    #+#             */
/*   Updated: 2023/03/07 13:19:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int cd_error(char *arg)
{
	write(2, "bash: cd: ",10);
	perror(arg);
	return (1);
}

void set_pwd(t_shell_s *minishell)
{
	char	*cwd;
	char	*toadd;

	cwd = getcwd(NULL, 4096);
	toadd = ft_strjoin("PWD=", cwd);
	free(cwd);
	ft_putenv(toadd, minishell);
	free(toadd);
}

int cd (char **args, int args_count, t_shell_s *minishell)
{
	char	*home;

	if (args_count == 0)
	{
		home = ft_getenv(minishell, "HOME");
		if (!home || !(*home))
		{
			write(1, "bash: cd: HOME not set\n", 2);
			return (1);
		}
		if(chdir(home) == -1)
			return (cd_error(home));
	}
	else if (args_count == 1)
	{
		if (chdir(args[0]) == -1)
			return (cd_error(args[0]));
	}
	else
	{
		write(1, "cd: too many arguments\n", 2);
		return (1);
	}
	set_pwd(minishell);
	return (0);
}