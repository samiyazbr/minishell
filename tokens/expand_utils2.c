/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:51:06 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/10 13:55:51 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_which_quotes2(t_shell *shell, char *str, size_t i)
{
	if (str[i] == '\'' && !shell->doub)
		shell->sin = true;
	else if (str[i] == '\"' && !shell->sin)
		shell->doub = true;
}
