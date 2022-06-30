/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:51:18 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/31 09:16:44 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		if (i == n - 1)
			break ;
		++i;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int ac, char **av)
{
	(void)ac;
	printf("ft_strncmp:%d\n", ft_strncmp(av[1], av[2], atoi(av[3])));
	printf("strncmp:%d\n", strncmp(av[1], av[2], atoi(av[3])));
	printf("null test\n");
	printf("ft_strncmp:%d\n", ft_strncmp(NULL, "hello", atoi(av[3])));
	printf("strncmp:%d\n", strncmp(NULL, "hello", atoi(av[3])));
	return (0);
}
*/