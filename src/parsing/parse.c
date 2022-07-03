/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/03 18:41:44 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Function:  validate_line
 * --------------------------------------------------------------------------
 * Test invalid characters in current line
 *
 * line: from get_next_line(fd)
 * returns: 1 if valid line, else 0
 */
int	validate_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		//This is a example
		if (line[i] == 'Z')
		// if (line[i] == 'F')
			return (0);
		++i;
	}
	return (1);
}

static int	get_line_rec(char ***map, char *line, int fd, int i)
{
	if (line)
	{
		if (!validate_line(line))
		{
			free(line);
			return (-42);
		}
		if (*map == NULL)
			*map = ft_calloc(2, sizeof(char *));
		else
			*map = ft_realloc(*map, (i + 1) * sizeof(char *), (i + 2) * sizeof(char *));
		(*map)[i] = line;
		return (get_line_rec(map, get_next_line(fd), fd, i + 1));
	}
	return (0);
}

int parse(char **av, t_game *game)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (0);
	if (get_line_rec(&game->map, get_next_line(fd), fd, 0) == -42)
	{
		close(fd);
		printf("Error\n");
		// print_game(game);
		free_game(game);
		exit(42);
	}
	close(fd);
	return (1);
}