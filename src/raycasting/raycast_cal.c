/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 06:54:32 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/22 02:09:24 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_step(t_game *game)
{
	if (game->ray->dir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->side_x = (game->player->x - game->ray->map_x)
			* game->ray->delta_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->side_x = (game->ray->map_x + 1.0 - game->player->x)
			* game->ray->delta_x;
	}
	if (game->ray->dir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->side_y = (game->player->y - game->ray->map_y)
			* game->ray->delta_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->side_y = (game->ray->map_y + 1.0 - game->player->y)
			* game->ray->delta_y;
	}
}

static void	calculate_line_height(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray->side_x < game->ray->side_y)
		{
			game->ray->side_x += game->ray->delta_x;
			game->ray->map_x += game->ray->step_x;
			game->ray->is_side = 0;
		}
		else
		{
			game->ray->side_y += game->ray->delta_y;
			game->ray->map_y += game->ray->step_y;
			game->ray->is_side = 1;
		}
		if (game->map[game->ray->map_x][game->ray->map_y] > '0')
			hit = 1;
	}
	if (game->ray->is_side == 0)
		game->ray->perp_wall_dist = (game->ray->side_x - game->ray->delta_x);
	else
		game->ray->perp_wall_dist = (game->ray->side_y - game->ray->delta_y);
	game->ray->line_height = (int)(SCREEN_HEIGHT / game->ray->perp_wall_dist);
}

static void	calculate_wall_x(t_game *game)
{
	game->ray->draw_start = -game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (game->ray->draw_end >= SCREEN_HEIGHT)
		game->ray->draw_end = SCREEN_HEIGHT - 1;
	if (game->ray->is_side == 0)
	{
		game->tex->idx = 0;
		if (game->ray->dir_x > 0)
			++game->tex->idx;
		game->ray->wall_x = game->player->y + game->ray->perp_wall_dist
			* game->ray->dir_y;
	}
	else
	{
		game->tex->idx = 2;
		if (game->ray->dir_y < 0)
			++game->tex->idx;
		game->ray->wall_x = game->player->x + game->ray->perp_wall_dist
			* game->ray->dir_x;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
}

void	update_buffer(t_game *game, int x)
{
	int	y;
	int	color;

	game->tex->x = (int)(game->ray->wall_x * game->tex->w);
	if ((game->ray->is_side == 0 && game->ray->dir_x > 0)
		|| (game->ray->is_side == 1 && game->ray->dir_y < 0))
		game->tex->x = game->tex->w - game->tex->x - 1;
	game->tex->step = 1.0 * game->tex->h / game->ray->line_height;
	game->tex->pos = (game->ray->draw_start
			- SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * game->tex->step;
	y = game->ray->draw_start;
	while (y < game->ray->draw_end)
	{
		game->tex->y = (int) game->tex->pos & (game->tex->h - 1);
		game->tex->pos += game->tex->step;
		color = game->textures[game->tex->idx][game->tex->h
			* game->tex->y + game->tex->x];
		if (game->ray->is_side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			game->tex->buffer[y][x] = color;
		++y;
	}
}

void	calculate(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, x);
		calculate_step(game);
		calculate_line_height(game);
		calculate_wall_x(game);
		update_buffer(game, x);
		++x;
	}
}
