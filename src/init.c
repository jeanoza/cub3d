/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:27:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/19 22:49:13 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_error(t_game *game)
{
	ft_putstr_fd("Error\n\
[42]    424242 segmentation fault (core dumped)  ./notcub3d 42.cub\n\
just kidding ahah mlx isnt happy with env -i\n", 2);
	free_game(game);
	exit(1);
}

int	*xpm_to_img(t_game *game, char *path, t_data *tmp)
{
	int		*buffer;
	int		x;
	int		y;

	//TODO:add protection if there is no file...?
	tmp->img = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex->w, &game->tex->h);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel,
			&tmp->line_length, &tmp->endian);
	buffer = (int *)ft_calloc(1, sizeof(int) * game->tex->w * game->tex->h);
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

	game->textures[0] = xpm_to_img(game, game->so_path + 3, &tmp);
	game->textures[1] = xpm_to_img(game, game->no_path + 3, &tmp);
	game->textures[2] = xpm_to_img(game, game->we_path + 3, &tmp);
	game->textures[3] = xpm_to_img(game, game->ea_path + 3, &tmp);
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		mlx_error(game);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game->tex = ft_calloc(1, sizeof(t_texture));

	game->player->dir_x = -1.0;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	game->textures = ft_calloc(5, sizeof(int *));

	init_texture_to_buffer(game);
	raycast(game);
	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
	mlx_hook(game->win, KEY_PRESS, 0, input_handle, game);
	mlx_loop(game->mlx);
}