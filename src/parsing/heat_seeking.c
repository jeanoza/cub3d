/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_seeking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:06:16 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 23:19:59 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_space(char **dst)
{
	int	x;
	int	y;

	y = 1;
	while (dst[y])
	{
		x = 1;
		while (dst[y][x])
		{
			if (dst[y][x] == SPACE && seeking(dst, x, y, OFFMAP))
				dst[y][x] = OFFMAP;
			else if (dst[y][x] == SPACE)
				dst[y][x] = VOID;
			x++;
		}
		y++;
	}
}

static int not_closed_map_error(int y, int x)
{
	ft_putstr_fd("Error\nMap isn't closed at line ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(" col ", 2);
	ft_putnbr_fd(x, 2);
	ft_putendl_fd("", 2);
	return (1);
}

int	check_void_offmap_seeker(char **dst)
{
	int	x;
	int	y;

	y = 1;
	while (dst[y])
	{
		x = 1;
		while (dst[y][x])
		{
			if ((dst[y][x] == VOID || is_valid(dst[y][x]) == 2)
				&& seeking(dst, x, y, OFFMAP))
				return (not_closed_map_error(y, x));
			x++;
		}
		y++;
	}
	return (0);
}
/*
	si sur ' ' set 0 or OFFMAP et refaire

	si sur 1 rien faire
	Si sur OFFMAP rien faire
	
	Si sur 0 forbiden is OFFMAP
	si sur N forb is OFFMAP



*/