/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:31:36 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/14 22:36:23 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_game *game)
{
	if (game->image)
	{
		if (game->image->img)
			mlx_destroy_image(game->mlx, game->image->img);
		//if (game->image->addr)
		//	free(game->image->addr);
		free(game->image);
	}
}

int	close_game_win_ctrl(t_game *game)
{
	if (mlx_destroy_window(game->mlx, game->win))
	{
		printf("Error\nDestroy window failed\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	//FIXME: en mlx_mac : y a pas de destroy_display mince! on verra ensemble ca apres
	free_img(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	printf("Closed by win x button\n");
	exit(EXIT_SUCCESS);
}