/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:24:18 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 16:05:05 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_quotes_env(char *str, t_shell *s, size_t i)
{
	char	*before;
	char	*after;

	set_which_quotes2(s, str, i);
	str = trim_str_quotes(str);
	before = ft_substr(str, 0, i - 1);
	after = ft_substr(str, i, ft_strlen(str) - i);
	ft_free(str);
	str = join_and_free(before, after, 3);
	return (str);
}

static void	ft_free_and_create(t_shell *s, char *str,
		char **after, char **expansion)
{
	char	*env_var;

	env_var = ft_substr(str, s->start, s->end - s->start + 1);
	*expansion = ft_getenv(s, env_var);
	ft_free(env_var);
	*after = ft_substr(str, s->end + 1, ft_strlen(str));
	ft_free(str);
}

char	*ft_free_and_return_loop(t_shell *s, char *str,
	char *expansion, char *before )
{
	char	*after;

	ft_free_and_create(s, str, &after, &expansion);
	return (last_loop_alnum(str, after, expansion, before));
}

char	*ft_return_quotes_env(t_shell *s, char *str, size_t i)
{
	char		*before;
	char		*after;

	before = NULL;
	set_which_quotes2(s, str, i);
	str = handle_dollar_space(s, str, i);
	str = trim_str_quotes(str);
	if (i > 1)
		before = ft_substr(str, 0, i);
	after = ft_substr(str, i, ft_strlen(str) - i);
	ft_free(str);
	if (before != NULL)
		return (join_and_free(before, after, 2));
	return (join_and_free(after, "", 1));
}
