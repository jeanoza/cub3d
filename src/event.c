/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:31:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/19 18:52:34 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game_win_ctrl(t_game *game)
{
	// if (mlx_destroy_window(game->mlx, game->win))
	// {
	// 	printf("Error\nDestroy window failed\n");
	// 	free_game(game);
	// 	exit(EXIT_FAILURE);
	// }
	// // mlx_destroy_display(game->mlx);
	// free(game->mlx);
	printf("Closed by win x button\n");
	return free_game(game);
	// exit(EXIT_SUCCESS);
}

int	input_handle(int code, t_game *game)
{
	double x;
	double y;

	x = game->player->x;
	y = game->player->y;

	if (code == KEY_ESC)
		free_game(game);
	if (code == KEY_W)
		game->player->x -= 0.1;
	else if (code == KEY_S)
		game->player->x += 0.1;
	else if (code == KEY_A)
		game->player->y -= 0.1;
	else if (code == KEY_D)
		game->player->y += 0.1;
	if (game->map[(int)game->player->x][(int) game->player->y] != '0')
	{
		game->player->x = x;
		game->player->y = y;
	}
	//FIXME: calculate with function MATH
	if (code == KEY_LEFT)
		game->player->dir_y -= 0.1;
	if (code == KEY_RIGHT)
		game->player->dir_y += 0.1;
	raycast(game);
	return (0);
}