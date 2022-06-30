/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:20:51 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:45:34 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		++i;
	}
	return (dst);
}

/*
#include<stdio.h>
#include<string.h>
int	main(int ac, char **av)
{
	char	dst[100];
	char	dst_ft[100];

	(void)ac;

	printf("ft_memcpy:%s, (dst_ft):%s\n",
		(char *)ft_memcpy(dst_ft, av[1], atoi(av[2])), dst_ft);
	printf("memcpy:%s, (dst):%s\n",
		(char *)memcpy(dst, av[1], atoi(av[2])), dst);
	//NULL test
	// printf("ft_memcpy:%p, (dst_ft):%s\n",
		// (char *)ft_memcpy((void *)0, av[1], 3), dst_ft);
	// printf("memcpy:%p, (dst):%s\n",
		// (char *)memcpy((void *)0, av[1], 3), dst);
	return (0);
}
*/