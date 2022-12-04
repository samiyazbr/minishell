#include "../include/minishell.h"


static void	ft_free_all_memmory(size_t number_of_words, char **result)
{
	while (number_of_words--)
		free(result[number_of_words - 1]);
	free(result);
}

static char	*ft_pull_the_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_counting_words(const char *s, char c)
{
	int	num;

	num = 0;
	while (*s)
	{
		if (*s && *s == c)
			s++;
		else
		{
			num++;
			while (*s && *s != c)
				s++;
		}
	}
	return (num);
}

char	**ft_split(const char *s, char c)
{
	int		number_of_words;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	number_of_words = ft_counting_words(s, c);
	result = (char **)malloc(sizeof(char *) * (number_of_words + 1));
	if (!result)
		return (NULL);
	while (number_of_words--)
	{
		while (*s && *s == c)
			s++;
		result[i] = ft_pull_the_word(s, c);
		if (result[i] == NULL)
			ft_free_all_memmory(number_of_words, result);
		while (*s && *s != c)
			s++;
		i++;
	}
	result[i] = NULL;
	return (result);
}


char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	result = (char *)malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

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