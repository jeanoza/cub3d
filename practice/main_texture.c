#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx.h"

//Mac OS
//gcc main_ranged.c -I../mlx_mac/ -L../mlx_mac/ -lmlx -framework OpenGL -framework AppKit
//Linux 42
//gcc main_ranged.c -I../mlx_linux/ -L../mlx_linux/ -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd

#define mapWidth 24
#define mapHeight 24
#define screen_width 640
#define screen_height 480

typedef	struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_player{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct	s_ray {
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		is_hit;
	int		is_side;
	double	perp_wall_dist;
}	t_ray;

typedef struct	s_game {
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	char		**map;
	t_player	*player;
}	t_game;


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	calculate_step(t_game *game, t_ray *ray)
{
	if(ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player->x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_x;
	}
	if(ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player->y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_y;
	}


}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
	ray->dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;

	ray->map_x = game->player->x;
	ray->map_y = game->player->y;

	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);

	//FIXME: undefined put or not?
	ray->perp_wall_dist = 0;

	//what direction to step in x or y-direction (either +1 or -1)
	//FIXME: undefined put or not?
	ray->step_x = 0;
	ray->step_y = 0;

	ray->is_hit = 0; //was there a wall hit?
	//FIXME: undefined put or not?
	ray->is_side = 0; //was a NS or a EW wall hit?

}

int	find_object(t_game *game, t_ray *ray)
{
	while(ray->is_hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->is_side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->is_side = 1;
		}
		//Check if ray has hit a wall
		if(game->map[ray->map_x][ray->map_y] > '0')
			ray->is_hit = 1;
	}
	if(ray->is_side == 0)
		ray->perp_wall_dist = (ray->side_x - ray->delta_x);
	else
		ray->perp_wall_dist = (ray->side_y - ray->delta_y);
	//Calculate height of line to draw on screen
	return (int)(screen_height / ray->perp_wall_dist);
}

//FIXME: it will not be useful maybe...
int	get_color(t_game *game, t_ray *ray)
{
	if (game->map[ray->map_x][ray->map_y] == '1')
		return encode_rgb(255, 0, 0);
	if (game->map[ray->map_x][ray->map_y] == '2')
		return encode_rgb(0, 255, 0);
	if (game->map[ray->map_x][ray->map_y] == '3')
		return encode_rgb(0, 0, 255);
	if (game->map[ray->map_x][ray->map_y] == '4')
		return encode_rgb(255, 255, 0);
	return (0);
}

void	put_pixel(t_game *game, int color, int x, int draw[2])
{
	t_data	data;
	int		y;

	data.img = mlx_new_image(game->mlx, screen_width, screen_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	y = draw[0];
	while (y < draw[1])
	{
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		++y;
	}
}

/*
* draw [2] = [start, end]
*/
void raycast (t_game *game)
{
	int		x;
	int		line_height;
	int		draw[2];
	t_ray	ray;

	x = 0;
	while (x < screen_width)
	{
		init_ray(game, &ray, x);
		//calculate step and initial sideDist
		calculate_step(game, &ray);
		line_height = find_object(game, &ray);

		//calculate lowest and highest pixel to fill in current stripe
		draw[0] = -line_height / 2 + screen_height / 2;
		if(draw[0] < 0)
			draw[0] = 0;
		draw[1] = line_height / 2 + screen_height / 2;
		if(draw[1] >= screen_height)
			draw[1] = screen_height - 1;
		put_pixel(game, get_color(game, &ray), x, draw);
		++x;
	}
}

void copy_map_into_game(t_game *game)
{
	int y;
	int x;
	y = 0;
	while (y < mapHeight)
	{
		game->map[y] = calloc(1, mapWidth);
		x = 0;
		while (x < mapWidth)
		{
			game->map[y][x] = worldMap[y][x] + '0';
			++x;
		}
		++y;
	}
}

void print_map(t_game *game)
{
	int y;
	int x;
	y = 0;
	while (y < mapHeight)
	{
		x = 0;
		while (x < mapWidth)
		{
			printf("%c", game->map[y][x]);
			++x;
		}
		printf("\n");
		++y;
	}
}

int main(void)
{
	t_game *game;

	game = calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screen_width, screen_height, "cub3d");
	game->map = calloc(mapHeight, 8);
	game->player = calloc(1, sizeof(t_player));
	game->player->x = 22;
	game->player->y = 12;
	game->player->dir_x = -1;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;


	copy_map_into_game(game);
	raycast(game);
	mlx_loop(game->mlx);

	return (0);
}