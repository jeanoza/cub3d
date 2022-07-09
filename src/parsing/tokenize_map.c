/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:17:09 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 22:50:19 by mabriel          ###   ########.fr       */
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

static void	fill_edges(t_game *game, char **dst)
{
	int	i;

	i = 0;
	while (i < game->width + 2)
	{
		dst[0][i] = OFFMAP;
		dst[game->height + 1][i] = OFFMAP;
		i++;
	}
	i = 0;
	while (i < game->height + 2)
	{
		dst[i][0] = OFFMAP;
		dst[i][game->width + 1] = OFFMAP;
		dst[i][game->width + 2] = 0;
		i++;
	}
	dst[i] = 0;
}

static void	fill_inside(t_game *game, char **src, char **dst)
{
	int	i;
	int	j;

	i = 0;
	while (src && src[i])
	{
		j = 0;
		while (src[i][j])
		{
			dst[i + 1][j + 1] = src[i][j];
			j++;
		}
		while (j < game->width + 1)
		{
			dst[i + 1][j + 1] = OFFMAP;
			j++;
		}
		i++;
	}
}

char **tokenize(t_game *game, char **src)
{
	char	**dst;

	(void)src;
	dst = malloc_dst(game);
	fill_edges(game, dst);
	fill_inside(game, src, dst);
	set_space(dst);
	return (dst);
}