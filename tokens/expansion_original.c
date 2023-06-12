/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_original.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:44:44 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 16:00:46 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env_var_isalpha_basic(t_shell *s, size_t *i, char *str)
{
	s->start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		*i = *i + 1;
	s->end = *i - 1;
	str = create_env_var_str2(s, str, (size_t)i);
	return (str);
}

static char	*handle_dollar_space_original(t_shell *s, char *str, size_t i)
{
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '?' && !s->sin)
		{
			if (ft_isdigit(str[i + 1]))
				return (create_env_var_str(s, str, i + 1, i + 1));
			if (!move_to_end(s, str, &i))
				break ;
			else
				return (create_env_var_str(s, str, s->start, s->end));
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (create_env_var_str(s, str, i + 1, i + 1));
		else
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

char	*expand_env_original(t_shell	*s, char *str)
{
	size_t		i;

	ft_initialize_expand(s, &i);
	while (str[i] != '\0')
	{
		set_which_quotes2(s, str, i);
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' ' && !s->sin)
		{
			i++;
			if (ft_isdigit(str[i]))
				return (numeric_helper(str, i, s));
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				return (expand_env_var_isalpha_basic(s, &i, str));
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (handle_question_helper(s, str, i));
		else if (str[i] == '$' && str[i + 1] == ' ' && !s->sin)
			return (handle_dollar_space_original(s, str, i));
		else
			i++;
	}
	return (create_env_var_str(s, str, s->start, s->end));
}
