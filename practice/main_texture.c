#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

# if defined(__APPLE__)
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
// typedef enum e_key { KEY_W = 13, KEY_A = 0, KEY_S = 1, KEY_D = 2,
// 	KEY_ESC = 53 }	t_key;
# else
#  ifndef M_PI
#   define M_PI (3.14159265358979323846)
#  endif
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

#define KEY_PRESS 2


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
	int		is_side;
	double	perp_wall_dist;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	wall_x;
}	t_ray;

typedef struct texture {
	int		**buffer;
	int		w;
	int		h;
	int		idx;
	double	step;
	double	pos;
	int		x;
	int		y;
}	t_texture;

typedef struct	s_game {
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	char		**map;
	int			**tex_buffer;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
}	t_game;


int worldMap[mapWidth][mapHeight]=
{
};

void	free_2d_array(void **_2d_array)
{
	int	i;

	if (!_2d_array)
		return ;
	i = 0;
	while (_2d_array && _2d_array[i])
	{
		free(_2d_array[i]);
		++i;
	}
	free(_2d_array);
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
	game->ray->camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
	game->ray->dir_x = game->player->dir_x + game->player->plane_x * game->ray->camera_x;
	game->ray->dir_y = game->player->dir_y + game->player->plane_y * game->ray->camera_x;
	game->ray->map_x = game->player->x;
	game->ray->map_y = game->player->y;
	game->ray->delta_x = fabs(1 / game->ray->dir_x);
	game->ray->delta_y = fabs(1 / game->ray->dir_y);
}

void	calculate_line_height(t_game *game)
{
	int hit;

	hit = 0;
	while(hit == 0)
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
		if(game->map[game->ray->map_x][game->ray->map_y] > '0')
			hit = 1;
	}
	if(game->ray->is_side == 0)
		game->ray->perp_wall_dist = (game->ray->side_x - game->ray->delta_x);
	else
		game->ray->perp_wall_dist = (game->ray->side_y - game->ray->delta_y);
	// if (game->ray->is_side == 0)
	// 	game->ray->perp_wall_dist = ((game->ray->map_x - game->player->x) + (1 - game->ray->step_x) / 2) \
	// 					/ game->ray->dir_x;
	// else
	// 	game->ray->perp_wall_dist = ((game->ray->map_y - game->player->y) + (1 - game->ray->step_y) / 2) \
	// 						/ game->ray->dir_y;

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
		if (game->ray->dir_y < 0)
			++game->texture->idx;
		game->ray->wall_x = game->player->x + game->ray->perp_wall_dist * game->ray->dir_x;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
}

void	init_buffer(t_game *game)
{
	int	i;

	if (game->texture->buffer)
		free_2d_array((void **) game->texture->buffer);
	game->texture->buffer = calloc(1, sizeof(int *) * screen_height);
	i = 0;
	while (i < screen_height)
	{
		game->texture->buffer[i] = calloc(1, sizeof(int) * screen_width);
		++i;
	}
}


void	update_buffer(t_game *game, int _x)
{
	int	_y;
	int	color;

	game->texture->x = (int) (game->ray->wall_x * game->texture->w);
	if ((game->ray->is_side == 0 && game->ray->dir_x > 0)
		||(game->ray->is_side == 1 && game->ray->dir_y < 0))
		game->texture->x = game->texture->w - game->texture->x - 1;
	game->texture->step = 1.0 * game->texture->h / game->ray->line_height;
	game->texture->pos = (game->ray->draw_start - screen_height / 2 + game->ray->line_height / 2) * game->texture->step;
	_y = game->ray->draw_start;
	while (_y < game->ray->draw_end)
	{
		game->texture->y = (int) game->texture->pos & (game->texture->h - 1);
		game->texture->pos += game->texture->step;
		color = game->tex_buffer[game->texture->idx][game->texture->h * game->texture->y + game->texture->x];
		if (game->ray->is_side == 1)
			color = (color >> 1) & 8355711;
		game->texture->buffer[_y][_x] = color;
		++_y;
	}
}

int	*xpm_to_img(t_game *game, char *path, t_data *tmp)
{
	int		*buffer;

	tmp->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture->w, &game->texture->h);
	tmp->data = (int *)mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	buffer = (int *)calloc(1, sizeof(int) * game->texture->w * game->texture->h);

	for (int y = 0; y < game->texture->h; ++y)
	{
		for (int x = 0; x < game->texture->w; ++x)
			buffer[y * game->texture->h + x] = tmp->data[y * game->texture->h + x];
	}
	mlx_destroy_image(game->mlx, tmp->img);
	return buffer;
}

void	draw_texture(t_game *game)
{
	t_data	data;
	int		x;
	int		y;

	data.img = mlx_new_image(game->mlx, screen_width, screen_height);
	data.data = (int *) mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y = 0;
	while (y < screen_height)
	{
		x = 0;
		while (x < screen_width)
		{
			data.data[y * screen_width + x] = game->texture->buffer[y][x];
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(game->mlx, game->win, data.img, 0, 0);

	//FIXME:need or not?
	mlx_destroy_image(game->mlx, data.img);
}

int raycast (t_game *game)
{
	int		x;

	x = 0;
	game->ray = calloc(1, sizeof(t_ray));
	if (!game->ray)
	{
		//FIXME:put freeall
		exit(-42);
	}
	init_buffer(game);
	while (x < screen_width)
	{
		init_ray(game, x);
		calculate_step(game);
		calculate_line_height(game);
		calculate_wall_x(game);
		update_buffer(game, x);
		++x;
	}
	draw_texture(game);
	free(game->ray);
	return (0);
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

	game->tex_buffer[0] = xpm_to_img(game, "../asset/textures/wall_s.xpm", &tmp);
	game->tex_buffer[1] = xpm_to_img(game, "../asset/textures/wall_n.xpm", &tmp);
	game->tex_buffer[2] = xpm_to_img(game, "../asset/textures/wall_w.xpm", &tmp);
	game->tex_buffer[3] = xpm_to_img(game, "../asset/textures/wall_e.xpm", &tmp);
}


void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screen_width, screen_height, "cub3d");
	game->map = calloc(mapHeight, 8);
	game->texture = calloc(1, sizeof(t_texture));
	game->player = calloc(1, sizeof(t_player));
	//FIXME: x,y location reverese (because DDA algo calculate with map[x][y])
	game->player->x = 5.5;
	game->player->y = 20.5;

	game->player->dir_x = -1.0;
	game->player->dir_y = 0.0;
	game->tex_buffer = calloc(4, sizeof(int *));
	game->player->plane_x = 0;
	game->player->plane_y = 0.66;
	init_buffer(game);
	if (!(game && game->mlx && game->win && game->map
		&& game->texture && game->player && game->tex_buffer))
	{
		//FIXME:put free all function
		exit(-42);
	}
}

int	manage_input_key(int code, t_game *game)
{
	double x;
	double y;

	x = game->player->x;
	y = game->player->y;

	if (code == KEY_ESC)
	{
		//FIXME:freeall
		exit(0);
	}
	if (game->map[(int)game->player->y][(int) game->player->x] == '0')
	{
		if (code == KEY_W)
			game->player->x -= 0.1;
		else if (code == KEY_S)
			game->player->x += 0.1;
		else if (code == KEY_A)
			game->player->y -= 0.1;
		else if (code == KEY_D)
			game->player->y += 0.1;
	}
	raycast(game);
	return (0);
}

int main(void)
{
	t_game *game;

	game = calloc(1, sizeof(t_game));

	init_game(game);

	//just instead of real parsing.
	copy_map_into_game(game);

	init_texture_to_buffer(game);
	print_map(game);
	raycast(game);
	mlx_hook(game->win, KEY_PRESS, 0, manage_input_key, game);
	mlx_loop(game->mlx);

	return (0);
}