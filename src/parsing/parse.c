/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/21 17:15:40 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_parse(t_game *game)
{
	game->count = 1;
	game->line = 1;
	game->err = 0;
}

static int	if_forest(char *line_no_nl, t_game *game, int i)
{
	if (ft_strncmp(line_no_nl, "NO ", 3) == 0 && forest_help(game, 1))
		game->no_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "SO ", 3) == 0 && forest_help(game, 2))
		game->so_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "WE ", 3) == 0 && forest_help(game, 3))
		game->we_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "EA ", 3) == 0 && forest_help(game, 4))
		game->ea_path = line_no_nl;
	else if (ft_strncmp(line_no_nl, "F ", 2) == 0 && forest_help(game, 5))
		game->fcolor = line_no_nl;
	else if (ft_strncmp(line_no_nl, "C ", 2) == 0 && forest_help(game, 6))
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
		return (1);
	if (line[0] != '\n' || game->map)
	{
		if (ft_strchr(line, '\n'))
			line_no_nl = ft_strndup(line, ft_strlen(line) - 1);
		else
			line_no_nl = ft_strndup(line, ft_strlen(line));
		i = if_forest(line_no_nl, game, i);
	}
	game->line += 1;
	free(line);
	get_line_rec(game, get_next_line(fd), fd, i);
	return (0);
}

int	check_extension(char *s, char *ex)
{
	int	size;
	int	sizex;

	size = ft_strlen(s);
	sizex = ft_strlen(ex);
	if (size < 4)
		return (1);
	if (!ft_strncmp(s + size - sizex, ex, sizex + 1))
		return (0);
	return (1);
}

int	parse(char **av, t_game *game)
{
	int	fd;

	if (check_extension(av[1], ".cub"))
		exit_error_file(game, 1);
	fd = open_file(av[1], game);
	init_parse(game);
	if (get_line_rec(game, get_next_line(fd), fd, 0))
	{
		free_game(game);
		close(fd);
		ft_putstr_fd("Error\nEmpty file\n", 2);
		return (FALSE);
	}
	close(fd);
	if (game->err == 1)
	{
		free_game(game);
		return (FALSE);
	}
	check_file_and_color(game);
	check_map(game);
	return (TRUE);
}
