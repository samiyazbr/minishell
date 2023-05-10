/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:01:32 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:26:35 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_getenv(t_shell *shell, const char *name)
{
	int		i;
	int		len;
	char	*last_exit_code;

	last_exit_code = NULL;
	i = 0;
	if (!shell || !shell->env[i])
		return (NULL);
	else if (name[0] == '?')
	{
		last_exit_code = ft_itoa(shell->last_exit_code);
		return (last_exit_code);
	}
	len = ft_strlen(name);
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (ft_substr(shell->env[i], len + 1,
					ft_strlen(shell->env[i])));
		i++;
	}
	return (NULL);
}
