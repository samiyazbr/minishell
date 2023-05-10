/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 17:45:37 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	create_env2_isdigit(char *str, t_shell *s, char *before, size_t *i)
// {
// 	char	*env_var;
// 	char	*expansion;
// 	char	*after;

// 	before = ft_substr(str, 0, *i);
// 	env_var = ft_substr(str, *i + 1, 1);
// 	expansion = ft_getenv(s, env_var);
// 	ft_free(env_var);
// 	after = ft_substr(str, *i + 2, ft_strlen(str));
// 	ft_free(str);
// 	if (!expansion)
// 		str = join_and_free(before, "", 1);
// 	else
// 	{
// 		if (expansion && before)
// 			str = join_and_free(before, expansion, 3);
// 		else
// 			str = join_and_free(expansion, "", 1);
// 	}
// 	str = join_and_free(str, after, 3);
// }

char	*create_env_var_str2(t_shell *shell, char *str,
	size_t start, size_t end)
{
	char	*before;
	char	*env_var;
	char	*expansion;
	char	*after;
	size_t	i;

	expansion = NULL;
	if (shell->flag == 0)
	{
		env_var = ft_substr(str, start, end - start + 1);
		expansion = ft_getenv(shell, env_var);
		before = ft_substr(str, 0, start - 1);
	}
	else
	{
		env_var = ft_substr(str, start, end - start + 1);
		before = ft_substr(str, 0, start - 1);
		shell->flag = 0;
	}
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
	if (after)
		str = join_and_free(str, after, 3);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?')
		{
			if (ft_isdigit(str[i + 1]))
			{
				start = end = i + 1;
				before = ft_substr(str, 0, start - 1);
				env_var = ft_substr(str, start, end - start + 1);
				expansion = ft_getenv(shell, env_var);
				ft_free(env_var);
				after = ft_substr(str, end + 1, ft_strlen(str));
				ft_free(str);
				if(!expansion)
				str = join_and_free(before, "", 1);
				else
				{
					if (expansion && before)
						str = join_and_free(before, expansion, 3);
					else
						str = join_and_free(expansion, "", 1);
				}
				str = join_and_free(str, after, 3);
			}
				//create_env2_isdigit(str, shell, before, &i);
			else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
			{
				i++;
				start = i;
				before = ft_substr(str, 0, start - 1);
				while ((ft_isalnum(str[i]) || str[i] == '_') && str[i] != '\0')
					i++;
				end = i - 1;
				env_var = ft_substr(str, start, end - start + 1);
				expansion = ft_getenv(shell, env_var);
				ft_free(env_var);
				after = ft_substr(str, end + 1, ft_strlen(str));
				ft_free(str);
				if (!expansion)
					str = join_and_free(before, "", 1);
				else
					str = join_and_free(before, expansion, 3);
				str = join_and_free(str, after, 3);
			}
		}
		else if (str[i] == '$' && str[i + 1] == '?' && str[i + 2] == '\0')
			return (create_env_var_str(shell, str, i + 1, i + 1));
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (str);
}
