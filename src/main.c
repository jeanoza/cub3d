/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/02 12:06:10 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (line)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
		{
			// printf("%c(%d) ", line[i], line[i]);
			++i;
		}
		// printf("\n");
		line = get_next_line(fd);
	}
	return (game);
}

int	render(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 840, 1024, "cub3d");
	// mlx_clear_window(game->mlx, game->win);
	return (EXIT_SUCCESS);
}


int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(game));
	if (parse(ac, av, game))
	{
		render(game);
		while(1);
	}
	return (0);
}