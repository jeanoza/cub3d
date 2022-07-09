/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:10:02 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/10 00:24:42 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_map(t_game *game, char *line, int idx)
{
	int	len;

	if (game->map == NULL)
		game->map = ft_calloc(2, P_SIZE);
	else
		game->map = ft_realloc(game->map,
				(idx + 1) * P_SIZE, (idx + 2) * P_SIZE);
	(game->map)[idx] = line;
	len = ft_strlen(line);
	if (len > game->width)
		game->width = len;
	++game->height;
	return (idx + 1);
}

void	put_texture(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		game->no_path = line;
	else if (ft_strncmp(line, "SO", 2) == 0)
		game->so_path = line;
	else if (ft_strncmp(line, "WE", 2) == 0)
		game->we_path = line;
	else if (ft_strncmp(line, "EA", 2) == 0)
		game->ea_path = line;
}

char	**put_floor_ceil(t_game *game, char *line)
{
	char	**splitted;
	int		encoded_color;

	splitted = ft_split(line + 2, ',');
	encoded_color = encode_rgb(ft_atoi(splitted[0]),
			ft_atoi(splitted[1]), ft_atoi(splitted[2]));
	if (line[0] == 'F')
		game->f_color = encoded_color;
	else if (line[0] == 'C')
		game->c_color = encoded_color;
	return (splitted);
}
