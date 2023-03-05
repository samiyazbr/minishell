#include "../include/minishell.h"

void open_iofiles(t_shell_s *minishell)
{
	int i;

	i = 0;
	// Open input and output files
	while (minishell->files->num_of_redirections > 0)
	{
		if (minishell->files->redirect_type[i] == '>')
		{
			if((minishell->files->infile_fd= open(minishell->files->infile_name[i], O_RDONLY)) < 0)
			{
				printf("Error: Failed to open input file.\n");
				exit(1);
			}
			minishell->files->num_of_redirections++;
		}
		else if (minishell->files->redirect_type[i] == '<')
		{
			if ((minishell->files->outfile_fd= open(minishell->files->outfile_name[i], O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
			{
				printf("Error: Failed to open outfile file.\n");
				exit(1);
			}
			minishell->files->num_of_redirections++;
		}
		else if (minishell->files->redirect_type[i] == 'a')
		{
			if ((minishell->files->append_fd = open(minishell->files->append_name[i], O_WRONLY | O_APPEND)) < 0)
			{
				printf("Error: Failed to open outfile in append mode.\n");
				exit(1);
			}
		}
		i++;
	}
}

void ft_close_iofiles(t_files *redirec)
{
	int i;

	i = 0;
	while(redirec->infile_name[i])
	{
		close((int)redirec->infile_fd);
		i++;
	}
	i = 0;

	while(redirec->outfile_name[i])
	{
		close(redirec->outfile_fd);
		i++;
	}
}

int redirection(t_shell_s	*minishell)
{
    pid_t pid;
	int i;

	i = 0;
	open_iofiles(minishell);
    if ((pid = fork()) < 0)
	{
        printf("Error: Failed to fork child process.\n");
        exit(1);
    }
	else if (pid == 0)
	{
		if (dup2(minishell->files->infile_fd, 0) < 0)
		{
        printf("Error: Failed to redirect input.\n");
        exit(1);
		}
        if (dup2(minishell->files->outfile_fd, 1) < 0)
		{
            printf("Error: Failed to redirect output.\n");
            exit(1);
        }
		while (minishell->num_pipes + 1 <= i)
		{
        	execve(minishell->command_block[i]->command, minishell->command_block[i]->args, NULL);
			i++;
		}
    }
	else
	{
        if (waitpid(pid, NULL, 0) < 0) {
            printf("Error: Failed to wait for child process.\n");
            exit(1);
        }
    }

    // Close files
	ft_close_iofiles(minishell->files);

    return (0);
}
