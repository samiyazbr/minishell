/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:00:30 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 12:40:43 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*check_to_end_of_token(char *line, size_t *y, t_token *token)
{
	char	is_quote;

	while (line[*y] != ' ' && line[*y] != '\0')
	{
		if (line[*y] == '\'' || line[*y] == '\"')
		{
			is_quote = line[*y];
			y++;
			while (line[*y] != is_quote && line[*y])
					y++;
			if (!line[*y])
				return (throw_error("Error: Unterminated string\n"));
			y++;
		}
		else if (!ft_strchr("|&()><", line[*y]))
			break ;
		else
			y++;
	}
	return (token);
}

t_list	*next_token(t_shell *shell, t_token *tkn, char *line)
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
		{
			tkn->substr = expand_env(shell, tkn->substr);
		}
	}
	if (ft_strchr(tkn->substr, '*') == NULL)
		tkn->substr = trim_str_quotes(tkn->substr);
	if (!tkn->substr)
		return (tk_free_and_error(tkn));
	res = ft_lstnew(tkn);
	return (res);
}

t_list	*token_a_double_quote(t_shell *minishell, char *line, size_t *i)
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
	while (line[y] && line[y] != '\"')
		y++;
	if (line[y] == '\0')
		return (tk_free_and_error(token));
	y++;
	if (!check_to_end_of_token(line, &y, token))
		return (tk_free_and_null(token));
	token->end = y - 1;
	res = next_token(minishell, token, line);
	if (!res)
		return (tk_free_and_null(token));
	*i = token->end;
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
	if (!check_to_end_of_token(line, &y, token))
		return (free_parseerror(token, 1));
	token->end = y - 1;
	minishell->exp = 0;
	res = next_token(minishell, token, line);
	if (!res)
		return (free_parseerror(token, 1));
	*i = token->end;
	return (res);
}

t_list	*token_operator(char *line, size_t *i)
{
	t_token_type	typ;
	t_token			*token;
	t_list			*res;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->start = *i;
	ft_is_token_type(&typ, line, i);
	token->type = typ;
	token->end = *i;
	if (typ == APPEND || typ == HEREDOC || typ == LAST_EXIT)
	{
		token->end += 1;
		*i += 1;
		token->substr = ft_substr(line, token->start, 2);
	}
	else
		token->substr = ft_substr(line, token->start, 1);
	res = ft_lstnew(token);
	if (!res)
		return (NULL);
	return (res);
}
