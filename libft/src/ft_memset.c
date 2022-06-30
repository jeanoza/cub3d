/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:53:45 by kychoi            #+#    #+#             */
/*   Updated: 2022/05/14 14:40:01 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, unsigned int len)
{
	unsigned char	*str;
	unsigned int	i;

	str = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char) c;
		++i;
	}
	return (b);
}
/*
#include<stdio.h>
int	main(int ac, char **av)
{
	(void)ac;
	int length;
	int	i;

	length = ft_strlen(av[1]);
	printf("before:%s\n", av[1]);
	ft_memset(av[1], 0, ft_atoi(av[2]));
	write(1, "after:", 6);
	i = 0;
	while (i < length)
	{
		write(1, &av[1][i], 1);
		++i;
	}
	return (0);
}
*/