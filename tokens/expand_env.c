/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/02 17:34:47 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_which_quotes(char *str, size_t i, bool *single, bool *doubles)
{
	if (str[i] == '\'' && !doubles)
		*single = true;
	else if (str[i] == '\"' && !single)
		*doubles = true;
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

char	*create_env_var_str(t_shell *shell, char *str,
	size_t start, size_t end)
{
	char	*before;
	char	*env_var;
	char	*expansion;
	char	*after;

	before = ft_substr(str, 0, start - 1);
	printf("before:%s:\n", before);
	env_var = ft_substr(str, start, end - start + 1);
	printf("env_var:%s:\n", env_var);
	expansion = ft_getenv(shell, env_var);
	ft_free(env_var);
	after = ft_substr(str, end + 1, ft_strlen(str));
	ft_free(str);
	if(!expansion)
	str = join_and_free(before, "", 1);
	else
	{
		if (expansion && before)
			str = join_and_free(before, expansion, 1);
		else
			str = join_and_free(expansion, "", 1);
	}
	str = join_and_free(str, after, 3);
	printf("Str after expansion: %s\n", str);
	return (str);
}

int	move_to_end(char *str, size_t *i, size_t *start, size_t *end)
{
	*i += 1;
	*start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	*end = *i - 1;
	if (start < end)
		return (0);
	return (1);
}

char	*expand_env(t_shell	*shell, char *str, int *expand)
{
	size_t		i;
	size_t		start;
	size_t		end;
	bool		single;
	bool		doubles;

	i = 0;
	single = false;
	doubles = false;
	while (str[i] != '\0')
	{
		set_which_quotes(str, i, &single, &doubles);
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' ' && !single)
		{
			if (ft_isdigit(str[i + 1]))
				return (create_env_var_str(shell, str, i + 1, i + 1));
			if (!move_to_end(str, &i, &start, &end))
				break ;
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !single)
			return (create_env_var_str(shell, str, i + 1, i + 1));
		
		else if (str[i] == '$' && str[i + 1] == ' ' && !single)
		{
			i++;
			while(str[i] != '\0')
			{
				if(str[i]== '$'&& str[i + 1] != '?' && !single)
				{
					printf("I have the next $\n");
					if (ft_isdigit(str[i + 1]))
					{
						printf("I have a digit after $\n");
						return (create_env_var_str(shell, str, i + 1, i + 1));
					}
					if (!move_to_end(str, &i, &start, &end))
					{
						printf("Am I breaking?\n");
						break ;
					}
					else
						return (create_env_var_str(shell, str, start, end));
				}
				else if (str[i] == '$' && str[i + 1] == '?' && !single)
					return (create_env_var_str(shell, str, i + 1, i + 1));
				else if (str[i] == '$' && str[i + 1] == ' ' && !single)
					return (expand_loop(shell, str, expand, &i, &start, &end, single));
				else
					i++;
			}
			*expand = 0;
			printf("str: %s\n", str);
			return (str);
		}
		else	
			i++;
	}
	return (create_env_var_str(shell, str, start, end));
}
