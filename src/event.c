/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:31:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/21 10:10:07 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Maxime: I changed the close_game to make the exit in the function
//			and not in the free_game

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
	free_game(game);
	exit(0);
	return (0);
	// exit(EXIT_SUCCESS);
}

void	help_in_han(int code, t_game *game)
{
	if (code == KEY_ESC)
	{
		free_game(game);
		exit(0);
	}
	if (code == KEY_W)
		game->player->x -= 0.1;
	else if (code == KEY_S)
		game->player->x += 0.1;
	else if (code == KEY_A)
		game->player->y -= 0.1;
	else if (code == KEY_D)
		game->player->y += 0.1;
}

int	input_handle(int code, t_game *game)
{
	double	x;
	double	y;

	x = game->player->x;
	y = game->player->y;
	help_in_han(code, game);
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
