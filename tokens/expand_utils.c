/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:41:30 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 14:49:37 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_to_end(char *str, size_t i, size_t start, size_t end)
{
	i += 1;
	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i += 1;
	end = i - 1;
	if (start < end)
		return (0);
	return (1);
}

int	move_to_end(t_shell *shell, char *str, size_t *i)
{
	*i += 1;
	shell->start = (int) *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	shell->end = (int)(*i - 1);
	if (shell->start < shell->end)
		return (0);
	return (1);
}

char	*create_env_var_str(t_shell *shell, char *str,
	size_t start, size_t end)
{
	char	*before;
	char	*env_var;
	char	*expansion;
	char	*after;

	before = ft_substr(str, 0, start - 1);
	env_var = ft_substr(str, start, end - start + 1);
	expansion = ft_getenv(shell, env_var);
	ft_free(env_var);
	after = ft_substr(str, end + 1, ft_strlen(str));
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

char	*get_env(const t_shell *shell, const char *name)
{
	size_t		i;
	char		**vars;
	char		*look_for;
	size_t		look_for_len;

	i = 0;
	vars = shell->env;
	if (name[0] == '?')
		return (ft_itoa(shell->last_exit_code));
	while (vars[i] != NULL)
	{
		look_for = ft_strjoin(name, "=");
		look_for_len = ft_strlen(look_for);
		if (ft_strncmp(vars[i], look_for, look_for_len) == 0)
		{
			ft_free(look_for);
			return (ft_substr(vars[i], look_for_len,
					ft_strlen(vars[i]) - look_for_len + 1));
		}
		if (look_for)
			ft_free(look_for);
		i++;
	}
	return (NULL);
}

void	set_which_quotes(char *str, size_t i, bool *single, bool *doubles)
{
	if (str[i] == '\'' && !doubles)
		*single = true;
	else if (str[i] == '\"' && !single)
		*doubles = true;
}
