/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:10:24 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:45:35 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len > 0)
		{
			--len;
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			++i;
		}
	}
	return (dst);
}

/*
printf("\n\n\tdst[%p]:	%s\n\tsrc[%p]:	%s\n\n",
	dst, (char *)dst, src, (char *)src);
#include <string.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	char	dst[10] = "fffffffff";
	char	dst_ft[10] = "fffffffff";
	(void)ac;

	char 	*ptr = memmove(dst, av[1], 5);
	char 	*ptr_ft = ft_memmove(dst_ft, av[1], 5);

	printf("first:\n");
	printf("memmove[%p]	:	%s\n", ptr, ptr);
	printf("ft_memmove[%p]	:	%s\n", ptr_ft, ptr_ft);

	ptr = memmove(dst, dst + 2, 2);
	ptr_ft = ft_memmove(dst_ft, dst_ft + 2, 2);

	printf("second:\n");
	printf("memmove[%p]	:	%s\n", ptr, ptr);
	printf("ft_memmove[%p]	:	%s\n", ptr_ft, ptr_ft);
	return (0);
}
*/