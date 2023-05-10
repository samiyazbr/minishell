/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:45 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:17:05 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_check(char *s1)
{
	int	i;

	i = 0;
	if (!s1)
		return (false);
	if (s1[0] != '-')
		return (false);
	i = 1;
	if (s1[i] == '\0')
		return (false);
	while (s1[i])
	{
		if (s1[i] == 'n')
			i++;
		else
			return (false);
	}
	return (true);
}

void	write_echo_content(t_exec *step, int i)
{
	ft_putstr_fd(step->cmd->arg_arr[i], 1);
	if (step->cmd->arg_arr[i + 1])
		ft_putstr_fd(" ", 1);
}

void	ft_echo(t_exec *step, t_shell *shell)
{
	int	i;
	int	n;
	int	seen;

	i = 1;
	n = 0;
	seen = 0;
	if (ft_check(step->cmd->arg_arr[1]) == true)
		n = 1;
	while (step->cmd->arg_arr[i])
	{
		if (seen)
			write_echo_content(step, i);
		if (ft_check(step->cmd->arg_arr[i]) != true && !seen)
		{
			seen = 1;
			write_echo_content(step, i);
		}
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
