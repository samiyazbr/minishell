#include "../include/minishell.h"

t_shell_s	*parse(char *str, char *envp[])
{
	t_shell_s	*minishell;
	t_counter	count;
	char		*str1;
	char		*str2;

	minishell = malloc(sizeof(t_shell_s) * 1);
	count.i = 0;
	str1 = check_for_input(str);
	str2 = check_for_output(str);
	// printf("infile = %s\noutfile = %s\n", str1, str2);
	if (str1 != NULL)
	{
		minishell->infile = open(str2, F_OK | X_OK | O_RDONLY, 0777);
		free(str1);
	}
	if (str2 != NULL)
	{
		minishell->outfile = open(str1, F_OK | X_OK | O_RDWR | O_TRUNC, 0777);
		free(str2);
	}
	minishell->cmd_line = ft_strdup(str);
	minishell = get_path(minishell, envp);
	minishell = get_home(minishell, envp);
	minishell = get_commands(minishell, str);
	minishell = lexer(minishell, str);
	// count.i = skip_spaces(str, count.i);
	return (minishell);
}

// int	check_pipes_valid()
