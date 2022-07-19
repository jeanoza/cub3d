/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mabriel2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:32:16 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/19 05:35:00 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

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

void	create_image(t_game *game)
{
	game->image = ft_calloc(1, sizeof(t_data));
	game->image->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->image->addr = (int *)mlx_get_data_addr\
	(game->image->img, &game->image->bits_per_pixel, \
	&game->image->line_length, &game->image->endian);
}

// void	create_img(t_game *game, t_data **img, char *path)
// {
// 	t_data *i;
// 	int		size;

// 	(void)img;
// 	i = ft_calloc(1, sizeof(t_data));
// 	if (!i)
// 		image_error(game, "Error\nMalloc Error\n");
// 	if (!path)
// 		i->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	else
// 		i->img = mlx_xpm_file_to_image(game->mlx, "asset/textures/wall_e.xpm", &size, &size);
// 	if (!i->img)
// 		image_error(game, "Error\nImage couldn't be created\n");
// 	i->data = 
// 	mlx_get_data_addr(i->img, &i->bits_per_pixel, 
// 	&i->line_length, &i->endian);
// 	if (!i->addr)
// 		image_error(game, "Error\nmlx_get_data_addr failed\n");
// 	*img = i; 
// }

void	draw_square(t_game *game, int size, int color, int x, int y)
{
	int	i;
	int	j;

	i = y;
	while (i < size + y)
	{
		j = x;
		while (j < size + x)
		{
			game->image->addr[(i * WIDTH) + j] = color;
			j++;
		}
		game->image->addr[(i * WIDTH) + j] = 0;
		i++;
	}
	j = x;
	while (j < size + x)
	{
		game->image->addr[(i * WIDTH) + j] = 0;
		j++;
	}
}

#define PI 3.1415926535
float	px,  py;
float	pdx, pdy, pa; 

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	size;

	size = 64;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == WALL)
				draw_square(game, size - 1, INT_MAX, j * size, i * size);
			else
				draw_square(game, size - 1, 44444, j * size, i * size);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	draw_square(game, 20, 8888, px, py);
}

void	draw_line(t_game *game, int x1, int y1, int x2, int y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;

	float x, y, step, i;
	if (abs((int)dx) >= abs((int)dy))
		step = abs((int)dx);
	else
		step = abs((int)dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 1;
	while (i <= step)
	{
		game->image->addr[(int)(((int)y * WIDTH) + (int)x)] = INT_MAX / 6;
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_player_line(t_game *game)
{
	float	x;
	float	y;

	x = (float)cos(pa) * 50;
	y = (float)sin(pa) * 50;
	draw_line(game, px + 10, py + 10, px + 10 + x, py + 10 - y);
}

void	cast_rays(t_game *game)
{
	int	gridx, gridy;
	float	xo, yo;
	float	ay, ax;
	float	ra;

	ra = pa;
	if (ra < PI) // looking up
	{
		ay = (((int)py >> 6) << 6) - 10;
		yo = -64;
	}
	if (ra > PI) // looking down
	{
		ay = (((int)py >> 6) << 6) + 64;
		yo = 64;
	}
	ax = px + (py-ay) / tan(ra);
	xo = 64 / tan(ra);
	while (game->map[(int)ay / 64][(int)ax / 64] == '0')
	{
		ax += xo;
		ay += yo;
	}
	draw_line(game, px + 10, py + 10, ax + 10, ay + 10);
	printf("ax:%f ay:%f\n",ax,ay);
}


int	function(int keycode, t_game *game)
{
	if (keycode == 'w')
	{
		py += pdy;
		px += pdx;
	}
	if (keycode == 'a')
	{
		py -= pdx;
		px += pdy;
	}
	if (keycode == 'd')
	{
		py += pdx;
		px -= pdy;
	}
	if (keycode == 's')
	{
		py -= pdy;
		px -= pdx;
	}
	if (keycode == 65363)
	{
		pa -= 0.03;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == 65361)
		{
		pa += 0.03;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	draw_map(game);
	draw_player(game);
	//draw_line(game, px + 12, py + 12, (pdx + px)*10, (pdy + py)*10);
	draw_player_line(game);
	//cast_rays(game);
	printf("%f\n",pa);
	mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	return (0);
}

void	maxime(t_game *game)
{
//	t_data *north;
	px = (game->player->x - 1) * 64 + 20;
	py = (game->player->y - 1) * 64 + 20;
	pa = PI / 2; //for north
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	maxime_init(game);
	create_image(game);
	draw_map(game);
	draw_player(game);
	draw_player_line(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win, north->img, 0, 0);
	mlx_hook(game->win, 02, 1L<<0, &function, game);
	mlx_loop(game->mlx);
}
