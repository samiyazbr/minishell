// gcc minishell.c -lreadline

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
#include <unistd.h>	/* needed to define getpid() */
#include <wait.h>

int main(int ac, char** av, char **envp)
{
  char* buf;
  (void)ac;
  (void)av;
  int pid;
//  char s[100];

//	printf("%s\n", getcwd(s, 100));
//	chdir("..");
//	printf("%s\n", getcwd(s, 100));
  while (1)
  {
	buf = readline("minishell> ");
	if (!buf)
		exit(EXIT_FAILURE); 
    if (strlen(buf) > 0)
      add_history(buf);
	char *args[] = {"-la", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	//printf("About to run /bin/ls\n");
	//pid = fork();
	//if(pid == 0)
		//execve(buf, args, NULL);
		if (access(buf, 0) == 0)
		{
			printf("valid\n");
		}
		
	//wait(NULL);
	//printf("\n");
  }

  return 0;
}
