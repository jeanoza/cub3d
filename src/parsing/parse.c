/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/07 17:25:41 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_by_invalid_line(char *line, t_game *game)
{
	free(line);
	free_game(game);
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
		// if (line[i] == 'F')
		if (line[i] == 'Z')
			return (exit_by_invalid_line(line, game));
		++i;
	}
	return (TRUE);
}

static int put_map(t_game *game, char *line, int idx)
{
	if (game->map == NULL)
		game->map = ft_calloc(2, P_SIZE);
	else
		game->map = ft_realloc(game->map,
				(idx + 1) * P_SIZE, (idx + 2) * P_SIZE);
	(game->map)[idx] = line;
	return (idx + 1);
}
static void	get_line_rec(t_game *game, char *line, int fd, int i)
{
	char	*line_no_nl;

	if (line == NULL)
		return ;
	validate_line(line, game);
	if (line[0] != '\n')
	{
		line_no_nl = ft_strndup(line, ft_strlen(line) - 1);
		if (ft_strncmp(line_no_nl, "NO", 2) == 0)
			game->no_path = line_no_nl;
		else if (ft_strncmp(line_no_nl, "SO", 2) == 0)
			game->so_path = line_no_nl;
		else if (ft_strncmp(line_no_nl, "WE", 2) == 0)
			game->we_path = line_no_nl;
		else if (ft_strncmp(line_no_nl, "EA", 2) == 0)
			game->ea_path = line_no_nl;
		else if (line_no_nl[0] == 'F')
			game->f_color = line_no_nl;
		else if (line_no_nl[0] == 'C')
			game->c_color = line_no_nl;
		else
			i = put_map(game, line_no_nl, i);
	}
	free(line);
	get_line_rec(game, get_next_line(fd), fd, i);
}

int	parse(char **av, t_game *game)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (FALSE);
	get_line_rec(game, get_next_line(fd), fd, 0);
	close(fd);
	return (TRUE);
}