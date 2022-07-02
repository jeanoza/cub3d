/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/03 00:23:16 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(void **_2d_array)
{
	int	i;

	if (!_2d_array)
		return ;
	i = 0;
	while (_2d_array && _2d_array[i])
	{
		free(_2d_array[i]);
		++i;
	}
	free(_2d_array);
}

int	get_line_num(char *path)
{
	int	fd;
	int	i;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (get_next_line(fd))
		++i;
	close(fd);
	return(i);
}

/*
 * Function:  parse
 * --------------------------------------------------------------------------
 * Verify line is validate or not by parse_error function.
 * returns:	NULL | [t_map *map1, t_map *map2...,] //TODO: modify return value explication
 */
t_game *parse(char **av, t_game *game)
{
	int	fd;
	int	i;
	int	length;

	length = get_line_num(av[1]);
	if (length)
	{
		fd = open(av[1], O_RDONLY);
		game->map = ft_calloc(length + 1, sizeof(char *));
		i = 0;
		while (i < length)
		{
			game->map[i] = get_next_line(fd);
			++i;
		}
		game->map[i] = NULL;
		close(fd);
		return (game);
	}
	return (NULL);
}

int	render(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1240, 720, "cub3d");
	//for test game->map data(char *)
	int	i = 0;
	while (game->map && game->map[i])
	{
		printf("%s\n(i:%d)", game->map[i], i);
		++i;
	}
	return (EXIT_SUCCESS);
}


int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;

	if (parse(av, &game))
	{
		render(&game);
		mlx_destroy_window(game.mlx, game.win);
		free_2d_array((void **) game.map);
	}
	return (0);
}