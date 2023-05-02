/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szubair <szubair@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:09:47 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/01 12:53:26 by szubair          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	ft_free2(void *str)
{
	if (*(void **)str != NULL)
		free(*(void **)str);
	*(void **)str = NULL;
}

void	ft_free_array(char **array)
{
	size_t	i;
	size_t	lst_s;

	if (!array)
		return ;
	lst_s = 0;
	while (array[lst_s])
		lst_s++;
	i = 0;
	while (i < lst_s)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_token(void *content)
{
	t_token	*token;

	token = NULL;
	if (content != NULL)
	{
		token = (t_token *) content;
		if (token->substr != NULL)
			ft_free(token->substr);
		if (token->sub_tokens != NULL)
			ft_lstclear(&token->sub_tokens, free_token);
		free(token);
		token = NULL;
	}
}
