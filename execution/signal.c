/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:39 by szubair           #+#    #+#             */
/*   Updated: 2023/04/27 17:44:13 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	heredoc_ctrl_c(t_shell *shell, char *line)
{
	if (g_dupstdin == -1)
	{
		shell->last_exit_code = 1;
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		ft_lstclear(&shell->heredoc_contents, free);
		rl_on_new_line();
		ft_free2(&line);
		ft_close(&g_dupstdin);
		return (false);
	}
	return (true);
}

void	handle_ctrl_c(t_shell *shell)
{
	if (g_dupstdin == -1)
	{
		g_dupstdin = dup(0);
		shell->last_exit_code = 1;
	}
}

void	handle_ctrl_d(const char *line, t_shell *shell)
{
	if (line == NULL)
	{
		int x;
		ft_free_array(shell->env);
		shell->env=NULL;
		ft_free_array(shell->declared_env);
		shell->declared_env=NULL;
		ft_free_array(shell->args);
		ft_lstclear(&shell->tokens, free_token);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_close(&g_dupstdin);
		ft_free2(&shell->fd);
		free_steps(&shell->steps_to_free);
		clear_history();
		get_next_line(-1);
		x = shell->last_exit_code;
		printf("Is it here I exit (8)\n");
		ft_free(shell->line);
		free(shell);
		exit(x);
	}
}
