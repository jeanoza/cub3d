/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:07 by kychoi            #+#    #+#             */
/*   Updated: 2022/07/02 12:54:31 by kychoi           ###   ########.fr       */
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

//TODO: parler avec Max pour des variables dans t_map et t_game
typedef struct s_map {
	int		x;
	int		y;
}	t_map;

typedef struct s_player {
	int		x;
	int		y;
}	t_player;

//Principal struct
typedef struct s_game {
	void		*mlx;
	void		*win;
	t_map		**map;
	t_player	player;
}	t_game;

/*  */
void	put_header(void);

#endif
