/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:07 by kychoi            #+#    #+#             */
/*   Updated: 2022/07/05 08:56:43 by kyubongchoi      ###   ########.fr       */
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

typedef enum e_bool { FALSE, TRUE }	t_bool;
typedef enum e_error { ERR_PARSE = -42 }	t_error;
typedef enum e_event { EVENT_EXIT_WIN = 17 }	t_event;

//TODO: parler avec Max pour des variables dans s_player et t_game
typedef struct s_player {
	int		x;
	int		y;
}	t_player;

//Principal struct
typedef struct s_game {
	void		*mlx;
	void		*win;
	char		*NO_path;
	char		*SO_path;
	char		*WE_path;
	char		*EA_path;
	char		**map;
	t_player	*player;
}	t_game;

/* parse.c */
int parse(char **av, t_game *game);

/* painter.c */
void	put_header(void);
void	print_game(t_game *game);

/* free.c */
void	free_game(t_game *game);

#endif
