/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:51:24 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 16:01:05 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_dupstdin;

void	minishell_exec(t_shell *shell, char *line)
{
	if (shell->step != NULL)
		exec_cmds(shell, shell->step, 0, shell->line);
	ft_lstclear(&shell->tokens, free_token);
	ft_lstclear(&shell->heredoc_contents, free);
	free_steps(&shell->steps_to_free);
	shell->steps_to_free = NULL;
	rl_on_new_line();
	ft_free(line);
	ft_close(&g_dupstdin);
}

int	validate_quotes(char *l)
{
	size_t	i;
	char	is_quote;

	i = 0;
	while (l[i] != '\0')
	{
		if (l[i] == '\'' || l[i] == '\"')
		{
			is_quote = l[i];
			i++;
			while (l[i] != is_quote && l[i])
				i++;
			if (l[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

bool	quotes(char *cmd_line)
{
	if (validate_quotes(cmd_line))
	{
		printf("Parse Error: Unterminated string\n");
		free(cmd_line);
		return (true);
	}
	return (false);
}

void	heredoc(t_shell *cmd, char *cmd_line)
{
	ft_lstadd_back(&cmd->steps_to_free, cmd->step);
	run_heredocs(cmd);
	minishell_exec(cmd, cmd_line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	int		error;
	t_shell	*cmd;

	(void) argc;
	(void) argv;
	cmd = init_shell(envp, &error);
	while (1)
	{
		cmd_line = print_prompt(cmd);
		if (add_to_history(cmd_line) == FALSE)
			continue ;
		error = 1;
		if (quotes(cmd_line) == true)
			continue ;
		cmd->tokens = tokenize_the_input(cmd, cmd_line, &error);
		if (ft_is_token_error(cmd, cmd_line, &error))
			continue ;
		cmd->step = ft_get_steps(cmd->tokens, &error);
		if (handle_get_steps_error(cmd, &error, cmd_line))
			continue ;
		heredoc(cmd, cmd_line);
	}
	return (0);
}
