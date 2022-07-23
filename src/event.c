/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:02:00 by kychoi            #+#    #+#             */
/*   Updated: 2022/07/23 15:55:01 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game_win_ctrl(t_game *game)
{
	printf("Closed by win x button\n");
	free_game(game);
	exit(0);
	return (0);
}

void	move_player(int code, t_game *game)
{
	if (code == KEY_W)
	{
		game->player->x = game->player->x + (game->player->dir_x / 5);
		game->player->y = game->player->y + (game->player->dir_y / 5);
	}
	else if (code == KEY_S)
	{
		game->player->x = game->player->x - (game->player->dir_x / 5);
		game->player->y = game->player->y - (game->player->dir_y / 5);
	}
	else if (code == KEY_A)
	{
		game->player->x = game->player->x - (game->player->dir_y / 5);
		game->player->y = game->player->y + (game->player->dir_x / 5);
	}
	else if (code == KEY_D)
	{
		game->player->x = game->player->x + (game->player->dir_y / 5);
		game->player->y = game->player->y - (game->player->dir_x / 5);
	}
}

void	change_dir(int code, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	radian;

	if (code == KEY_LEFT)
		radian = RADIAN;
	else
		radian = -RADIAN;
	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(radian)
		- game->player->dir_y * sin(radian);
	game->player->dir_y = old_dir_x * sin(radian)
		+ game->player->dir_y * cos(radian);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(radian)
		- game->player->plane_y * sin(radian);
	game->player->plane_y = old_plane_x * sin(radian)
		+ game->player->plane_y * cos(radian);
}

int	input_handle(int code, t_game *game)
{
	double	tmp[2];

	if (code == KEY_ESC)
	{
		free_game(game);
		exit(0);
	}
	tmp[0] = game->player->x;
	tmp[1] = game->player->y;
	if (code == KEY_LEFT || code == KEY_RIGHT)
		change_dir(code, game);
	move_player(code, game);
	if (game->map[(int) game->player->x][(int) game->player->y] != '0')
	{
		game->player->x = tmp[0];
		game->player->y = tmp[1];
	}
	raycast(game);
	return (0);
}
