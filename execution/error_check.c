/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:36 by szubair           #+#    #+#             */
/*   Updated: 2023/06/02 16:26:32 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	cmd_not_found_check(t_exec *step, bool valid_redirs)
{
	bool	check;

	check = (access(step->cmd->arg_arr[0], F_OK) == -1 && !is_builtin(step));
	if ((check || is_dir(step->cmd->arg_arr[0])) && valid_redirs
		&& !ft_strchr(step->cmd->arg_arr[0], '/'))
		return (true);
	if (access(step->cmd->arg_arr[0], F_OK) != -1
		&& access(step->cmd->arg_arr[0], X_OK) == -1
		&& !ft_strchr(step->cmd->arg_arr[0], '/') && valid_redirs)
		return (true);
	return (false);
}

bool	file_not_found_check(t_exec *step, bool valid_redirs)
{
	return ((access(step->cmd->arg_arr[0], F_OK) == -1 && !is_builtin(step))
		&& valid_redirs && ft_strchr(step->cmd->arg_arr[0], '/'));
}

bool	permission_denied_check(t_exec *step, bool valid_redirs)
{
	return ((access(step->cmd->arg_arr[0], X_OK) == -1
			&& !is_builtin(step)) && valid_redirs);
}
