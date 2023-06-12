/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_plain_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:53:36 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 14:49:46 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_isalpha(char *str, size_t *i)
{
	*i = *i + 1;
	while (str[*i] && (ft_isalpha(str[*i + 1])))
		*i = *i + 1;
}

static void	reset_index(size_t *i, char *str)
{
	if (*i > ft_strlen(str))
		*i = ft_strlen(str);
}

static void	plain_expand(t_shell *s, t_token *t, size_t i)
{
	size_t	x;

	while (t->substr[i] != '\0')
	{
		set_which_quotes2(s, t->substr, i);
		if (t->substr[i] == '$' && t->substr[i + 1] != '?'
			&& t->substr[i + 1] != ' ' && !s->sin)
		{
			i++;
			x = i++;
			if (ft_isdigit(t->substr[i]))
				t->substr = expand_num_sq(t, x);
			else if (ft_isalpha(t->substr[i + 1]) || t->substr[i + 1] == '_')
			{
				loop_isalpha(t->substr, &i);
				t->substr = create_env_var_str(s, t->substr, x, i);
				reset_index(&i, t->substr);
			}
		}
		if (t->substr[i] == '$' && t->substr[i + 1] == '?' && !s->sin)
				t->substr = create_env_var_str(s, t->substr, i + 1, i + 1);
		if (t->substr[i] == '\0')
			break ;
		i++;
	}
}

int	plain_text_part(t_shell *shell, char *line,
	size_t *idx, t_list **tokens)
{
	t_token	*tkn;
	size_t	i;

	i = *idx;
	tkn = plain_text_part2(idx);
	if (!tkn)
		return (1);
	while (line[i] && ft_strchr(" \'\"|(<&>)", line[i]) == NULL)
		i++;
	if (line[i] == ')')
		return (tks_clear_and_return(tokens));
	to_end_of_token(line, &i, tkn);
	if (ft_is_dollar_env(tkn->substr))
	{
		i = 0;
		plain_expand(shell, tkn, i);
	}
	tkn->substr = trim_str_dollar(tkn->substr);
	tkn->substr = trim_str_quotes(tkn->substr);
	if (!tkn->substr)
		return (throw_error_and_return2(tkn));
	ft_lstadd_back(tokens, ft_lstnew(tkn));
	*idx = tkn->end;
	return (0);
}
