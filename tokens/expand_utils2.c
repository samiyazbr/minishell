/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:51:06 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 15:39:14 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_which_quotes2(t_shell *shell, char *str, size_t i)
{
	if (str[i] == '\'' && !shell->doub)
		shell->sin = true;
	else if (str[i] == '\"' && !shell->sin)
		shell->doub = true;
}

void	ft_initialize_expand(t_shell *shell, size_t *i)
{
	*i = 0;
	shell->sin = false;
	shell->doub = false;
	shell->start = 0;
	shell->end = 0;
	shell->flag = 0;
}

char	*expand_env_var_isalpha(t_shell *s, size_t *i, char *str)
{
	s->start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		*i = *i + 1;
	s->end = *i - 1;
	set_which_quotes2(s, str, *i);
	if (*i > ft_strlen(str))
		*i = ft_strlen(str);
	if (s->end)
		str = create_env_var_str2(s, str, (size_t)i);
	if (str[0] == '/' && str[0] != '\'' && str[0] != '\"'
		&& (ft_strchr(str, '\'') || ft_strchr(str, '\"')))
	{
		if (str && ft_strlen(str) > 0)
		{
			if ((str[*i] == '\'' || str[*i] == '\"'))
				str = remove_quotes(i, str);
		}
	}
	return (str);
}

static char	*new_expand_helper(t_shell *shell, char *str, size_t *i, size_t s)
{
	*i = *i + 1;
	while (str[*i] && (ft_isalpha(*i + 1) || str[*i + 1] == ' '))
		*i = *i + 1;
	return (create_env_var_str(shell, str, s, *i + 1));
}

void	new_expand(t_shell *shell, t_token *tkn, size_t	i)
{
	size_t	s;

	while (tkn->substr[i] != '\0')
	{
		if (tkn->substr[i] == '$' && tkn->substr[i + 1] != '?'
			&& tkn->substr[i + 1] != ' ' && tkn->substr[i + 1] != '_'
			&& tkn->substr[i + 1] != '\0')
		{
			i++;
			s = i++;
			if (ft_isdigit(tkn->substr[i]))
				tkn->substr = expand_num_sq(tkn, s);
			else if (ft_isalpha(tkn->substr[i + 1]))
			{
				tkn->substr = new_expand_helper(shell, tkn->substr, &i, s);
				i = 0;
			}
		}
		else if (tkn->substr[i] == '$' && tkn->substr[i + 1] == '?')
			tkn->substr = create_env_var_str(shell, tkn->substr, i + 1, i + 1);
		i++;
	}
}
