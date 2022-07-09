/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/10 00:47:36 by mabriel          ###   ########.fr       */
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
		close(fd);
		printf("Error\nEmpty file\n");
		return (FALSE);
	}
	close(fd);
	check_file_and_color(game);
	check_map(game);
	if (game->err == 1)
	{
		free_game(game);
		return (FALSE);
	}
	return (TRUE);
}