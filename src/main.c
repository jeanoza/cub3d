/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/04 09:02:28 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_game *game)
{
	//FIXME: this is example
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
	free_game(game);
	printf("Closed by win x button\n");
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void)ac;

	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		init(game);
		mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
		mlx_loop(game->mlx);
	}

	return (0);
}