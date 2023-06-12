/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:28:44 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 17:29:30 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redir(void *redir_ptr)
{
	t_redir	*redir;

	redir = redir_ptr;
	ft_free(redir->file);
	free(redir);
}

void	free_exec_step(void *exec_step_ptr)
{
	t_exec	*exec_step;
	size_t	i;

	exec_step = exec_step_ptr;
	if (exec_step->cmd)
	{
		ft_lstclear(&exec_step->cmd->redirs, free_redir);
		ft_lstclear(&exec_step->cmd->args, free);
		i = 0;
		if (exec_step->cmd->arg_arr)
		{
			while (exec_step->cmd->arg_arr[i] != NULL)
			{
				ft_free2(&exec_step->cmd->arg_arr[i]);
				i++;
			}
			free(exec_step->cmd->arg_arr);
		}
		free(exec_step->cmd);
	}
	ft_free2(&exec_step->subexpr_line);
	free(exec_step);
}

void	free_steps(t_list **step_list)
{
	t_list	*curr;
	t_list	*next;

	curr = *step_list;
	while (curr)
	{
		next = curr->next;
		free_exec_step(curr->content);
		free(curr);
		curr = next;
	}
	*step_list = NULL;
}

void	*free_parseerror(t_token *token, int num)
{
	if (num == 1)
	{
		free(token);
		return (NULL);
	}
	else
	{
		free(token);
		return (throw_error("Parse Error: Unterminated string\n"));
	}
}
