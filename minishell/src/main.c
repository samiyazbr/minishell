/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:51:24 by codespace         #+#    #+#             */
/*   Updated: 2023/03/07 11:52:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//int	is_builtin(t_shell_s *minishell, int i,char **env)
//{
//	if (ft_strncmp(minishell->commands[i], "echo", 4) == 0)
//		return (ft_echo(minishell->flags[i]));
//	else if (ft_strncmp(minishell->commands[i], "env", 3) == 0)
//		return (ft_env(env, minishell->flags[i]));
//	else if(ft_strncmp(minishell->commands[i], "cd", 2) == 0)
//		return(ft_cd(minishell->flags[i], minishell->num_commands));
//	else if (ft_strcmp(minishell->commands[i], "pwd", 3) == 0)
//		return (ft_pwd(minishell->flags[i]));
//	else if (ft_strncmp(minishell->commands[i], "unset", 5) == 0)
//		return(ft_unset(minishell->flags[i][1]));
//	//else if (ft_strncmp(minishell->commands[i], "export", 5) == 0)
//	return (-1);
//}
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
