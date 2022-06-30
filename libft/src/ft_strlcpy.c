/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:16:41 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:46:01 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(src);
	if (dstsize == 0)
		return (dst_len);
	i = 0;
	while (*(src + i))
	{
		if (i == dstsize - 1)
			break ;
		*(dst + i) = *(src + i);
		++i;
	}
	*(dst + i) = 0;
	return (dst_len);
}
/*
#include <stdio.h>
#include <string.h>
int main(int ac, char **av)
{
	int		result_ft;
	int		result;
	char	dst_ft[100];
	char	dst[100];
	
	(void)ac;
	(void)dst;
	(void)result;
	result =  strlcpy(dst, av[1], (size_t) ft_atoi(av[2]));
	result_ft = ft_strlcpy(dst_ft, av[1], (size_t) ft_atoi(av[2]));
	printf("av[1]:%s av[2]:%s\n", av[1], av[2]);
	printf("strlcpy		:[%p]%s(%d)\n", dst, dst, result);
	printf("ft_strlcpy	:[%p]%s(%d)\n", dst_ft, dst_ft, result_ft);
	return (0);
}
*/