/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:10:27 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/03 18:42:34 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_2d_array(void **_2d_array)
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

void	free_game(t_game *game)
{
	if (game)
	{
		//FIXME: if destroy in this function there is leaks from mlx (to test in linux)
		// if (game->mlx && game->win)
		// 	mlx_destroy_window(game->mlx, game->win);
		if (game->map)
			free_2d_array((void **)game->map);
		if (game->player)
			free(game->player);
		free(game);
	}
}