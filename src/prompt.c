/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:09:56 by szubair           #+#    #+#             */
/*   Updated: 2023/05/08 16:21:20 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*print_prompt(t_shell *shell)
{
	char	*prompt;

	g_dupstdin = dup(0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
	prompt = readline("minishell😃$ ");
	shell->line = prompt;
	signal(SIGQUIT, sigquit);
	handle_ctrl_d(prompt, shell);
	return (prompt);
}

int	add_to_history(char *line)
{
	if (line[0] != '\0')
	{
		add_history(line);
		return (TRUE);
	}
	else
	{
		ft_close(&g_dupstdin);
		ft_free(line);
		return (FALSE);
	}
}
