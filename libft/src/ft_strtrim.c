/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:51:38 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:46:12 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		idx_start;
	int		idx_end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	idx_start = 0;
	while (s1[idx_start] && ft_contains(s1[idx_start], set))
		++idx_start;
	idx_end = ft_strlen(s1) - 1;
	while (idx_end > idx_start && s1[idx_end] && ft_contains(s1[idx_end], set))
		--idx_end;
	new_str = malloc(sizeof(char) * (idx_end - idx_start + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i <= (idx_end - idx_start))
	{
		new_str[i] = s1[idx_start + i];
		++i;
	}
	new_str[i] = '\0';
	return (new_str);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	char *s1 = "  \t \t \n   \n\n\n\t";
	printf("strlen:%zu\n", ft_strlen(s1));

	(void)ac;
	(void)av;
	printf("ft_strtrim:%s\n", ft_strtrim(s1, " \n\t"));
	return (0);
}
*/