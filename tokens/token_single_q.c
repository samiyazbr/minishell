/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_single_q.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:46:50 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 13:31:08 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_num_sq(t_token *tkn, size_t start)
{
	char		*nums;
	char		*before;

	before = ft_substr(tkn->substr, 0, start - 2);
	nums = ft_substr(tkn->substr, start, ft_strlen(tkn->substr));
	ft_free(tkn->substr);
	return (join_and_free(before, nums, 3));
}

static void	initialize_next_token(t_token *tkn, char *line, size_t *i)
{
	if (tkn->end <= tkn->start)
		tkn->substr = ft_strdup("");
	else
		tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	*i = 0;
}

static size_t	position_second_last_quote(char *l, int c)
{
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	while (l[i])
		i++;
	while (i > 0)
	{
		if (l[i] == ch)
		{
			return (i);
		}
		i--;
	}
	return (0);
}

t_list	*next_token_sq(t_shell *shell, t_token *tkn, char *line)
{
	t_list	*res;
	size_t	i;

	initialize_next_token(tkn, line, &i);
	if (!tkn->substr)
		return (tk_free_and_error(tkn));
	i = position_second_last_quote(tkn->substr, '\'');
	if (ft_is_dollar_env(tkn->substr))
	{
		i++;
		if (tkn->substr[i] == '\"')
			i++;
		new_expand(shell, tkn, i);
	}
	tkn->substr = trim_str_quotes(tkn->substr);
	res = ft_lstnew(tkn);
	return (res);
}

t_list	*token_a_single_quote(t_shell *minishell, char *line, size_t *i)
{
	size_t	y;
	t_token	*token;
	t_list	*res;

	res = NULL;
	y = *i;
	token = ft_calloc(1, sizeof(t_token));
	token->start = y;
	token->type = QUOTED_STRING;
	y++;
	while (line[y] && line[y] != '\'')
		y++;
	if (line[y] == '\0')
		return (free_parseerror(token, 2));
	y++;
	while ((line[y] != ' ' && line[y] != '\t') && line[y] != '\0')
		y++;
	token->end = y - 1;
	res = next_token_sq(minishell, token, line);
	if (!res)
		return (free_parseerror(token, 1));
	*i = token->end;
	return (res);
}
