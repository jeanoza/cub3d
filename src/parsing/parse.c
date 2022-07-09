/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 17:53:55 by mabriel          ###   ########.fr       */
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

static int	if_forest(char *line_no_nl, t_game *game, int i)
{
	if (ft_strncmp(line_no_nl, "NO", 2) == 0 && forest_help(game, 1))
		game->no_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "SO", 2) == 0 && forest_help(game, 2))
		game->so_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "WE", 2) == 0 && forest_help(game, 3))
		game->we_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "EA", 2) == 0 && forest_help(game, 4))
		game->ea_path = line_no_nl;
	else if (line_no_nl[0] == 'F' && forest_help(game, 5))
		game->fcolor = line_no_nl;
	else if (line_no_nl[0] == 'C' && forest_help(game, 6))
		game->ccolor = line_no_nl;
	else if (game->count == 7 || game->err == 1)
		return (put_map(game, line_no_nl, i));
	else if (game->err == 0)
		error_parsing(ERR_LINE, line_no_nl, game);
	return (i);
}

static int	get_line_rec(t_game *game, char *line, int fd, int i)
{
	char	*line_no_nl;

	if (line == NULL)
		return 1;
	//validate_line(line, game);
	if (line[0] != '\n' || game->map)
	{
		line_no_nl = ft_strndup(line, ft_strlen(line) - 1);
		i = if_forest(line_no_nl, game, i);
	}
	game->line += 1;
	free(line);
	get_line_rec(game, get_next_line(fd), fd, i);
	return (0);
}

static int	check_extension(char *s)
{
	int	size;

	size = ft_strlen(s);
	if (size < 4)
		return (1);
	if (s[size - 1] == 'b' && s[size - 2] == 'u'
		&& s[size - 3] == 'c' && s[size - 4] == '.')
		return (0);
	return (1);
}

int	parse(char **av, t_game *game)
{
	int	fd;

	if (check_extension(av[1]))
		exit_error_file(game, 1);
	fd = open_file(av[1], game);
	init_parse(game);
	if (get_line_rec(game, get_next_line(fd), fd, 0))
	{
		free_game(game);
		printf("Empty file\n");
		return (FALSE);
	}
	close(fd);
	check_map(game);
	put_floor_ceil(game, game->ccolor);
	put_floor_ceil(game, game->fcolor);
	game->player = ft_calloc(1, sizeof(t_player));
	game->player->x = 10;
	game->player->y = 15;
	game->player->dir = EAST;

	

	if (game->err == 1)
	{
		free_game(game);
		return (FALSE);
	}
	return (TRUE);
}