/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:01:32 by szubair           #+#    #+#             */
/*   Updated: 2023/05/03 14:59:15 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *ft_getenv(t_shell *minishell, const char *name)
{
    int i;
    int len;
	char *last_exit_code;

	last_exit_code = NULL;
    i = 0;
	if (!minishell || !minishell->env[i])
      return (NULL);
	else if (name[0] == '?')
	{
		last_exit_code = ft_itoa(minishell->last_exit_code);
		return (last_exit_code);
	}
    len = ft_strlen(name);
    while (minishell->env[i] != NULL)
    {
        if (ft_strncmp(minishell->env[i], name, len) == 0 && minishell->env[i][len] == '=')
            return (ft_substr(minishell->env[i], len + 1, ft_strlen(minishell->env[i])));
            //return (&minishell->env[i][len + 1]);
        i++;
    }
    return (NULL);
}
