/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:10:27 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/07 17:24:11 by kyubongchoi      ###   ########.fr       */
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
		if (game->no_path)
			free(game->no_path);
		if (game->so_path)
			free(game->so_path);
		if (game->we_path)
			free(game->we_path);
		if (game->ea_path)
			free(game->ea_path);
		if (game->f_color)
			free(game->f_color);
		if (game->c_color)
			free(game->c_color);
		if (game->map)
			free_2d_array((void **)game->map);
		if (game->player)
			free(game->player);
		free(game);
	}
}