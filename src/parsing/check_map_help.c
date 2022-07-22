/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:38:51 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/22 20:41:41 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	help_set_angle(t_game *game, char angle)
{
	if (angle == 'W')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	if (angle == 'S')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
}

void	set_player_angle(t_game *game, char angle)
{
	if (angle == 'N')
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	if (angle == 'E')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	help_set_angle(game, angle);
}
