/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:45:05 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/23 15:55:41 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, int x)
{
	game->ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray->dir_x = game->player->dir_x + game->player->plane_x
		* game->ray->camera_x;
	game->ray->dir_y = game->player->dir_y + game->player->plane_y
		* game->ray->camera_x;
	game->ray->map_x = game->player->x;
	game->ray->map_y = game->player->y;
	game->ray->delta_x = fabs(1 / game->ray->dir_x);
	game->ray->delta_y = fabs(1 / game->ray->dir_y);
}

void	draw_texture(t_game *game, int x, int y)
{
	t_data	data;

	data.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data.img)
		mlx_error(game);
	data.data = (int *) mlx_get_data_addr(data.img,
			&data.bits_per_pixel, &data.line_length, &data.endian);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (game->tex->buffer[y][x] > 0)
				data.data[y * SCREEN_WIDTH + x] = game->tex->buffer[y][x];
			else if (y < SCREEN_HEIGHT / 2)
				data.data[y * SCREEN_WIDTH + x] = game->c_color;
			else if (y < SCREEN_HEIGHT - 1)
				data.data[y * SCREEN_WIDTH + x] = game->f_color;
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(game->mlx, game->win, data.img, 0, 0);
	mlx_destroy_image(game->mlx, data.img);
}

void	init_buffer(t_game *game)
{
	int	i;

	if (game->tex->buffer)
		free_2d_array((void **) game->tex->buffer);
	game->tex->buffer = ft_calloc(SCREEN_HEIGHT + 1, sizeof(int *));
	if (!game->tex->buffer)
		malloc_err(game, 0, 0, NULL);
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		game->tex->buffer[i] = ft_calloc(SCREEN_WIDTH + 1, sizeof(int));
		if (!game->tex->buffer[i])
			malloc_err(game, 0, 0, NULL);
		++i;
	}
}

int	raycast(t_game *game)
{
	int		tmp[2];

	init_buffer(game);
	game->ray = ft_calloc(1, sizeof(t_ray));
	if (!game->ray)
		malloc_err(game, 0, 0, NULL);
	calculate(game);
	free(game->ray);
	tmp[0] = 0;
	tmp[1] = 0;
	draw_texture(game, tmp[0], tmp[1]);
	return (0);
}
