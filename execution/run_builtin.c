/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:20 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:00:41 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*run_parent_builtin(t_exec *step, t_shell *shell, int *fd)
{
	int	x;

	run_builtin(step, shell, FALSE);
	if (ft_strcmp(step->cmd->arg_arr[0], "exit") == 0)
	{
		x = 0;
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
		x = shell->last_exit_code;
		printf("Is it here I exit (10)\n");
		ft_free(shell->line);
		free(shell);
		exit(x);
	}
	return (fd);
}

int	run_child_builtin(t_shell *shell, t_exec *step, int *fds,
	int *heredoc_fds)
{
	int	exit_code;

	run_builtin(step, shell, TRUE);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&g_dupstdin);
	exit_code = step->exit_code;
	printf("Is it here I exit (3)\n");
	ft_lstclear(&shell->tokens, free_token);
	ft_lstclear(&shell->heredoc_contents, free);
	ft_free_array(shell->env);
	shell->env = NULL;
	ft_free_array(shell->declared_env);
	ft_free_array(shell->args);
	shell->declared_env = NULL;
	free_steps(&shell->steps_to_free);
	ft_free(shell->line);
	ft_free2(&fds);
	free(shell);
	return (exit_code);
}

int	run_child_builtin2(t_shell *shell, t_exec *step, int *fds, int *heredoc_fds)
{
	int	exit_code;

	run_builtin(step, shell, TRUE);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&g_dupstdin);
	exit_code = step->exit_code;
	printf("Is it here I exit (4)\n");
	ft_lstclear(&shell->tokens, free_token);
	free_steps(&shell->steps_to_free);
	ft_free_array(shell->env);
	shell->env = NULL;
	ft_free_array(shell->declared_env);
	shell->declared_env = NULL;
	ft_free_array(shell->args);
	ft_lstclear(&shell->heredoc_contents, free);
	shell->step = NULL;
	ft_free(shell->line);
	ft_free2(&fds);
	free(shell);
	return (exit_code);
}
