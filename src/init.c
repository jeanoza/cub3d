/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:27:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 10:38:23 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//FIXME: to see after raycasting to put pixel of floor and ceilling
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
	//t_data img;
	// img.img = mlx_new_image(game->mlx, 1440, 900);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 	&img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 255);
	// mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);

void	init(t_game *game)
{
	//FIXME: this is example : 2nd and 3rd parametre have to be changed by input(parsing)
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1440, 900, "cub3d");
	print_game(game);
	mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
	mlx_loop(game->mlx);
}