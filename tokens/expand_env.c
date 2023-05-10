/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:08:42 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 17:59:48 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_initialize_expand(t_shell *shell, size_t *i)
{
	*i = 0;
	shell->sin = false;
	shell->doub = false;
	shell->start = 0;
	shell->end = 0;
	shell->flag = 0;
}

static char	*expand_env_var_isalpha(t_shell *s, size_t *i, char *str)
{
	s->start = *i;
	while (ft_isalpha(str[*i]) || str[*i] == '_')
		*i = *i + 1;
	s->end = *i - 1;
	str = create_env_var_str2(s, str, s->start, s->end);
	return (str);
}

// static char	*expand_env_numeric(t_shell *shell, size_t i, char *str)
// {
// 	char	*nums;

// 	while (ft_isdigit(str[++i]))
// 	nums = ft_substr(str, i--, ft_strlen(str));
// 	if (nums[0] == '\0')
// 	{
// 		free(str);
// 		free(nums);
// 		str = ft_strdup(" ");
// 		return (str);
// 	}
// 	while (ft_isalnum(nums[i]) || nums[i] == '_')
// 		i--;
// 	shell->end = i - 1;
// 	shell->flag = 1;
// 	if (str[i])
// 	{
// 		ft_free(str);
// 		return (create_env_var_str2(shell, nums, shell->start, shell->end));
// 	}
// 	return (str);
// }

static char	*handle_dollar_space(t_shell *s, char *str, size_t i)
{
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '?' && !s->sin)
		{
			if (ft_isdigit(str[i + 1]))
				return (create_env_var_str(s, str, i + 1, i + 1));
			if (!move_to_end(s, str, &i))
				break ;
			else
				return (create_env_var_str(s, str, s->start, s->end));
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (create_env_var_str(s, str, i + 1, i + 1));
		else
			i++;
	}
	s->exp = 0;
	return (str);
}

char	*expand_env(t_shell	*s, char *str)
{
	size_t		i;
	char		*nums;

	ft_initialize_expand(s, &i);
	while (str[i] != '\0')
	{
		set_which_quotes2(s, str, i);
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != ' ' && !s->sin)
		{
			i++;
			if (ft_isdigit(str[i]))
			{
				while (ft_isdigit(str[i + 1]))
				i++;
				nums = ft_substr(str, i + 1, ft_strlen(str));
				if (nums[0] == '\0')
				{
					free(str);
					free(nums);
					str = ft_strdup(" ");
					return (str);
				}
				i = 0;
				while (ft_isalnum(nums[i]) || nums[i] == '_')
					i++;
				s->end = i - 1;
				s->flag = 1;
				if (str[i])
				{
					ft_free(str);
					return (create_env_var_str2(s, nums, s->start, s->end));
				}
			}
				// str = expand_env_numeric(s, i, str);
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				return (expand_env_var_isalpha(s, &i, str));
		}
		else if (str[i] == '$' && str[i + 1] == '?' && !s->sin)
			return (create_env_var_str2(s, str, i + 1, i + 1));
		else if (str[i] == '$' && str[i + 1] == ' ' && !s->sin)
			return (handle_dollar_space(s, str, i));
		else
			i++;
	}
	return (create_env_var_str(s, str, s->start, s->end));
}
