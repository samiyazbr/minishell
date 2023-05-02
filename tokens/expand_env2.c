/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/02 14:37:46 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_loop(t_shell *shell, char *str, int *expand, size_t *i, size_t *start, size_t *end, bool single)
{
	*i = *i + 1;
	while (str[*i] != '\0' || str[*i] != ' ')
	{
		if(str[*i]== '$'&& str[*i + 1] != '?' && !single)
		{
			printf("I have the next $\n");
			if (ft_isdigit(str[*i + 1]))
			{
				printf("I have a digit after $\n");
				return (create_env_var_str(shell, str, *(i + 1), *(i + 1)));
			}
			if (!move_to_end(str, i, start, end))
			{
				printf("Am I breaking?\n");
				break ;
			}
			else
				return (create_env_var_str(shell, str, *start, *end));
		}
		else if (str[*i] == '$' && str[*i + 1] == '?' && !single)
			return (create_env_var_str(shell, str, *i + 1, *i + 1));
		else
			i++;
	}
	*expand = 0;
	printf("str in loop: %s\n", str);
	return (str);
}
