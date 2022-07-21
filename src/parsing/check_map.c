/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:25:20 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/21 17:35:18 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_player_angle(t_game *game, char angle)
{
	if (angle == 'N')
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	if (angle == 'E')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	if (angle == 'W')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	if (angle == 'S')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
}


static void	set_player(t_game *game, int i, int j)
{
	if (!game->player)
		game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		free_game(game);
		exit(1);
	}
	//FIXME: x and y is not same in ordinary math,
	//as i use map[x][y] in raycast
	//so, x is first dimension, y is second dimension in map.
	//FIXME: maybe, if we change the method of parsing,
	//we have to change this value (ex:i + 1.5 => i + 0.5)
	game->player->x = i + 1.5;
	game->player->y = j + 1.5;
	// if (game->map[i][j] == 'N')
	// 	game->player->dir = NORTH;
	// if (game->map[i][j] == 'W')
	// 	game->player->dir = WEST;
	// if (game->map[i][j] == 'E')
	// 	game->player->dir = EAST;
	// if (game->map[i][j] == 'S')
	// 	game->player->dir = SOUTH;
	set_player_angle(game, game->map[i][j]);
	game->map[i][j] = '0';
}

static int	check_forbidden_char(t_game *game)
{
	int		i;
	int		j;
	int		nbr;
	char	**map;

	map = game->map;
	i = 0;
	nbr = 0;
	while (map && map[i])
	{
		j = 0;
		while (map && map[i][j])
		{
			if (!is_valid(map[i][j]))
				return (-2);
			if (is_valid(map[i][j]) == 2)
			{
				set_player(game, i, j);
				nbr++;
			}
			j++;
		}
		i++;
	}
	return (nbr - 1);
}

static void	check_forb_char_player(t_game *game)
{
	int	ret;
	int	err;

	err = 0;
	ret = check_forbidden_char(game);
	if (ret == -2 && ++err)
		ft_putstr_fd("Error\nForbidden char in map\n", 2);
	else if ((ret > 0 || ret == -1) && ++err)
		ft_putstr_fd("Error\nExactly 1 player needed\n", 2);
	if (err)
	{
		free_game(game);
		exit (1);
	}
}

static void	check_empty_line(t_game *game)
{
	char	**s;
	char	h[1];
	int		tmp;
	int		i;

	s = game->map;
	i = 0;
	tmp = -1;
	while (s[i])
	{
		if (s[i][0] == 0)
			tmp = i;
		i++;
	}
	*h = i - tmp;
	if (tmp >= 0)
		error_parsing(ERR_MAP, h, game);
}

void	check_map(t_game *game)
{
	char	**tok_map;

	check_forb_char_player(game);
	check_empty_line(game);
	tok_map = tokenize(game, game->map);
	if (check_void_offmap_seeker(tok_map))
	{
		free_2d_array((void **)tok_map);
		free_game(game);
		exit(1);
	}
	offmap_to_wall(game, tok_map);
}
