/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:50:58 by numussan          #+#    #+#             */
/*   Updated: 2023/04/26 15:42:02 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strdup(const char *s1)
{
	const unsigned char	*pointer;
	char	*result;

	if (!s1)
		return (NULL);
	pointer = (const unsigned char *)s1;
	result = (char *)malloc(ft_strlen(s1) + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, pointer, ft_strlen(s1) + 1);
	return (result);
}
