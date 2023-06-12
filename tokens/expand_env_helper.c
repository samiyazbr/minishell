/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:50:46 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/06/02 13:47:48 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*numeric_free_and_return(char *str, char *nums, char *before)
{
	free(str);
	free(nums);
	free(before);
	str = ft_strdup(" ");
	return (str);
}

char	*numeric_helper(char *str, size_t i, t_shell *s)
{
	char		*nums;
	char		*before;
	size_t		y;

	before = ft_substr(str, 0, i - 1);
	nums = ft_substr(str, i + 1, ft_strlen(str));
	if (nums[0] == '\0')
		return (numeric_free_and_return(str, nums, before));
	nums = join_and_free(before, nums, 3);
	y = 0;
	while (ft_isalnum(nums[y]) || nums[y] == '_')
		y++;
	s->end = y - 1;
	s->flag = 1;
	ft_free(str);
	return (nums);
}
