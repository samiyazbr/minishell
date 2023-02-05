/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooutabac <ooutabac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:48:06 by ooutabac          #+#    #+#             */
/*   Updated: 2023/02/01 22:16:31 by ooutabac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* LEXER
How it works:

*/
t_shell_s	*lexer(t_shell_s *minishell, char *str)
{
	t_counter	count;

	count.i = 0;
	count.j = 0;
	if (!str)
		return (minishell);
	if (!minishell)
		return (NULL);
	minishell->lexer = ft_calloc(sizeof(t_lexer), 1);
	
	minishell->lexer->num_of_dquotes = number_of_dquotes(str);
	if (minishell->lexer->num_of_dquotes % 2 == 1)
		return (printf("Minishell: Error: lexer--utils3.c: Odd number of quotes\n"), minishell);
	minishell->lexer->tokens = malloc(sizeof(char *) * (minishell->lexer->num_of_dquotes + 1));
	while (str[count.i])
	{
		minishell->lexer->tokens[count.j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (str[count.i] == '\"' && str[++count.i])
		{
			count.k = 0;
			while (str[count.i] && str[count.i] != '\"')
				minishell->lexer->tokens[count.j][count.k++] = str[count.i++];
			minishell->lexer->tokens[count.j][count.k] = '\0';
			count.j++;
		}
		count.i++;
	}
	// printf("%s\n", minishell->lexer->tokens[0]);
	// printf("%s\n", minishell->lexer->tokens[1]);
	minishell->lexer->tokens[count.j] = NULL;
	return (minishell);
}
// if (str[count.i] == '\'')
// {
	// count.k = 0;
	// while (str[count.i] && str[count.i] != '\'')
	// {
		// minishell->lexer->tokens[count.j][count.k++] = str[count.i++];
	// }
	// count.j++;
// }

int	ft_strlen_dquotes(char *str, int i)
{
	int	counter;
	int	length;

	counter = 0;
	length = 0;
	while (str[i] && counter != 2)
	{
		if (str[i] == '\"')
			counter++;
		length++;
	}
	if (counter == 0)
		return (-1);
	return (length);
}

int	number_of_dquotes(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while(str[i])
	{
		if (str[i] == '\"')
			counter++;
		i++;
	}
	return (counter);
}

void	print_struct(t_shell_s *args)
{

	t_counter	counter;

	counter.i = 0;
	counter.j = 0;
	counter.k = 0;
	counter.m = 0;
	counter.n = 0;
	printf("\nNUMBER OF COMMANDS: %i\n", args->num_commands);
	printf("\nNUMBER OF PIPES: %i\n", args->num_pipes);
	printf("\nPRINTING COMMANDS:\n");
	while (counter.i < args->num_commands)
		printf("%s\n", args->commands[counter.i++]);
	// printf("\nPRINTING RAW COMMANDS:\n");
	// while (counter.n < args->num_commands)
	// 	printf("%s\n", args->cmd_raw[counter.n++]);
	// printf("\nPRINTING COMMANDS PATH:\n");
	// while (counter.j < args->num_commands)
	// 	printf("%s\n", args->cmd_path[counter.j++]);
	// printf("\nPRINTING COMMANDS WITH NO FLAGS:\n");
	// while (counter.k < args->num_commands)
	// 	printf("%s\n", args->cmd_noflag[counter.k++]);
	// printf("\nPRINTING FULL PATH:\n%s\n", args->full_path);
	printf("\nPRINTING SPLIT PATHS:\n");
	while (args->path[counter.m])
		printf("%s\n", args->path[counter.m++]);
	printf("\n\n");
	return ;
}