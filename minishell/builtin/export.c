/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:01:44 by szubair           #+#    #+#             */
/*   Updated: 2023/03/07 12:19:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_export(t_env_s *env, const char *key, const char *value)
{
	int i;
	char *new_env_var;
	char **new_envp;
	char **new_key;
	char **new_value;

	i = 0;
	// Check if the key already exists in the environment
	while (i < env->env_size)
	{
	    if (ft_strncmp(env->key[i], key, ft_strlen(key)) == 0)
	    {
	        // Key already exists, update the value
	        free(env->value[i]);
	        env->value[i] = ft_strdup(value);
	        return;
	    }
		i++;
	}

	// Key does not exist, add a new environment variable
	new_env_var = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (new_env_var == NULL)
	{
	    write(2, "Error: Failed to allocate memory.\n",34);
	    return;
	}
	printf("declare -x %s%s\n", key, value);

	// Create new arrays with one extra element
	new_envp = malloc(sizeof(char *) * (env->env_size + 1));
	new_key = malloc(sizeof(char *) * (env->env_size + 1));
	new_value = malloc(sizeof(char *) * (env->env_size + 1));
	if (new_envp == NULL || new_key == NULL || new_value == NULL)
	{
	    write(2, "Error: Failed to allocate memory.\n",34);
	    free(new_env_var);
	    return;
	}

	i = 0;
	// Copy the existing arrays to the new arrays
	while (i < env->env_size)
	{
	    new_envp[i] = env->envp[i];
	    new_key[i] = env->key[i];
	    new_value[i] = env->value[i];
		i++;
	}

	// Free the old arrays
	free(env->envp);
	free(env->key);
	free(env->value);

	// Add the new environment variable to the new arrays
	new_envp[env->env_size] = new_env_var;
	new_key[env->env_size] = ft_strdup(key);
	new_value[env->env_size] = ft_strdup(value);

	// Update the environment structure
	env->envp = new_envp;
	env->key = new_key;
	env->value = new_value;
	env->env_size++;
}
//int main()
//{
//    t_env_s env;
//    env.env_size = 0;
//    env.envp = NULL;
//    env.key = NULL;
//    env.value = NULL;

//    // Add some environment variables
//    ft_export(&env, "HOME=", "/home/user");
//    ft_export(&env, "PATH=", "/usr/bin:/usr/local/bin");
//    ft_export(&env, "USER=", "user");

//    // Print the environment variables
//    for (int i = 0; i < env.env_size; i++) {
//        printf("%s", env.envp[i]);
//    }

//    // Clean up
//    for (int i = 0; i < env.env_size; i++) {
//        free(env.envp[i]);
//        free(env.key[i]);
//        free(env.value[i]);
//    }
//    free(env.envp);
//    free(env.key);
//    free(env.value);

//    return 0;
//}