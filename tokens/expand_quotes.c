/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:34:36 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 13:37:37 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*after_free_join(char *str, size_t y, size_t z, char *before)
{
	char	*after;

	after = ft_substr(str, y, z - y);
	ft_free(str);
	return (join_and_free(before, after, 3));
}

static char	*remove_qu_loop(char *str)
{
	size_t	y;
	size_t	z;
	char	*before;

	z = 0;
	while (str[z] != '\0')
	{
		if ((str[z] == '\'' || str[z] == '\"')
			&& (str[0] != '\'' && str[0] != '\"'))
		{
			before = ft_substr(str, 0, z);
			y = z + 1;
			z++;
			while (str[z] != '\'' && str[z] != '\"' && str[z] != '\0')
				z++;
			if ((str[z] == '\'' || str[z] == '\"') && str[z + 1] == '\0')
				return (after_free_join(str, y, z, before));
			ft_free(before);
		}
		z++;
	}
	return (str);
}

static char	*after_remaining(size_t z, char *after, char *before, char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	before = join_and_free(before, after, 3);
	after = ft_substr(str, z + 1, len);
	ft_free(str);
	str = remove_qu_loop(after);
	return (join_and_free(before, str, 3));
}

char	*remove_quotes(size_t *i, char *str)
{
	size_t	y;
	size_t	z;
	char	*before;
	char	*after;

	before = ft_substr(str, 0, *i);
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		z = *i + 1;
		y = *i + 1;
		while (str[z] != '\'' && str[z] != '\"' && str[z] != '\0')
			z++;
		after = ft_substr(str, y, z - y);
		if ((str[z] == '\'' || str[z] == '\"') && str[z + 1] == '\0')
		{
			ft_free(str);
			return (join_and_free(before, after, 3));
		}
		else
			return (after_remaining(z, after, before, str));
	}
	ft_free(before);
	return (str);
}
