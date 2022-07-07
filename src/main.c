/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/07 18:42:01 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_game *game)
{
	//FIXME: this is example : 2nd and 3rd parametre have to be changed by input(parsing)
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1240, 720, "cub3d");
}

int	close_game_win_ctrl(t_game *game)
{
	if (mlx_destroy_window(game->mlx, game->win))
	{
		printf("Error\nDestroy window failed\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	printf("Closed by win x button\n");
	exit(EXIT_SUCCESS);
}

// FIXME: version with parsing
int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		exit(EXIT_FAILURE);
	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		init(game);
		print_game(game);
		mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
		mlx_loop(game->mlx);
	}

	return (EXIT_SUCCESS);
}
