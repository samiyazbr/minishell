/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:23:48 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 15:29:05 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_is_digit(char *str, t_shell *shell,
	size_t i, char *expansion)
{
	char	*before;
	char	*after;
	char	*env_var;

	before = ft_substr(str, 0, i);
	env_var = ft_substr(str, i + 1, 1);
	expansion = ft_getenv(shell, env_var);
	ft_free(env_var);
	after = ft_substr(str, i + 2, ft_strlen(str));
	ft_free(str);
	if (!expansion)
		str = join_and_free(before, "", 1);
	else
	{
		if (expansion && before)
			str = join_and_free(before, expansion, 3);
		else
			str = join_and_free(expansion, "", 1);
	}
	str = join_and_free(str, after, 3);
	return (str);
}

static char	*loop_move_end(char *str, size_t *i, t_shell *s)
{
	char	*before;

	*i = *i + 1;
	s->start = *i;
	before = ft_substr(str, 0, s->start - 1);
	while ((ft_isalnum(str[*i]) || str[*i] == '_') && str[*i] != '\0')
		*i = *i + 1;
	s->end = *i - 1;
	return (before);
}

static char	*last_helper(char *str, t_shell *s, size_t i)
{
	i++;
	if (str[i] == '\"' || str[i] == '\'')
		return (ft_quotes_env(str, s, i));
	else if (ft_isdigit(str[i]))
		return (numeric_helper(str, i, s));
	else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
		return (expand_env_var_isalpha(s, &i, str));
	else
		return (str);
}

char	*last_loop_helper_env2(char *str, t_shell *s, size_t i, char *expansion)
{
	char	*before;

	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' ')
			return (last_helper(str, s, i));
		else if (str[i] == '$' && str[i + 1] != '?')
		{
			if (ft_isdigit(str[i + 1]))
				str = handle_is_digit(str, s, i, expansion);
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			{
				before = loop_move_end(str, &i, s);
				return (ft_free_and_return_loop(s, str, expansion, before));
			}
		}
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 2] == '\0')
			return (create_env_var_str(s, str, i + 1, i + 1));
		else if (str[i] == '$' && str[i + 1] == '?')
			return (expand_env(s, str));
		i++;
	}
	return (str);
}
