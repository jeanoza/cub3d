/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 01:37:06 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		game->f_color = line_no_nl;
	else if (line_no_nl[0] == 'C' && forest_help(game, 6))
		game->c_color = line_no_nl;
	else if (game->count == 7 || game->err == 1)
		return (put_map(game, line_no_nl, i));
	else if (game->err == 0)
		error_parsing(ERR_LINE, line_no_nl, game);
	return (i);
}

static void	get_line_rec(t_game *game, char *line, int fd, int i)
{
	char	*line_no_nl;

	if (line == NULL)
		return ;
	//validate_line(line, game);
	if (line[0] != '\n' || game->map)
	{
		line_no_nl = ft_strndup(line, ft_strlen(line) - 1);
		i = if_forest(line_no_nl, game, i);
	}
	game->line += 1;
	free(line);
	get_line_rec(game, get_next_line(fd), fd, i);
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
	get_line_rec(game, get_next_line(fd), fd, 0);
	close(fd);
	check_map(game);
	if (game->err == 1)
	{
		free_game(game);
		return (FALSE);
	}
	return (TRUE);
}