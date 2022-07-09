/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:07 by kychoi            #+#    #+#             */
/*   Updated: 2022/07/10 00:47:46 by mabriel          ###   ########.fr       */
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

/* libft */
# include "libft.h"
/* mlx */
# include "mlx.h"

/* Pointer size */
# define P_SIZE 8
# define OFFMAP 'O'
# define VOID	'0'
# define WALL	'1'
# define SPACE	' ' 

typedef enum e_bool { FALSE, TRUE }	t_bool;
typedef enum e_error { ERR_PARSE = -42 ,ERR_MAP = 1, ERR_LINE = 2 }	t_error;
typedef enum e_event { EVENT_EXIT_WIN = 17 }	t_event;
typedef enum e_dir {NORTH, SOUTH, EAST, WEST} t_dir;

//TODO: parler avec Max pour des variables dans s_player et t_game
typedef struct	s_player {
	int		x;
	int		y;
	t_dir	dir;
}	t_player;

typedef	struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

//Principal struct
typedef struct	s_game {
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
	t_player	*player;
}	t_game;


/* *********************************************************************** */
/*                               PARSING                                   */
/* *********************************************************************** */
/* parse.c */
int		parse(char **av, t_game *game);
int		check_place(t_game *game, int place);
int		validate_line(char *line, t_game *game);

/* check_map.c */
void	check_map(t_game *game);
int		is_valid(int c);

void	check_file_and_color(t_game *game);

/* parse_error.c */
void	error_parsing(t_error err_code, char *msg, t_game *game);
void	exit_error_file(t_game *game, int err_code);
int		forest_help(t_game *game, int code);
int		open_file(char *s, t_game *game);

/* tokenize_map.c */
char	**tokenize(t_game *game, char **src);

int		heat_seeking(char **dst);
int		seeking(char **dst, int	x, int y, int for_char);
void	set_space(char **dst);
int		check_void_offmap_seeker(char **dst);

/* tokenize_map_help.c */
void	offmap_to_wall(t_game *game, char **dst);

/* putter.c */
int		put_map(t_game *game, char *line, int idx);
void	put_texture(t_game *game, char *line);
char	**put_floor_ceil(t_game *game, char *line);

/* init.c */
void	init(t_game *game);

/* event.c */
int		close_game_win_ctrl(t_game *game);

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
