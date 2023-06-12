/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:39 by szubair           #+#    #+#             */
/*   Updated: 2023/06/02 16:24:46 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_ctrl_d(const char *line, t_shell *shell)
{
	int	x;

	x = 0;
	if (line == NULL)
	{
		ft_free_array(shell->env);
		shell->env = NULL;
		ft_free_array(shell->declared_env);
		shell->declared_env = NULL;
		ft_free_array(shell->args);
		ft_lstclear(&shell->tokens, free_token);
		ft_lstclear(&shell->heredoc_contents, free);
		ft_close(&g_dupstdin);
		ft_free2(&shell->fd);
		free_steps(&shell->steps_to_free);
		clear_history();
		get_next_line(-1);
		x = shell->last_exit_code;
		ft_free(shell->line);
		free(shell);
		exit(x);
	}
}
