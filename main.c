#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *cmd;
	int pid;
	char **av;

    while(1)
    {
        cmd = readline("$ ");
		av = ft_split(cmd, ' ');
		char *args[] = {0};
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
		cmd = ft_strjoin("/bin/",av[0]);
		pid = fork();
		if(pid == 0)
			execve(cmd, args, NULL);

        if(strcmp(cmd, "exit") == 0)
        {
            free(cmd);
            break;
        }

        //printf("%s\n", cmd);
		wait(NULL);
        free(cmd);

    }

    exit(EXIT_SUCCESS);
}