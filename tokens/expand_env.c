/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 16:10:22 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_dollar_move(char *str, size_t *i, size_t *start)
{
	*start = *i + 1;
	*i = *i + 1;
	while (str[*i] && ft_isalpha(str[*i + 1]))
			*i = *i + 1;
}

char	*handle_dollar_space(t_shell *s, char *str, size_t i)
{
	size_t	start;

	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '=' && !s->sin)
		{
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			{
				handle_dollar_move(str, &i, &start);
				str = create_env_var_str(s, str, start, i);
				i = start;
			}
			else if (ft_isdigit(str[i + 1]))
				str = create_env_var_str(s, str, i + 1, i + 1);
			else
				str = create_env_var_str(s, str, s->start, s->end);
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (create_env_var_str(s, str, i + 1, i + 1));
		i++;
	}
	s->exp = 0;
	return (str);
}

static char	*handle_question_helper(t_shell *s, char *str, size_t i)
{
	s->start = i + 1;
	s->end = i + 1;
	return (create_env_var_str2(s, str, i));
}

char	*expand_env(t_shell	*s, char *str)
{
	size_t		i;

	ft_initialize_expand(s, &i);
	while (str[i] != '\0')
	{
		set_which_quotes2(s, str, i);
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' ' && !s->sin)
		{
			i++;
			if (str[i] == '\"' || str[i] == '\'')
				return (ft_return_quotes_env(s, str, i));
			else if (ft_isdigit(str[i]))
				return (numeric_helper(str, i, s));
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				return (expand_env_var_isalpha(s, &i, str));
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (handle_question_helper(s, str, i));
		else if (str[i] == '$' && str[i + 1] == ' ' && !s->sin)
			return (handle_dollar_space(s, str, i));
		else
			i++;
	}
	return (create_env_var_str(s, str, s->start, s->end));
}
