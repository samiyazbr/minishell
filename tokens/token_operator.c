/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:00:30 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 15:12:29 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	break_after_space(t_token *tkn, size_t i)
{
	char	*new;

	new = ft_substr(tkn->substr, 0, i);
	ft_free(tkn->substr);
	tkn->substr = join_and_free(new, "", 1);
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
