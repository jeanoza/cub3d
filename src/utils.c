/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:08:35 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 15:48:45 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	index_of(char *str, char to_find)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == to_find)
			return (i);
		++i;
	}
	return (-1);
}
