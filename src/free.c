/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:10:27 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/04 08:59:36 by kyubongchoi      ###   ########.fr       */
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
		if (game->map)
			free_2d_array((void **)game->map);
		if (game->player)
			free(game->player);
		free(game);
	}
}