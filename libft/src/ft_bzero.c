/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:26:14 by kychoi            #+#    #+#             */
/*   Updated: 2022/05/22 14:37:19 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

void	ft_bzero(void *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		++i;
	}
}
/*
#include <stdio.h>
int main(int ac, char **av)
{
	int length;
	int	i;

	length = ft_strlen(av[1]);
	printf("before:%s\n", av[1]);
	ft_bzero(av[1], ft_atoi(av[2]));
	write(1, "after:", 7);
	i = 0;
	while (i < length)
	{
		write(1, &av[1][i], 1);
		++i;
	}
	return (0);
}
*/