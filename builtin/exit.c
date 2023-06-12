/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:57:33 by szubair           #+#    #+#             */
/*   Updated: 2023/05/15 12:18:57 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_exitcode(t_shell *shell, t_exec *step,
	const int exitcode)
{
	step->exit_code = exitcode;
	shell->last_exit_code = step->exit_code;
}

void	check_valid_args(t_shell *shell, t_exec *step, int i, int *j)
{
	if ((step->cmd->arg_arr[1] && step->cmd->arg_arr[1][i])
		|| (step->cmd->arg_arr[1] && step->cmd->arg_arr[1][0] == '\0'))
	{
		printf("minishell: exit: %s: numeric argument required\n",
			step->cmd->arg_arr[1]);
		set_exitcode(shell, step, 255);
		*j = 1;
	}
	else if (step->cmd->arg_arr[1] && step->cmd->arg_arr[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		set_exitcode(shell, step, 1);
		*j = 1;
	}
}

void	ft_exit(t_exec *step, t_shell *shell, int child)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	j = 0;
	check = 1;
	if (step->cmd->arg_arr[1] && (step->cmd->arg_arr[1][i] == '-'
		|| step->cmd->arg_arr[1][i] == '+'))
		i++;
	while (step->cmd->arg_arr[1] && step->cmd->arg_arr[1][i] >= '0'
			&& step->cmd->arg_arr[1][i] <= '9')
		i++;
	check_valid_args(shell, step, i, &j);
	if (!j && step->cmd->arg_arr[1] != NULL)
		set_exitcode(shell, step, ft_atox(step->cmd->arg_arr[1], &check));
	if (check == 0)
	{
		set_exitcode(shell, step, 255);
		printf("minishell: exit: %s: numeric argument required\n",
			step->cmd->arg_arr[1]);
	}
	if (!child)
		printf("exit\n");
}
