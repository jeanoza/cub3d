/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/02 18:21:15 by kychoi           ###   ########.fr       */
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

/*
 * Function:  parse
 * --------------------------------------------------------------------------
 * Verify line is validate or not by parse_error function.
 * returns:	NULL | [t_map *map1, t_map *map2...,]
 */
// t_map	**parse(int ac, char **av, t_game *game)
t_game *parse(int ac, char **av, t_game *game)
{
	int	fd;
	char *line;
	int	i;


	if (ac != 2)
		return (NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	game->map = ft_calloc(2, 8);
	game->map[0] = line;
	i = 1;
	while (line)
	{
		printf("line[%p]%s\n", line, line);
		game->map = ft_realloc(game->map, (i + 1) * 8, (i + 2) * 8);
		game->map[i] = line;
		line = get_next_line(fd);
		++i;
	}
	return (game);
}

int	render(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1240, 720, "cub3d");
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
	t_game	*game;

	game = malloc(sizeof(game));
	printf("game[%p]\n", game);
	if (parse(ac, av, game))
	{
		render(game);
		// mlx_loop(game->mlx);
		free_2d_array((void **) game->map);
		mlx_destroy_window(game->mlx, game->win);
		free(game);
	}
	return (0);
}