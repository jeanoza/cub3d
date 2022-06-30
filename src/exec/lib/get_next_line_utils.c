/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:54:38 by mabriel           #+#    #+#             */
/*   Updated: 2021/12/10 18:37:10 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strcat(char *s1, const char *s2)
{
	int	len;
	int	len2;
	int	i;

	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	while (i < len2)
	{
		s1[len + i] = s2[i];
		i++;
	}
	s1[len + i] = '\0';
	return (s1);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	int		len;

	len = 0;
	if (!s1)
	{
		s1 = (char *)malloc(1);
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(*str) * len + 1);
	if (!str)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	free(s1);
	str = ft_strcat(str, (char *)s2);
	return (str);
}

char	*clean_line(char *dirty_line)
{
	char	*s;
	int		i;
	int		j;

	if (!dirty_line)
		return (NULL);
	i = 0;
	while (dirty_line[i] && dirty_line[i] != '\n')
		i++;
	if (dirty_line[i] == '\n')
		i++;
	s = (char *)malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	j = -1;
	while (++j < i)
		s[j] = dirty_line[j];
	s[j] = '\0';
	if (s[0] == '\0')
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*left_line(char *dirty_line)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	if (!dirty_line)
		return (NULL);
	help_left_line(dirty_line, &i, &j);
	s = (char *)malloc(sizeof(char) * j - i + 1);
	if (!s)
		return (NULL);
	j = 0;
	while (dirty_line[i])
	{
		s[j] = dirty_line[i];
		j++;
		i++;
	}
	s[j] = '\0';
	free(dirty_line);
	return (s);
}
