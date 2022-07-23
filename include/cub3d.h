/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:07 by kychoi            #+#    #+#             */
/*   Updated: 2022/07/23 17:02:54 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m" //purple
# define CYN "\033[0;36m" //emerald
# define WHT "\033[0;37m"
# define DFT "\033[0m"

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>

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
#  define KEY_ESC 65307
# endif
//FIXME KEY_ESC
# define KEY_PRESS 2

/* libft */
# include "libft.h"
/* mlx */
# include "mlx.h"

/* Pointer size */
# define P_SIZE 8

/* Map Token */
# define OFFMAP 'O'
# define VOID	'0'
# define WALL	'1'
# define SPACE	' '

# define RADIAN 0.05
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

typedef enum e_bool { FALSE, TRUE }	t_bool;
typedef enum e_error { ERR_MAP = 1, ERR_LINE = 2 }	t_error;
typedef enum e_event { EVENT_EXIT_WIN = 17 }	t_event;
typedef enum e_dir { NORTH, SOUTH, EAST, WEST }	t_dir;

//TODO: parler avec Max pour des variables dans s_player et t_game
typedef struct s_player {
	double	x;
	double	y;
	t_dir	dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_data {
	void	*img;
	int		*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_ray {
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

typedef struct s_texture {
	int		**buffer;
	int		w;
	int		h;
	int		idx;
	double	step;
	double	pos;
	int		x;
	int		y;
}	t_texture;

//Principal struct
typedef struct s_game {
	int			f_color;
	int			c_color;
	int			width;
	int			height;
	void		*mlx;
	void		*win;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*ccolor;
	char		*fcolor;
	char		**map;
	int			count;
	int			line;
	int			err;
	int			**textures;
	t_player	*player;
	t_ray		*ray;
	t_texture	*tex;
}	t_game;

/* *********************************************************************** */
/*                               PARSING                                   */
/* *********************************************************************** */
/* parse.c */
int		parse(char **av, t_game *game);
int		check_place(t_game *game, int place);
int		validate_line(char *line, t_game *game);
int		check_extension(char *s, char *ex);

/* check_map.c */
void	check_map(t_game *game);
int		is_valid(int c);
void	check_file_and_color(t_game *game);
void	set_player_angle(t_game *game, char angle);

/* parse_error.c */
void	error_parsing(t_error err_code, char *msg, t_game *game);
void	exit_error_file(t_game *game, int err_code);
int		forest_help(t_game *game, int code);
int		open_file(char *s, t_game *game);

/* tokenize_map.c */
char	**tokenize(t_game *game, char **src);
void	malloc_err(t_game *game, int code, int i, char **dst);

int		heat_seeking(char **dst);
int		seeking(char **dst, int x, int y, int for_char);
void	set_space(char **dst);
int		check_void_offmap_seeker(char **dst);

/* tokenize_map_help.c */
void	offmap_to_wall(t_game *game, char **dst);
int		check_digit(char *s);

void	maxime(t_game *game);
void	mlx_error(t_game *game);

/* putter.c */
int		put_map(t_game *game, char *line, int idx);
void	put_texture(t_game *game, char *line);
char	**put_floor_ceil(t_game *game, char *line);
void	check_textures_extention(t_game *game, char *s);

/* *********************************************************************** */
/*                               RAYCASTING                                */
/* *********************************************************************** */
/* raycast.c */
int		raycast(t_game *game);
void	init_ray(t_game *game, int x);

/* raycast_cal */
void	calculate(t_game *game);

/* init.c */
void	init(t_game *game);

/* event.c */
int		close_game_win_ctrl(t_game *game);
int		input_handle(int code, t_game *game);

/* utils.c */
int		encode_rgb(int red, int green, int blue);
int		index_of(char *str, char to_find);

/* painter.c */
void	put_header(void);
void	print_game(t_game *game);

/* free.c */
void	free_game(t_game *game);
void	free_2d_array(void **_2d_array);

#endif
