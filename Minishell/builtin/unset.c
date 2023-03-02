/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:17:55 by szubair           #+#    #+#             */
/*   Updated: 2023/02/17 16:35:29 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char **environ;

int	ft_unset(const char *name) {
	char	**env;
	int		i;
	int		length;

	length = 0;
	i = 0;
	env = environ;
	while (env[i] != NULL) 
	{
		length = ft_strlen(name);
		if (ft_strncmp(env[i], name, length) == 0 && env[i][length] == '=')
		{
			break;
		}
		i++;
	}
	if (env[i] == NULL)
	{
		return (1);
	}

	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}

	return (0);
}
