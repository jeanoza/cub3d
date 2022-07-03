/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/03 18:45:09 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_game *game)
{
	//FIXME: this is example
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1240, 720, "cub3d");
}


int	main(int ac, char **av)
{
	t_game	*game;

	(void)ac;

	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		init(game);
		print_game(game);
		//FIXME: why there is leaks when execute this mlx_destroy_window in free_game?
		mlx_destroy_window(game->mlx, game->win);
		free_game(game);
		// while (1);
	}

	return (0);
}