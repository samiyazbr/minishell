/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:01:32 by szubair           #+#    #+#             */
/*   Updated: 2023/03/05 12:03:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *ft_getenv(t_shell_s *minishell, const char *name)
{
    int i;
    int len;

    i = 0;
	if (!minishell || !minishell->envp || minishell->envp->envp[i] == NULL)
      return (NULL);

    len = ft_strlen(name);
    while (minishell->envp->envp[i] != NULL)
    {
        if (ft_strncmp(minishell->envp->envp[i], name, len) == 0 && minishell->envp->envp[i][len] == '=')
            return (&minishell->envp->envp[i][len + 1]);
        i++;
    }
    return (NULL);
}
