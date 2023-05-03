/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:51:24 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/03 13:31:11 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_dupstdin;

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
	if (shell->declared_env != NULL)
		ft_free_array(shell->declared_env);
}

int main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	int		error;
	t_shell	*cmd;
	// t_list	*copy;
	
	(void) argc;
	(void) argv;
	cmd = init_shell(envp, &error);
	while (1)
	{
		cmd_line = print_prompt(cmd);
		if(add_to_history(cmd_line) == FALSE)
			continue;
		error = TRUE;
		cmd->tokens = tokenize_the_input(cmd, cmd_line, &error);
		// copy = cmd->tokens;
		// 	while(copy)
		// 	{
		// 		t_token *print = copy->content;
		// 		printf("Token: %s\n", print->substr);
		// 		printf("Token type: %d\n", print->type);
		// 		copy = copy->next;
		// 	}
		if (ft_is_token_error(cmd, cmd_line, &error))
			continue;
		cmd->step = ft_get_steps(cmd->tokens, &error);
		if (handle_get_steps_error(cmd, &error, cmd_line))
			continue;
		ft_lstadd_back(&cmd->steps_to_free, cmd->step);
		run_heredocs(cmd);
		if (heredoc_ctrl_c(cmd, cmd_line) == false)
			continue ;

		minishell_exec(cmd, cmd_line);		
	}
	exit(EXIT_SUCCESS);
	return(0);
}
