/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:23:22 by mabriel           #+#    #+#             */
/*   Updated: 2022/04/11 18:24:39 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static unsigned int	ft_nbr_words(char const *s, char c)
{
	unsigned int	nbr_words;
	size_t			i;

	i = 0;
	nbr_words = 0;
	if (s && *s && s[i] == c)
		i++;
	else if (s && *s && s[i] != c)
	{
		if (s && s[i] != '\0')
			nbr_words++;
		i++;
	}
	while (s && s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			nbr_words++;
		i++;
	}
	return (nbr_words);
}

static void	*free_split(char **d)
{
	unsigned int	i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	j;
	char			**dst;

	i = 0;
	j = 0;
	dst = (char **)malloc(sizeof(char *) * (ft_nbr_words(s, c) + 1));
	if (!dst)
		return (NULL);
	while (j < ft_nbr_words(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		dst[j] = ft_substr(s, start, (size_t)(i - start));
		if (!dst[j])
			return (free_split(dst));
		j++;
	}
	dst[j] = NULL;
	return (dst);
}
