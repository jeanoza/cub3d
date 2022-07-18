/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:27:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/18 20:33:00 by kyubongchoi      ###   ########.fr       */
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

	tmp->img = mlx_xpm_file_to_image(game->mlx, path, &game->tex->w, &game->tex->h);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	buffer = (int *)calloc(1, sizeof(int) * game->tex->w * game->tex->h);

	for (int y = 0; y < game->tex->h; ++y)
	{
		for (int x = 0; x < game->tex->w; ++x)
			buffer[y * game->tex->h + x] = tmp->data[y * game->tex->h + x];
	}
	mlx_destroy_image(game->mlx, tmp->img);
	return buffer;
}

void	init_texture_to_buffer(t_game *game)
{
	t_data tmp;

	game->textures[0] = xpm_to_img(game, "./asset/textures/wall_s.xpm", &tmp);
	game->textures[1] = xpm_to_img(game, "./asset/textures/wall_n.xpm", &tmp);
	game->textures[2] = xpm_to_img(game, "./asset/textures/wall_w.xpm", &tmp);
	game->textures[3] = xpm_to_img(game, "./asset/textures/wall_e.xpm", &tmp);
}

// void	init_game(t_game *game)
// {
// 	//FIXME:put free all function
// 	// if (!(game && game->mlx && game->win && game->map
// 	// 	&& game->tex && game->player && game->textures))
// 	// {
// 	// 	exit(-42);
// 	// }
// }

int	input_handle(int code, t_game *game)
{
	double x;
	double y;

	x = game->player->x;
	y = game->player->y;

	if (code == KEY_ESC)
	{
		//FIXME:func exit which contains freeall(game)
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
	if (game->map[(int)game->player->x][(int) game->player->y] != '0')
	{
		game->player->x = x;
		game->player->y = y;
	}
	raycast(game);
	return (0);
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		mlx_error(game);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game->tex = calloc(1, sizeof(t_texture));

	//FIXME:put this in parse (x to y, y to x)
	game->player->x = 13.0;
	game->player->y = 28.0;

	game->player->dir_x = -1.0;
	game->player->dir_y = 0.0;
	game->textures = calloc(4, sizeof(int *));
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;

	init_texture_to_buffer(game);
	raycast(game);

	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
	mlx_hook(game->win, KEY_PRESS, 0, input_handle, game);
	mlx_loop(game->mlx);
}