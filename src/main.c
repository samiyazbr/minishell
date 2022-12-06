#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    char *cmd;
	int pid;
	char **av;
	int flag;

    while(1)
    {
		flag = 0;
        cmd = readline("minishell🤯$ ");
		av = ft_split(cmd, ' ');
        if(!cmd)
        {
            exit(EXIT_SUCCESS);
        }
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
		cmd = ft_strjoin("/bin/", av[0]);
		if (access(cmd, 0) == 0)
		{
			flag = 1;
		}
		if(flag)
		{
		pid = fork();
			if(pid == 0)
				execve(cmd, av, envp);
		}
		waitpid(pid, &flag, 0);
        //printf("%s\n", cmd);
        free(cmd);
		cmd = NULL;

    }

    exit(EXIT_SUCCESS);
}