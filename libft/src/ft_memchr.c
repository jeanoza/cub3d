/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:12:39 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:45:31 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((unsigned char *)(s + i)) != (unsigned char) c)
	{
		++i;
		if (i == n)
			return (0);
	}
	return ((void *)(s + i));
}
/*
#include <string.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	int		c = av[2][0];
	size_t	n = (size_t) ft_atoi(av[3]);
	void	*result = memchr((void *) av[1], c, n);
	void	*ft_result = ft_memchr((void *) av[1], c, n);
	(void)ac;

	printf("ft_memchr	[%p]:%s\n", ft_result, (char *)ft_result);
	printf("memchr		[%p]:%s\n", result, (char *)result);
	return (0);
}
*/