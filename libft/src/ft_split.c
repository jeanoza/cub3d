/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:50:30 by kychoi            #+#    #+#             */
/*   Updated: 2022/06/11 17:48:18 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counts_word_num(char const *s, char c)
{
	size_t	i;
	int		word_num;

	i = 0;
	word_num = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] && s[i] == c)
			++i;
		while (s[i] && s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
				++word_num;
			++i;
		}
	}
	return (word_num);
}

static char	**ft_free_all_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (NULL);
}

static char	*gets_str(char const *s, int len, char **tab)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		ft_free_all_tab(tab);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		idx_start;
	int		idx_end;
	int		idx_strs;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (counts_word_num(s, c) + 1));
	if (!strs)
		return (NULL);
	idx_strs = 0;
	idx_start = 0;
	idx_end = 0;
	while (s[idx_end] && idx_strs < counts_word_num(s, c))
	{
		while (s[idx_end] && s[idx_end] == c)
			++idx_end;
		idx_start = idx_end;
		while (s[idx_end] && s[idx_end] != c)
			++idx_end;
		strs[idx_strs] = gets_str(s + idx_start, idx_end - idx_start, strs);
		++idx_strs;
	}
	strs[idx_strs] = NULL;
	return (strs);
}
