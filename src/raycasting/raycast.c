/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:05 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/18 19:24:23 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step(t_game *game)
{
	if(game->ray->dir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->side_x = (game->player->x - game->ray->map_x) * game->ray->delta_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->side_x = (game->ray->map_x + 1.0 - game->player->x) * game->ray->delta_x;
	}
	if(game->ray->dir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->side_y = (game->player->y - game->ray->map_y) * game->ray->delta_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->side_y = (game->ray->map_y + 1.0 - game->player->y) * game->ray->delta_y;
	}


}

void	init_ray(t_game *game, int x)
{
	game->ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
	game->ray->dir_x = game->player->dir_x + game->player->plane_x * game->ray->camera_x;
	game->ray->dir_y = game->player->dir_y + game->player->plane_y * game->ray->camera_x;
	game->ray->map_x = game->player->x;
	game->ray->map_y = game->player->y;
	game->ray->delta_x = fabs(1 / game->ray->dir_x);
	game->ray->delta_y = fabs(1 / game->ray->dir_y);
}

void	calculate_line_height(t_game *game)
{
	int hit;

	hit = 0;
	while(hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(game->ray->side_x < game->ray->side_y)
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
		//Check if game->ray has hit a wall
		if(game->map[game->ray->map_x][game->ray->map_y] > '0')
			hit = 1;
	}
	if(game->ray->is_side == 0)
		game->ray->perp_wall_dist = (game->ray->side_x - game->ray->delta_x);
	else
		game->ray->perp_wall_dist = (game->ray->side_y - game->ray->delta_y);

	game->ray->line_height = (int)(SCREEN_HEIGHT / game->ray->perp_wall_dist);
}

void	calculate_wall_x(t_game *game)
{
	game->ray->draw_start = -game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if(game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if(game->ray->draw_end >= SCREEN_HEIGHT)
		game->ray->draw_end = SCREEN_HEIGHT - 1;

	if (game->ray->is_side == 0)
	{
		game->tex->idx = 0;
		if (game->ray->dir_x > 0)
			++game->tex->idx;
		game->ray->wall_x = game->player->y + game->ray->perp_wall_dist * game->ray->dir_y;
	}
	else
	{
		game->tex->idx = 2;
		if (game->ray->dir_y < 0)
			++game->tex->idx;
		game->ray->wall_x = game->player->x + game->ray->perp_wall_dist * game->ray->dir_x;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
}


void	update_buffer(t_game *game, int _x)
{
	int	_y;
	int	color;

	game->tex->x = (int) (game->ray->wall_x * game->tex->w);
	if ((game->ray->is_side == 0 && game->ray->dir_x > 0)
		||(game->ray->is_side == 1 && game->ray->dir_y < 0))
		game->tex->x = game->tex->w - game->tex->x - 1;
	game->tex->step = 1.0 * game->tex->h / game->ray->line_height;
	game->tex->pos = (game->ray->draw_start - SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * game->tex->step;
	_y = game->ray->draw_start;
	while (_y < game->ray->draw_end)
	{
		game->tex->y = (int) game->tex->pos & (game->tex->h - 1);
		game->tex->pos += game->tex->step;
		color = game->textures[game->tex->idx][game->tex->h * game->tex->y + game->tex->x];
		if (game->ray->is_side == 1)
			color = (color >> 1) & 8355711;
		game->tex->buffer[_y][_x] = color;
		++_y;
	}
}

void	draw_texture(t_game *game)
{
	t_data	data;
	int		x;
	int		y;

	data.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.data = (int *) mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			data.data[y * SCREEN_WIDTH + x] = game->tex->buffer[y][x];
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(game->mlx, game->win, data.img, 0, 0);

	//FIXME:need or not?
	mlx_destroy_image(game->mlx, data.img);
}

void	init_buffer(t_game *game)
{
	int	i;

	if (game->tex->buffer)
		free_2d_array((void **) game->tex->buffer);
	game->tex->buffer = calloc(1, sizeof(int *) * SCREEN_HEIGHT);
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		game->tex->buffer[i] = calloc(1, sizeof(int) * SCREEN_WIDTH);
		++i;
	}
}

int raycast (t_game *game)
{
	int		x;

	x = 0;
	game->ray = calloc(1, sizeof(t_ray));
	if (!game->ray)
	{
		//FIXME:put freeall
		exit(-42);
	}
	printf("Here\n");
	init_buffer(game);
	while (x < SCREEN_WIDTH)
	{
		init_ray(game, x);
		calculate_step(game);
		calculate_line_height(game);
		calculate_wall_x(game);
		update_buffer(game, x);
		++x;
	}
	draw_texture(game);
	free(game->ray);
	return (0);
}
