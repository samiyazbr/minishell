/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/05 15:37:31 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	initialize_in_str2(char **env_var, char **before,
	char **expansion, size_t *i)
{
	*env_var = NULL;
	*before = NULL;
	*expansion = NULL;
	*i = 0;
}

static char	*handle_flag_helper(t_shell *shell, char *str,
	char *env_var, char *expansion)
{
	if (shell->flag == 0)
	{
		env_var = ft_substr(str, shell->start, shell->end - shell->start + 1);
		expansion = ft_getenv(shell, env_var);
		ft_free(env_var);
	}
	else
	{
		shell->flag = 0;
		expansion = NULL;
	}
	return (expansion);
}

static void	ft_alnum_helper(char *expansion, char *before, char **str)
{
	if (!expansion)
		*str = join_and_free(before, "", 1);
	else
		*str = join_and_free(before, expansion, 3);
}

char	*last_loop_alnum(char *str, char *after, char *expansion, char *before)
{
	ft_alnum_helper(expansion, before, &str);
	str = join_and_free(str, after, 3);
	return (str);
}

char	*create_env_var_str2(t_shell *s, char *str, size_t i)
{
	char	*before;
	char	*env_var;
	char	*expansion;
	char	*after;

	initialize_in_str2(&env_var, &before, &expansion, &i);
	if (s->flag == 0)
		expansion = handle_flag_helper(s, str, env_var, before);
	before = ft_substr(str, 0, s->start - 1);
	ft_free(env_var);
	after = ft_substr(str, s->end + 1, ft_strlen(str));
	ft_free(str);
	if (!expansion)
		str = join_and_free(before, "", 1);
	if (expansion && before)
		str = join_and_free(before, expansion, 3);
	if (expansion && !before)
		str = join_and_free(expansion, "", 1);
	if (after)
		str = join_and_free(str, after, 3);
	if (ft_is_dollar_env(str))
		str = last_loop_helper_env2(str, s, i, expansion);
	return (str);
}
