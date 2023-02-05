/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:19:57 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/01 22:05:26 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell_s	*get_path(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "PATH=", 5))
		{
			minishell->path = ft_split(envp[count.i - 1] + 5, ':');
			break ;
		}
	}
	return (minishell);
}

t_shell_s	*get_home(t_shell_s *minishell, char *envp[])
{
	t_counter	count;

	count.i = 0;
	while (envp[count.i] != NULL)
	{
		if (ft_strnstr(envp[count.i++], "HOME=", 5))
		{
			minishell->home = ft_strdup(envp[count.i - 1] + 5);
			break ;
		}
	}
	return (minishell);
}

t_shell_s	*get_commands(t_shell_s *minishell, char *str)
{
	t_counter	count;

	count.i = 0;
	if (!str)
		return (minishell);
	while (str[count.i])
	{
		count.i++;
	}
	return (minishell);
}
