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
	int		*data;
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
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	wall_x;
}	t_ray;

typedef struct texture {
	int		w;
	int		h;
	int		idx;
	double	step;
	double	position;
	int		x;
	int		y;
}	t_texture;

typedef struct	s_game {
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	char		**map;
	int			**buffer;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
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
	game->ray = calloc(1, sizeof(t_ray));
	game->ray->camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
	game->ray->dir_x = game->player->dir_x + game->player->plane_x * game->ray->camera_x;
	game->ray->dir_y = game->player->dir_y + game->player->plane_y * game->ray->camera_x;

	game->ray->map_x = game->player->x;
	game->ray->map_y = game->player->y;

	game->ray->delta_x = fabs(1 / game->ray->dir_x);
	game->ray->delta_y = fabs(1 / game->ray->dir_y);

	//what direction to step in x or y-direction (either +1 or -1)

}

int	calculate_line_height(t_game *game)
{
	while(game->ray->is_hit == 0)
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
		if(game->map[game->ray->map_x][game->ray->map_y] != '0')
			game->ray->is_hit = 1;
	}
	if(game->ray->is_side == 0)
		game->ray->perp_wall_dist = (game->ray->side_x - game->ray->delta_x);
	else
		game->ray->perp_wall_dist = (game->ray->side_y - game->ray->delta_y);
	//Calculate height of line to draw on screen
	game->ray->line_height = (int)(screen_height / game->ray->perp_wall_dist);
}

void	calculate_wall_x(t_game *game)
{
	game->ray->draw_start = -game->ray->line_height / 2 + screen_height / 2;
	if(game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + screen_height / 2;
	if(game->ray->draw_end >= screen_height)
		game->ray->draw_end = screen_height - 1;
	if (game->ray->is_side == 0)
	{
		game->texture->idx = 0;
		if (game->ray->dir_x > 0)
			++game->texture->idx;
		game->ray->wall_x = game->player->y + game->ray->perp_wall_dist * game->ray->dir_y;
	}
	else
	{
		game->texture->idx = 2;
		if (game->ray->dir_x < 0)
			++game->texture->idx;
		game->ray->wall_x = game->player->x + game->ray->perp_wall_dist * game->ray->dir_x;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
}

void	update_buffer(t_game *game)
{
	double step;
	double tex_pos;
	int tex_y;
	int tex_x;


}

int	*xpm_to_img(t_game *game, char *path, t_data *tmp)
{
	int		*buffer;

	tmp->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture->w, &game->texture->h);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	buffer = (int *)malloc(sizeof(int) * game->texture->w * game->texture->h);


	for (int y = 0; y < game->texture->h; ++y)
	{
		for (int x = 0; x < game->texture->w; ++x)
			buffer[y * game->texture->h + x] = tmp->data[y * game->texture->h + x];
	}
	// mlx_destroy_image(game->mlx, tmp->img);
	return buffer;
}

void raycast (t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (x < screen_width)
	{
		init_ray(game, x);
		//calculate step and initial sideDist
		calculate_step(game);
		calculate_line_height(game);
		calculate_wall_x(game);
		// update_buffer(game);

		//calculate lowest and highest pixel to fill in current stripe
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

void	init_texture_to_buffer(t_game *game)
{
	t_data tmp;

	// game->buffer = (int **)malloc(sizeof(int *) * 4);
	game->buffer[0] = xpm_to_img(game->mlx, "../asset/textures/wall_s.xpm", &tmp);
	game->buffer[1] = xpm_to_img(game->mlx, "../asset/textures/wall_n.xpm", &tmp);
	game->buffer[2] = xpm_to_img(game->mlx, "../asset/textures/wall_w.xpm", &tmp);
	game->buffer[3] = xpm_to_img(game->mlx, "../asset/textures/wall_e.xpm", &tmp);
}

int main(void)
{
	t_game *game;

	game = calloc(1, sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screen_width, screen_height, "cub3d");
	game->map = calloc(mapHeight, 8);
	game->player = calloc(1, sizeof(t_player));
	game->ray = calloc(1, sizeof(t_ray));
	game->texture = calloc(1, sizeof(t_texture));
	game->player->x = 22;
	game->player->y = 12;
	game->player->dir_x = -1;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;

	//just instead of real parsing.
	copy_map_into_game(game);

	init_texture_to_buffer(game);
	// raycast(game);
	mlx_loop(game->mlx);

	return (0);
}