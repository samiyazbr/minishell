#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <wait.h>
#include "../libft/libft.h"
typedef struct t_env_s
{
    int env_index;
    int env_size;
    char **envp;
    char **key;
    char **value;
}   t_env_s;

typedef struct t_shell_s
{
    int num_commands; // number of all commands
    int num_pipes;  // number of all pipes
    int infile;  //file descriptor for redirect in file 
    int outfile;  // file descriptor for redirect out file
    char *cmd_line; // read the command line
    char **commands; // simple commands
    char *home;  //  a path for a home directory
    char **path;    // a path for the list of path direcotories separeted by ':'
    int pipe_num;     // number of pipe process (get it after split)
    struct t_env_s envp;
}   t_shell_s;

void ft_signal();
void ft_ctrl_c();

#endif