/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 22:56:23 by mabriel           #+#    #+#             */
/*   Updated: 2022/02/15 21:16:54 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static int	parser(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	help_left_line(char *str, int *i, int *j)
{
	int	a;
	int	b;

	a = 0;
	while (str[a] && str[a] != '\n')
		a++;
	if (str[a] == '\n')
		a++;
	b = a;
	while (str[b])
		b++;
	*i = a;
	*j = b;
}

static char	*read_fd(int fd, char *dirty_line)
{
	char	*buffer;
	int		ret;

	ret = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ret && !parser(dirty_line))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret == 0)
			break ;
		if (ret < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[ret] = '\0';
		dirty_line = ft_strjoin_free(dirty_line, buffer);
	}
	free(buffer);
	return (dirty_line);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left = read_fd(fd, left);
	if (!left)
		return (NULL);
	if (*left == '\0')
	{
		free (left);
		return (NULL);
	}
	line = clean_line(left);
	if (!line)
	{
		if (left)
			free(left);
		return (NULL);
	}
	left = left_line(left);
	return (line);
}
