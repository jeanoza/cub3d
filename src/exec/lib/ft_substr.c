/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:18:33 by mabriel           #+#    #+#             */
/*   Updated: 2022/04/11 18:22:30 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	star;
	char	*dst;

	if (!s)
		return (NULL);
	i = 0;
	star = (size_t)start;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (star >= ft_strlen(s) || !s)
		len = 0;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = s[star + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
