#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_counter
{
	int	i;
	int	j;
	int	k;
	int	m;
	int	n;
	int	x;
	int	y;
	int	trigger;
	int	counter;
}t_counter;

typedef struct s_lexer
{
	char	**tokens;
	int		num_of_pipes;
	int		num_of_commands;
	int		num_of_dquotes;
	int		num_of_squotes;
	int		infile;
	int		outfile;
}t_lexer;

typedef struct s_env_s
{
    int env_index;
    int env_size;
    char **envp;
    char **key;
    char **value;
}t_env_s;

typedef struct s_shell_s
{
    int num_commands; // number of all commands
    int num_pipes;  // number of all pipes
    int infile;  //file descriptor for redirect in file 
    int outfile;  // file descriptor for redirect out file
    char *cmd_line; // read the command line
    char **commands; // simple commands
    char *home;  //  a path for a home directory (DONE)
    char **path;    // a path for the list of path direcotories separeted by ':' (DONE)
    int pipe_num;     // number of pipe process (get it after split)
    t_env_s envp;
	t_lexer	*lexer;
}   t_shell_s;

void ft_signal();
void ft_ctrl_c();

/*--------------------------------OBADA--------------------------------*/
/*-------------------------------PARSING-------------------------------*/
t_shell_s		*parse(char *str, char *envp[]);

/*--------------------------------UTSIL1-------------------------------*/
int				skip_spaces(char *str, int i);
char			*check_for_input(char *str);
char			*check_for_output(char *str);
int				ft_strlen_spaces(char *str, int i);
int				count_pipes(char *str);

/*--------------------------------UTSIL2-------------------------------*/
t_shell_s		*get_path(t_shell_s	*minishell, char *envp[]);
t_shell_s		*get_home(t_shell_s *minishell, char *envp[]);
t_shell_s		*get_commands(t_shell_s *minishell, char *str);

/*--------------------------------UTSIL3-------------------------------*/
t_shell_s		*lexer(t_shell_s *minishell, char *str);
int				number_of_dquotes(char *str);
void			print_struct(t_shell_s *args);

#endif