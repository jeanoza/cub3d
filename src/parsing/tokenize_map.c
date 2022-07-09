/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:17:09 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 17:23:48 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	malloc_err(t_game *game, int code, int i, char **dst)
{
	ft_putstr_fd("Error\nMalloc couldn't allocate more memory\n", 2);
	if (code == 1)
	{
		while (i >= 0)
		{
			free(dst[i]);
			i--;
		}
		free(dst);
	}	
	free_game(game);
	exit(1);
}

static char	**malloc_dst(t_game *game)
{
	char	**dst;
	int		i;

	dst = (char **)malloc(sizeof(char*) * (game->height + 3));
	if (!dst)
		malloc_err(game, 0, 0, NULL);
	i = 0;
	while (i < game->height + 2)
	{
		dst[i] = (char *)malloc(sizeof(char) * (game->width + 3));
		if (!dst[i])
			malloc_err(game, 1, i, dst);
		i++;
	}
	return (dst);
}

static void	fill_edges(char **dst, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->width + 2)
	{
		dst[0][i] = 'A';
		dst[game->height + 1][i] = 'A';
		i++;
	}
	i = 0;
	while (i < game->height + 2)
	{
		dst[i][0] = 'A';
		if (i > 0 && i < game->height + 1)
		{
			for(int j = 1; j < game->width + 1; j++)
			dst[i][j] = 'B';
		}
		dst[i][game->width + 1] = 'A';
		dst[i][game->width + 2] = 0;
		i++;
	}
	dst[i] = 0;
}

char **tokenize(t_game *game, char **src)
{
	char	**dst;

	(void)src;
	dst = malloc_dst(game);
	fill_edges(dst, game);
	return (dst);
}