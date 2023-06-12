/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:45:15 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 14:46:17 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*check_token_errors(char *line, int *error)
{
	size_t	i;
	char	end_char;
	int		is_end;

	i = 0;
	end_char = '\0';
	is_end = 0;
	while (line[i])
	{
		set_quotes_at_end(line[i], &end_char, &is_end);
		if (!is_end && (line[i] == '\\' || line[i] == ';' || line[i] == '`'
				|| (line[i] == '&' && line[i + 1] != '&')
				|| (line[i] == '(' && line[i + 1] == ')')))
		{
			printf("Parse error: Invalid input\n");
			*error = 1;
			return (error);
		}
		if (!is_end && (line[i] == '&' && line[i + 1] != '\0'))
			i++;
		i++;
	}
	return (0);
}

int	first_part_quotes(t_shell *minishell, char *line,
	size_t *i, t_list **tokens)
{
	t_list	*new;

	new = NULL;
	if (line[*i] == '\'')
		new = token_a_single_quote(minishell, line, i);
	else if (line[*i] == '\"')
	{
		minishell->exp = !last_was_heredoc(*tokens);
		new = token_a_double_quote(minishell, line, i);
	}
	else if (is_operator(line, *i))
		new = token_operator(line, i);
	else
		new = token_nested_expr(minishell, line, i);
	if (new == NULL)
	{
		ft_lstclear(tokens, free_token);
		return (1);
	}
	ft_lstadd_back(tokens, new);
	return (0);
}

int	second_part_env(t_shell *minishell, char *line, size_t *i,
	t_list **tokens)
{
	t_list	*new;

	if (line[*i] == '$' && line[*i] != ' ' && !last_was_heredoc(*tokens))
	{
		new = token_an_env(minishell, line, i);
		if (new == NULL)
		{
			ft_lstclear(tokens, free_token);
			throw_error("Parse error\n");
			return (1);
		}
		if (clean_token_env(&new, tokens))
		{
			ft_lstclear(tokens, free_token);
			return (1);
		}
	}
	else if (line[*i] == ')')
	{
		ft_lstclear(tokens, free_token);
		throw_error("Parse error\n");
		return (1);
	}
	return (0);
}

static int	ft_def(size_t *len, int *error)
{
	*error = 0;
	*len = 0;
	return (1);
}

t_list	*tokenize_the_input(t_shell *minishell, char *line, int *er)
{
	t_list	*res;
	size_t	len;

	if (ft_def(&len, er) && check_token_errors(line, er))
		return (NULL);
	res = NULL;
	while (line[len])
	{
		if (is_special_red(line, len, minishell))
			len++;
		else if (line[len] == '\'' || line[len] == '\"'
			|| is_operator(line, len) || line[len] == '(')
				*er = first_part_quotes(minishell, line, &len, &res);
		else if ((line[len] == '$' && last_was_heredoc(res) == 0)
			|| line[len] == ')')
				*er = second_part_env(minishell, line, &len, &res);
		else if (line[len] != ' ' && line[len] != '\t' && line[len] != '\n'
			&& line[len] != '\v' && line[len] != '\f' && line[len] != '\r')
			*er = plain_text_part(minishell, line, &len, &res);
		if (*er == 1)
			return (NULL);
		if (line[len] != '\0')
			len++;
	}
	return (res);
}
