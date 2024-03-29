/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:01:18 by szubair           #+#    #+#             */
/*   Updated: 2023/05/30 13:46:24 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd(char **env, t_shell *shell)
{
	char	*pwd;
	int		i;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_getenv(shell, "PWD");
	if (!pwd)
		return ;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
		{
			ft_free2(&env[i]);
			env[i] = ft_strjoin("PWD=", pwd);
			break ;
		}
	}
	ft_free2(&pwd);
}

void	update_oldpwd(t_shell *shell, char **env, char *oldpwd)
{
	int		i;
	char	*create_oldpwd;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], 7))
		{
			ft_free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
			break ;
		}
	}
	if (env[i] == NULL)
	{
		create_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		update_env(shell, create_oldpwd);
		ft_free2(&create_oldpwd);
	}
}

void	cd_to_path(t_shell *shell, t_exec *step, char **env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_getenv(shell, "PWD");
	if (!oldpwd)
		return ;
	if (!chdir(step->cmd->arg_arr[1]) && ft_strlen(oldpwd))
	{
		update_pwd(env, shell);
		update_oldpwd(shell, env, oldpwd);
		step->exit_code = 0;
	}
	else if (chdir(step->cmd->arg_arr[1]) == -1)
	{
		printf("minishell: cd: %s: %s\n", step->cmd->arg_arr[1],
			strerror(errno));
		step->exit_code = 1;
	}
	ft_free2(&oldpwd);
}

void	cd_to_home(t_shell *shell, t_exec *step, char **env, char *home)
{
	int		i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp("HOME=", env[i], 5))
			home = ft_substr(env[i], 5, ft_strlen(env[i]));
	if (home)
		move_to_home(shell, step, env, home);
	else
	{
		perror("minishell: cd: HOME not set\n");
		step->exit_code = 1;
	}
}

void	ft_cd(t_exec *step, char **env, t_shell *shell)
{
	char	*home;

	if (step->cmd->arg_arr[1])
		cd_to_path(shell, step, env);
	else
	{
		home = NULL;
		cd_to_home(shell, step, env, home);
	}
	shell->last_exit_code = step->exit_code;
}
