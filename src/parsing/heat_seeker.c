/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_seeker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:01:27 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 22:02:04 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	search_up(char **dst, int x, int y, int for_char)
{
	int	i;

	i = y;
	while (i >= 0 && dst[i][x] != WALL)
	{
		if (dst[i][x] == for_char)
			return (1);
		i--;
	}
	return (0);
}

static int	search_down(char **dst, int x, int y, int for_char)
{
	int	i;

	i = y;
	while (dst[i] && dst[i][x] != WALL)
	{
		if (dst[i][x] == for_char)
			return (1);
		i++;
	}
	return (0);
}

static int	search_left(char **dst, int x, int y, int for_char)
{
	int	i;

	i = x;
	while (i >= 0 && dst[y][i] != WALL)
	{
		if (dst[y][i] == for_char)
			return (1);
		i--;
	}
	return (0);
}

static int	search_right(char **dst, int x, int y, int for_char)
{
	int	i;

	i = x;
	while (dst[y][i] && dst[y][i] != WALL)
	{
		if (dst[y][i] == for_char)
			return (1);
		i++;
	}
	return (0);
}

int	seeking(char **dst, int	x, int y, int for_char)
{
	int	ret;

	ret = 0;
	ret += search_down(dst, x, y, for_char);
	ret += search_up(dst, x, y, for_char);
	ret += search_left(dst, x, y, for_char);
	ret += search_right(dst, x, y, for_char);
	return (ret);
}