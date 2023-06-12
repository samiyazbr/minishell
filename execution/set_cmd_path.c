/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:31 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:05:06 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_cmd_path(t_shell *shell, t_exec *step)
{
	char	*cmd_copy;

	if (step->cmd->arg_arr[0] && step->cmd->arg_arr[0][0] != '\0'
		&& access(step->cmd->arg_arr[0], X_OK) == -1
		&& !is_builtin(step) && !is_dir(step->cmd->arg_arr[0])
		&& ft_strchr(step->cmd->arg_arr[0], '/') == NULL)
	{
		cmd_copy = get_full_path(step->cmd->arg_arr[0], shell->env);
		if (cmd_copy != NULL)
			step->cmd->arg_arr[0] = cmd_copy;
	}
}

static void	join_path(char *bin, char **paths, char **path)
{
	int	i;

	i = 0;
	while (bin != NULL && paths != NULL && paths[i] != NULL)
	{
		*path = ft_strjoin(paths[i], bin);
		if (*path == NULL || access(*path, F_OK) != -1)
			break ;
		ft_free2(path);
		i++;
	}
}

char	*get_full_path(char *bin, char **env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*bin_cpy;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	i = 0;
	bin_cpy = ft_strdup(bin);
	bin = join_and_free("/", bin, 2);
	join_path(bin, paths, &path);
	ft_free2(&bin);
	ft_free_array(paths);
	if (path == NULL)
	{
		return (bin_cpy);
	}
	ft_free2(&bin_cpy);
	return (path);
}
