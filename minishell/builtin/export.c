/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:01:44 by szubair           #+#    #+#             */
/*   Updated: 2023/02/17 17:35:09 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_export(char **args)
{
	
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int	ft_export(const char *name, const char *value) {
    int	i;
	i = 0;
    int	length = 0;
    char *env_var;
    char *new_env_var;

    // If value is NULL, the user only wants to print the environment variable
    if (value == NULL) {
        while (environ[i] != NULL) {
            length = strlen(name);
            if (strncmp(environ[i], name, length) == 0 && environ[i][length] == '=') {
                printf("%s\n", environ[i]);
                return 0;
            }
            i++;
        }
        return 1;
    }

    // Otherwise, the user wants to set the environment variable
    length = strlen(name) + strlen(value) + 2;
    new_env_var = (char *) malloc(length * sizeof(char));

    if (new_env_var == NULL) {
        return 1;
    }

    snprintf(new_env_var, length, "%s=%s", name, value);
    env_var = getenv(name);

    if (env_var != NULL) {
        // If the variable already exists, overwrite its value
        if (setenv(name, value, 1) != 0) {
            free(new_env_var);
            return 1;
        }
    } else {
        // If the variable does not exist, add it to the environment
        if (putenv(new_env_var) != 0) {
            free(new_env_var);
            return 1;
        }
    }

    free(new_env_var);
    return 0;
}