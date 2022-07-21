/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:27:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/21 17:58:58 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_error(t_game *game)
{
	ft_putstr_fd("Error\n\
[42]    424242 segmentation fault (core dumped)  ./notcub3d 42.cub\n\
just kidding ahah mlx isnt happy (with env -i)\n", 2);
	free_game(game);
	exit(1);
}

static void	help_xpm_to_img(t_game *game, char *path, t_data *tmp, int **buffer)
{
	tmp->img = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex->w, &game->tex->h);
	if (!tmp->img)
		mlx_error(game);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel,
			&tmp->line_length, &tmp->endian);
	*buffer = (int *)ft_calloc(1, sizeof(int) * game->tex->w * game->tex->h);
	if (!*buffer)
	{
		mlx_destroy_image(game->mlx, tmp->img);
		malloc_err(game, 0, 0, NULL);
	}
}

int	*xpm_to_img(t_game *game, char *path, t_data *tmp)
{
	int		*buffer;
	int		x;
	int		y;

	help_xpm_to_img(game, path, tmp, &buffer);
	y = 0;
	while (y < game->tex->h)
	{
		x = 0;
		while (x < game->tex->w)
		{
			buffer[y * game->tex->h + x] = tmp->data[y * game->tex->h + x];
			++x;
		}
		++y;
	}
	mlx_destroy_image(game->mlx, tmp->img);
	return (buffer);
}

void	init_texture_to_buffer(t_game *game)
{
	t_data	tmp;

	game->textures[0] = xpm_to_img(game, game->so_path, &tmp);
	game->textures[1] = xpm_to_img(game, game->no_path, &tmp);
	game->textures[2] = xpm_to_img(game, game->we_path, &tmp);
	game->textures[3] = xpm_to_img(game, game->ea_path, &tmp);
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		mlx_error(game);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		mlx_error(game);
	game->tex = ft_calloc(1, sizeof(t_texture));
	if (!game->tex)
		malloc_err(game, 0, 0, NULL);
	game->textures = ft_calloc(5, sizeof(int *));
	if (!game->textures)
		malloc_err(game, 0, 0, NULL);
	init_texture_to_buffer(game);
	raycast(game);
	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
	mlx_hook(game->win, KEY_PRESS, 1L << 0, input_handle, game);
	mlx_loop(game->mlx);
}
