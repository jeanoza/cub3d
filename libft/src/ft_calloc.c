/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:48:14 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 14:38:44 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	size_t			i;
	size_t			len;

	len = count * size;
	result = malloc(len);
	if (result)
	{
		i = 0;
		while (i < len)
		{
			result[i] = 0;
			++i;
		}
		return ((void *) result);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int ac, char **av)
{
	(void)ac;
	int		len = ft_atoi(av[2]);

	char	*ptr = calloc(len, sizeof(char));
	char	*ptr_ft = ft_calloc(len, sizeof(char));

	strncpy(ptr, av[1], len);
	strncpy(ptr_ft, av[1], len);

	printf("ptr:		%s(len:%lu)\n", ptr, ft_strlen(ptr));
	printf("ptr_ft:		%s(len:%lu)\n", ptr_ft, ft_strlen(ptr_ft));
	return (0);
}
*/