/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:50 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:18:56 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env(t_shell *shell, t_exec *step)
{
	size_t	i;

	i = 0;
	if (step->cmd->arg_arr[1] != NULL)
	{
		step->exit_code = 1;
		shell->last_exit_code = step->exit_code;
		return ;
	}
	while (shell->env[i] != NULL)
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
