/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:15:09 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 10:55:49 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_heredoc_fds(t_redir *inredir, int *heredoc_fds, int *fdtmp)
{
	dup2(*fdtmp, 0);
	if (inredir && inredir->type == HEREDOC)
	{
		ft_close(&heredoc_fds[1]);
		ft_close(fdtmp);
		dup2(heredoc_fds[0], 0);
	}
}

void	dup_pipes_and_redirs(t_exec *step, int *fds, int in_fd,
	int out_fd)
{
	if (step->pipe_next)
	{	
		ft_close(&fds[0]);
		dup2(fds[1], 1);
	}
	if (in_fd != -1)
		dup2(in_fd, 0);
	if (out_fd != -1)
		dup2(out_fd, 1);
}

void	child_builtin_cleanup(int *out_fd, int *in_fd, int *fdtmp,
	int exit_code)
{
	ft_close(out_fd);
	ft_close(in_fd);
	ft_close(fdtmp);
	exit(exit_code);
}

void	close_fds(const t_exec *step, int *fds, int *fdtmp)
{
	if (!step->pipe_next)
		ft_close(&fds[0]);
	ft_close(fdtmp);
}
