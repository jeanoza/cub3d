/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:51:23 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 12:17:55 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) < 1)
		return ((char *) haystack);
	i = 0;
	while (i < len && haystack[i])
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j))
		{
			if (i + j == len || *(needle + j) == 0)
				break ;
			++j;
		}
		if (*(needle + j) == 0)
			break ;
		++i;
	}
	if (j == ft_strlen(needle))
		return ((char *) haystack + i);
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	size_t	len = atoi(av[3]);
	char	*ft_res = ft_strnstr(av[1], av[2], len);
	char	*res = strnstr(av[1], av[2], len);
	printf("ft_strnstr:	%s[%p]\n",ft_res, ft_res);
	printf("strnstr:	%s[%p]\n", res, res);
	return (0);
}
*/