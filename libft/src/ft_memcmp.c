/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:12:51 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:45:32 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((unsigned char *)(s1 + i)) == *((unsigned char *)(s2 + i)))
	{
		if (i == n - 1)
			break ;
		++i;
	}
	return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}
/*
#include <stdio.h>
#include <string.h>
int	main(int ac, char **av)
{
	(void)ac;
	// printf("ft_memcmp	:%d\n", ft_memcmp(av[1], av[2], atoi(av[3])));
	// printf("memcmp		:%d\n", memcmp(av[1], av[2], atoi(av[3])));
	// printf("ft_memcmp	:%d\n", ft_memcmp("hello", "helloo", atoi(av[3])));
	// printf("memcmp		:%d\n", memcmp("hello", "helloo", atoi(av[3])));
	printf("ft_memcmp	:%d\n", ft_memcmp("hello", "helloo", 0));
	printf("memcmp		:%d\n", memcmp("hello", "helloo", 0));
	while (1)
	return (0);
}
*/