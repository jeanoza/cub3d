/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:20:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 15:19:17 by kyubongchoi      ###   ########.fr       */
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

static void	get_line_rec(t_game *game, char *line, int fd, int i)
{
	char	*line_no_nl;

	if (line == NULL)
		return ;
	validate_line(line, game);
	if (line[0] != '\n')
	{
		line_no_nl = ft_strndup(line, ft_strlen(line) - 1);
		if (ft_strncmp(line_no_nl, "NO", 2) == 0
			|| ft_strncmp(line_no_nl, "SO", 2) == 0
			|| ft_strncmp(line_no_nl, "WE", 2) == 0
			|| ft_strncmp(line_no_nl, "EA", 2) == 0)
			put_texture(game, line_no_nl);
		else if (line_no_nl[0] == 'F' || line_no_nl[0] == 'C')
			put_floor_ceil(game, line_no_nl);
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