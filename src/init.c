/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:27:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/17 03:27:55 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	mlx_error(t_game *game)
{
	ft_putstr_fd("Error\n\
[42]    424242 segmentation fault (core dumped)  ./notcub3d 42.cub\n\
just kidding ahah mlx isnt happy with env -i\n", 2);
	free_game(game);
	exit(1);
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		mlx_error(game);
	game->win = mlx_new_window(game->mlx, 1440, 900, "cub3d");

	print_game(game);
	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
	mlx_loop(game->mlx);
}