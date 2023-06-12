/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_redic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 17:31:07 by szubair           #+#    #+#             */
/*   Updated: 2023/06/02 17:41:26 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_input_redir_access(t_redir *redir_file)
{
	if (access(redir_file->file, R_OK) == -1)
		return (1);
	return (0);
}

static int	check_output_redir_access(t_redir *redir_file)
{
	if ((access(redir_file->file, F_OK) != -1
			&& access(redir_file->file, W_OK) == -1)
		|| is_dir(redir_file->file))
		return (1);
	return (0);
}

static int	check_redir_syntax(t_redir *redir_file)
{
	if (ft_strchr(redir_file->file, '>') || ft_strchr(redir_file->file, '<'))
	{
		printf("parse error\n");
		return (1);
	}
	return (0);
}

int	check_access_for_redir(t_redir *redir_file, t_list **redir)
{
	if (redir_file->type == INPUT_REDIR)
	{
		return (check_input_redir_access(redir_file));
	}
	else if (redir_file->type == OUTPUT_REDIR || redir_file->type == APPEND)
	{
		if (check_redir_syntax(redir_file))
			return (1);
		return (check_output_redir_access(redir_file));
	}
	if (redir_file->type == INPUT_REDIR || redir_file->type == HEREDOC)
	{
		*redir = (*redir)->next;
		return (2);
	}
	return (0);
}
