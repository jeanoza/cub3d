/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:31:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/21 14:59:24 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Maxime: I changed the close_game to make the exit in the function
//			and not in the free_game

int	close_game_win_ctrl(t_game *game)
{
	printf("Closed by win x button\n");
	free_game(game);
	exit(0);
	return (0);
}

void	move_player(int code, t_game *game, double x, double y)
{
	x = game->player->x;
	y = game->player->y;
	if (code == KEY_W)
	{
		game->player->x = game->player->x + (game->player->dir_x / 10);
		game->player->y = game->player->y + (game->player->dir_y / 10);
	}
	else if (code == KEY_S)
	{
		game->player->x = game->player->x - (game->player->dir_x / 10);
		game->player->y = game->player->y - (game->player->dir_y / 10);
	}
	else if (code == KEY_A)
	{
		game->player->x = game->player->x - (game->player->dir_y / 10);
		game->player->y = game->player->y + (game->player->dir_x / 10);
	}
	else if (code == KEY_D)
	{
		game->player->x = game->player->x + (game->player->dir_y / 10);
		game->player->y = game->player->y - (game->player->dir_x / 10);
	}
	if (game->map[(int)game->player->x][(int) game->player->y] != '0')
	{
		game->player->x = x;
		game->player->y = y;
	}
	// printf("poxX:%f poxY:%f dirX:%f dirY:%f\n", game->player->x, game->player->y, game->player->dir_x, game->player->dir_y);
}

void	change_dir(int code, t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	if (code == KEY_LEFT)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(RADIAN) - game->player->dir_y * sin(RADIAN);
		game->player->dir_y = old_dir_x * sin(RADIAN) + game->player->dir_y * cos(RADIAN);
		old_plane_x = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(RADIAN) - game->player->plane_y *sin(RADIAN) ;
		game->player->plane_y = old_plane_x * sin(RADIAN) + game->player->plane_y * cos(RADIAN);
	}
	if (code == KEY_RIGHT)
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-RADIAN) - game->player->dir_y * sin(-RADIAN);
		game->player->dir_y = old_dir_x * sin(-RADIAN) + game->player->dir_y * cos(-RADIAN);
		old_plane_x = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-RADIAN) - game->player->plane_y *sin(-RADIAN) ;
		game->player->plane_y = old_plane_x * sin(-RADIAN) + game->player->plane_y * cos(-RADIAN);
	}
}

int	input_handle(int code, t_game *game)
{
	double tmp[2];

	if (code == KEY_ESC)
	{
		free_game(game);
		exit(0);
	}
	move_player(code, game, tmp[0], tmp[1]);
	change_dir(code, game);
	//FIXME: calculate with function MATH
	raycast(game);
	return (0);
}
