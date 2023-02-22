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

void	free_2d(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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

//#define PROMPT "minishell🤓$ "

//char *get_command() {
//    char *cmd = readline(PROMPT);
//    if (cmd && *cmd)
//        add_history(cmd);
//    return cmd;
//}

//char **parse_command(char *cmd) {
//    char **av = NULL;
//    if (cmd)
//        av = ft_split(cmd, ' ');
//    return av;
//}

//void execute_command(char **av, char **envp) {
//    if (!av || !av[0])
//        return;
//    char *cmd = av[0];
//    if (ft_strchr(cmd, '/') == 0) {
//        char *path = ft_getenv("PATH");
//        if (!path) {
//            printf("Error: PATH environment variable not set\n");
//            return;
//        }
//        char **paths = ft_split(path, ':');
//        for (int i = 0; paths[i]; i++) {
//            paths[i] = ft_strjoin(paths[i], "/");
//            cmd = ft_strjoin(paths[i], av[0]);
//            if (access(cmd, 0) == 0) {
//                break;
//            }
//        }
//    }
//    int pid = fork();
//    if (pid == 0) {
//        execve(cmd, av, envp);
//        perror("execve");
//        exit(1);
//    } else if (pid == -1) {
//        perror("fork");
//        exit(1);
//    } else {
//        int status;
//        waitpid(pid, &status, 0);
//    }
//}

//int main(int argc, char **argv, char **envp) {
//    (void)argv;
//	(void)argc;
	
//	ft_signal();
//    while (1) {
//        char *cmd = get_command();
//        if (!cmd)
//            continue;
//        if (strcmp(cmd, "exit") == 0) {
//            free(cmd);
//            break;
//        }
//        char **av = parse_command(cmd);
//        free(cmd);
//        execute_command(av, envp);
//        free(av);
//    }
//    return 0;
//}

int main(int argc, char **argv, char **envp)
{
	char *path;
	(void)argc;
	(void)argv;
	char *cmd;
	int pid;
	char **av;
	int flag;
	int i;

	i = 0;
	ft_signal();
	while (1)
	{
		flag = 0;
		cmd = readline("minishell🤓$ ");
		if (cmd == NULL)
		{
			free(cmd);
			printf("\n");
			exit (0);
		}
		av = ft_split(cmd, ' ');
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
		path = ft_getenv("PATH");
		if (path == NULL)
		{
			printf("Error: PATH environment variable not set\n");
			continue;
		}
		char **paths = ft_split(path, ':');
		cmd = av[0];
		if (ft_strchr(cmd, '/')== 0)
		{
			int x = 0;
			while (paths[x])
			{
				paths[x] = ft_strjoin(paths[x], "/");
				cmd = ft_strjoin(paths[x], av[0]);
				if (access(cmd, 0) == 0)
				{
					flag = 1;
					break ;
				} 
				x++;
			}
		}
		pid = fork();
		if(pid == 0)
			execve(cmd, av, envp);
		i++;
		waitpid(pid, &flag, 0);
		free(cmd);
		cmd = NULL;
	}

	exit(EXIT_SUCCESS);
}
