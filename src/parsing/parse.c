/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/05 09:09:40 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_by_invalid_line(char *line, t_game *game)
{
	free(line);
	free_game(game);
	// while (1);
	exit(EXIT_FAILURE);
}

/*
 * Function:  validate_line
 * --------------------------------------------------------------------------
 * Test invalid characters in current line
 *
 * line: from get_next_line(fd)
 * game: t_game ptr to use 
 */
int	validate_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		//This is a example
		if (line[i] == 'F')
		// if (line[i] == 'Z')
			return (exit_by_invalid_line(line, game));
		++i;
	}
	return (TRUE);
}

//TODO: have parsing NO_path ... Color etc than map
static int	get_line_rec(t_game *game, int fd, int i, int j)
{
	char	*line;

	line = get_next_line(fd);
	// printf("line:%s(i:%d j:%d)\n", line, i, j);
	if (line)
	{
		validate_line(line, game);
		if (line[0] != '\n')
		{
			if (game->map == NULL)
				game->map = ft_calloc(2, P_SIZE);
			else
				game->map = ft_realloc(game->map,
						(i + 1) * P_SIZE, (i + 2) * P_SIZE);
			(game->map)[i++] = line;
		}
		return (get_line_rec(game, fd, i, j + 1));
	}
	return (0);
}

int	parse(char **av, t_game *game)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || get_line_rec(game, fd, 0, 0) == -42)
	{
		close(fd);
		printf("Error\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (TRUE);
}