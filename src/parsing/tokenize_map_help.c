/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_map_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:19:45 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 23:47:54 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	offmap_to_wall(t_game *game, char **dst)
{
	int	i;
	int	j;

	i = 0;
	while (dst[i])
	{
		j = 0;
		while (dst[i][j])
		{
			if (dst[i][j] == OFFMAP)
				dst[i][j] = WALL;
			j++;
		}
		i++;
	}
	free_2d_array((void**)game->map);
	game->map = dst;
	game->width += 2;
	game->height += 2;
}