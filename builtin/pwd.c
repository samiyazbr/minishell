/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:57:40 by szubair           #+#    #+#             */
/*   Updated: 2023/05/10 11:19:54 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_exec *step, t_shell *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		dir = ft_getenv(shell, "PWD");
	if (!dir)
		return ;
	printf("%s\n", dir);
	ft_free2(&dir);
	step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
