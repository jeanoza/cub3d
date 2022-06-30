/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:29:19 by kychoi            #+#    #+#             */
/*   Updated: 2022/03/18 12:53:17 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * len + 1);
	if (str)
	{
		i = 0;
		while (i < len)
		{
			str[i] = s1[i];
			++i;
		}
		str[i] = 0;
		return (str);
	}
	return (0);
}

char	*ft_strndup_free(char *s1, size_t len)
{
	char	*str;
	size_t	i;

	str = malloc(sizeof(char) * len + 1);
	if (str)
	{
		i = 0;
		while (i < len)
		{
			str[i] = s1[i];
			++i;
		}
		str[i] = 0;
		free(s1);
		return (str);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int ac, char **av)
{
	(void)ac;
	char	*str = strdup(av[1]);
	char	*str_ft = ft_strndup_free(av[1]);

	printf("strdup:		%s\n", str);
	printf("ft_strndup_free:	%s\n", str_ft);
	return (0);
}
*/