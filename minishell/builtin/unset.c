/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:17:55 by szubair           #+#    #+#             */
/*   Updated: 2023/03/06 10:52:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_unset(t_env_s *env, const char *key_to_unset)
{
    int i, j;
	i = 0;
    while (i < env->env_size)
    {
        if (ft_strncmp(env->key[i], key_to_unset, ft_strlen(key_to_unset)) == 0)
        {
            free(env->key[i]);
            free(env->value[i]);
			j = i;
            while (j < env->env_size - 1)
            {
                env->key[j] = env->key[j+1];
                env->value[j] = env->value[j+1];
                env->envp[j] = env->envp[j+1];
				j++;
            }
            env->envp[j] = NULL;
            env->key[j] = NULL;
            env->value[j] = NULL;
            env->env_size--;
            break;
        }
		i++;
    }
}
