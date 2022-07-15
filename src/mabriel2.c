/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mabriel2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:32:16 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/15 21:37:59 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	maxime_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		mlx_error(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		mlx_error(game);
	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
}

void	image_error(t_game *game, char *msg)
{
	if (game->image)
	{
		if (game->image->img)
			mlx_destroy_image(game->mlx, game->image->img);
		//if (game->image->addr)
		//	free(game->image->addr);
		free(game->image);
	}
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	create_img(t_game *game, t_data **img, char *path)
{
	t_data *i;
	int		size;

	(void)img;
	i = ft_calloc(1, sizeof(t_data));
	if (!i)
		image_error(game, "Error\nMalloc Error\n");
	if (!path)
		i->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	else
		i->img = mlx_xpm_file_to_image(game->mlx, "asset/textures/wall_e.xpm", &size, &size);
	if (!i->img)
		image_error(game, "Error\nImage couldn't be created\n");
	i->addr = \
	mlx_get_data_addr(i->img, &i->bits_per_pixel, \
	&i->line_length, &i->endian);
	if (!i->addr)
		image_error(game, "Error\nmlx_get_data_addr failed\n");
	*img = i; 
}

void	set_image(t_game *game)
{
	int	i;

	i = 0;
	while (i < (game->image->line_length * HEIGHT) - 100)
	{
			game->image->addr[i] = (char)0;
			game->image->addr[i + 1] = (char)0;
			game->image->addr[i + 2] = (char)255;
			game->image->addr[i + 3] = (char)0;
		i += 4;
	}
}



int	function(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	
	return (0);
}

void	maxime(t_game *game)
{
	t_data *north;

	maxime_init(game);
	create_img(game, &game->image, NULL);
	create_img(game, &north, game->no_path);
	set_image(game);
	game->image = north;
	int	midx = (WIDTH / 2) - 32;
	int midy = (HEIGHT / 2) - 32;
	//mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, north->img, midx, midy);
	mlx_loop_hook(game->win, &function, game);
	mlx_loop(game->mlx);
}
