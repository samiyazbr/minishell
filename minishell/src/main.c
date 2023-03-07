/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:51:24 by codespace         #+#    #+#             */
/*   Updated: 2023/03/07 12:41:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_shell_s *minishell, int i,char **env)
{
	int j;
	int arg_count;

	if (ft_strncmp(minishell->command_block[i]->command, "echo", 4) == 0)
		return (ft_echo(minishell->command_block[i]->args));
	else if (ft_strncmp(minishell->command_block[i]->command, "env", 3) == 0)
		return (ft_env(env, minishell->command_block[i]->args));
	else if(ft_strncmp(minishell->command_block[i]->command, "cd", 2) == 0)
	{
		while (minishell->command_block[i]->args)
		{
			arg_count++;
		}
		return(cd(minishell->command_block[i]->args, arg_count, minishell));
	}
	else if (ft_strncmp(minishell->command_block[i]->command, "pwd", 3) == 0)
		return (ft_pwd(minishell->command_block[i]->args));
	else if (ft_strncmp(minishell->command_block[i]->command, "unset", 5) == 0)
	{
		ft_unset(minishell->envp, minishell->command_block[i]->args[1]);
		return (0);
	}
	else if (ft_strncmp(minishell->command_block[i]->command, "export", 5) == 0)
	{
		while(j < minishell->envp->env_size)
		{
			j = 0;
			ft_export(minishell->envp, minishell->envp->key[j], minishell->envp->value[i]);
			j++;
		}
		if (j == minishell->envp->env_size)
		{
			return (0);
		}
		else
		{
			//g_err = 127;
			return (127);
		}

	}
	return (-1);
}
void ft_ctrl_c()
{
	rl_replace_line("", 0);
	printf("\n");
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void ft_signal()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
}


int main(int argc, char **argv, char **envp)
{
	char *path;
	(void)argc;
	(void)argv;
	char *cmd;
	int pid;
	int flag;
	int i;
	t_shell_s *minishell;

	i = 0;
	while (1)
	{
		ft_signal();
		flag = 0;
		cmd = readline("minishell🤓$ ");
		if (cmd == NULL)
		{
			exit (0);
		}
		minishell = parse(cmd, envp);
		if(!cmd)
			exit(EXIT_SUCCESS);
		if (strlen(cmd) > 0)
			add_history(cmd);
		if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
		{
			free(cmd);
			continue;
		}
		if(strcmp(cmd, "exit") == 0)
		{
			free(cmd);
			break;
		}
		path = ft_getenv(minishell, "PATH");
		if (path == NULL)
		{
			printf("Error: PATH environment variable not set\n");
			continue;
		}
		char **paths = ft_split(path, ':');
		pid = fork();
		i = 0;
		if (minishell != NULL)
		{	while (i < minishell->num_commands)
			{	
				cmd = minishell->command_block[i]->command;
				if (ft_strchr(minishell->command_block[i]->command, '/')== 0)
				{
					int x = 0;
					while (paths[x])
					{
						paths[x] = ft_strjoin(paths[x], "/");
						cmd = ft_strjoin(paths[x], minishell->command_block[i]->command);
						if (access(cmd, 0) == 0)
						{
							flag = 1;
							break ;
						} 
						x++;
					}
				}
				if(pid == 0)
				{
					execve(cmd, minishell->command_block[i]->args, minishell->envp->envp);
					perror("execve");
				}
				i++;
			}
		}
		waitpid(pid, &flag, 0);
		free(cmd);
		cmd = NULL;
	}

	exit(EXIT_SUCCESS);
}
