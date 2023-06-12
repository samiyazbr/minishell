/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_double_q.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:03:12 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 13:45:21 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*next_token_dq(t_shell *shell, t_token *tkn, char *line)
{
	t_list	*res;

	res = NULL;
	if (tkn->end <= tkn->start)
		tkn->substr = ft_strdup("");
	else
		tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	if (!tkn->substr)
		return (throw_error(NULL));
	while (shell->exp == 1 && ft_is_dollar_env(tkn->substr))
	{
		if (ft_is_dollar_env(tkn->substr))
			tkn->substr = expand_env_original(shell, tkn->substr);
	}
	tkn->substr = trim_str_quotes(tkn->substr);
	if (!tkn->substr)
		return (tk_free_and_error(tkn));
	res = ft_lstnew(tkn);
	return (res);
}

static void	loop_token(char *l, size_t *y)
{
	char	quo;

	while (l[*y] != ' ' && l[*y] != '\0')
	{
		if (l[*y] == '\'' || l[*y] == '\"')
		{
			quo = l[*y];
			*y = *y + 1;
			while (l[*y] != quo && l[*y])
				*y = *y + 1;
			*y = *y + 1;
		}
		else
			*y = *y + 1;
	}
}

t_list	*token_a_double_quote(t_shell *minishell, char *l, size_t *i)
{
	size_t	y;
	t_token	*token;
	t_list	*res;

	res = NULL;
	token = ft_calloc(1, sizeof(t_token));
	y = *i;
	if (!token)
		return (NULL);
	token->start = y;
	token->type = DOUBLE_QUOTED_STRING;
	y++;
	while (l[y] && l[y] != '\"')
		y++;
	y++;
	loop_token(l, &y);
	token->end = y - 1;
	res = next_token_dq(minishell, token, l);
	if (!res)
		return (tk_free_and_null(token));
	*i = token->end;
	return (res);
}
