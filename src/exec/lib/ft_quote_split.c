/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:55:17 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/20 20:20:04 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static unsigned int	treat(const char *s, unsigned int i)
{
	unsigned int	j;

	j = i + 1;
	while (s && s[j] && s[j] != 39)
		j++;
	return (j);
}

static unsigned int	count_words(const char *s, char c)
{
	unsigned int	nbr_words;
	unsigned int	i;

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
		if (s[i] == 39)
		{
			i = treat(s, i);
			nbr_words++;
		}
		if (s[i] != c && s[i - 1] == c && s[i] != 39)
			nbr_words++;
		i++;
	}
	return (nbr_words);
}

static char	**make_the_split(char **dst, char const *s, char c)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		if (s[i] == 39)
			start++;
		if (s[i] == 39)
			i = treat(s, i);
		else
			while (s[i] != '\0' && s[i] != c && s[i] != 39)
				i++;
		dst[j] = ft_substr(s, start, (size_t)(i - start));
		if (!dst[j])
			return (ft_free_split(dst));
		j++;
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_quote_split(char const *s, char c)
{
	char	**dst;

	dst = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!dst)
		return (NULL);
	make_the_split(dst, s, c);
	return (dst);
}
