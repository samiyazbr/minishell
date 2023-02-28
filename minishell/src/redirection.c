#include "../include/minishell.h"

void open_iofiles(t_files *redirec)
{
	int i;

	i = 0;
	// Open input and output files
	while (redirec->no_redirect > 0)
	{
		if (redirec->redirec_type[i] == '>')
		{
			if((redirec->infile_fd= open(redirec->infile_filename[i], O_RDONLY)) < 0)
			{
				printf("Error: Failed to open input file.\n");
				exit(1);
			}
			redirec->no_redirect++;
		}
		else if (redirec->redirec_type[i] == '<')
		{
			if ((redirec->outfile_fd= open(redirec->outfile_filename[i], O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
			{
				printf("Error: Failed to open outfile file.\n");
				exit(1);
			}
			redirec->no_redirect++;
		}
		i++;
	}
}

void ft_close_iofiles(t_files *redirec)
{
	int i;

	i = 0;
	while(redirec->infile_filename[i])
	{
		close((int)redirec->infile_fd);
		i++;
	}
	i = 0;

	while(redirec->outfile_filename[i])
	{
		close(redirec->outfile_fd);
		i++;
	}
}

int redirection(t_files *redirec)
{
    pid_t pid;
	t_execute *minishell;

	open_iofiles(redirec);
    if ((pid = fork()) < 0)
	{
        printf("Error: Failed to fork child process.\n");
        exit(1);
    }
	else if (pid == 0)
	{
		if (dup2(redirec->infile_fd, 0) < 0)
		{
        printf("Error: Failed to redirect input.\n");
        exit(1);
		}
        if (dup2(redirec->outfile_fd, 1) < 0)
		{
            printf("Error: Failed to redirect output.\n");
            exit(1);
        }
        execve(minihell->command, minishell->args, NULL);
    }
	else
	{
        if (waitpid(pid, NULL, 0) < 0) {
            printf("Error: Failed to wait for child process.\n");
            exit(1);
        }
    }

    // Close files
	ft_close_iofiles(redirec);

    return (0);
}
