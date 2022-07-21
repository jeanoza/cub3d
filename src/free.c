/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:10:27 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/21 16:53:51 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static	void	free_game_element(t_game *game)
{
	if (game->no_path)
		free(game->no_path);
	if (game->so_path)
		free(game->so_path);
	if (game->we_path)
		free(game->we_path);
	if (game->ea_path)
		free(game->ea_path);
	if (game->fcolor)
		free(game->fcolor);
	if (game->ccolor)
		free(game->ccolor);
	if (game->map)
		free_2d_array((void **)game->map);
	if (game->textures)
		free_2d_array((void **)game->textures);
}

#if defined(__APPLE__)

static	void	destroy_mlx(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
}
#else

static	void	destroy_mlx(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
#endif

void	free_game(t_game *game)
{
	if (game)
	{
		if (game->mlx)
			destroy_mlx(game);
		free_game_element(game);
		if (game->player)
			free(game->player);
		if (game->tex)
		{
			if (game->tex->buffer)
				free_2d_array((void **)game->tex->buffer);
			free(game->tex);
		}
		free(game);
	}
}
