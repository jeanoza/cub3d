/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:10:02 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 13:25:27 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_map(t_game *game, char *line, int idx)
{
	if (game->map == NULL)
		game->map = ft_calloc(2, P_SIZE);
	else
		game->map = ft_realloc(game->map,
				(idx + 1) * P_SIZE, (idx + 2) * P_SIZE);
	(game->map)[idx] = line;
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

void	put_floor_ceil(t_game *game, char *line)
{

		if (line[0] == 'F')
		{
			game->f_color = line;
		}
		else if (line[0] == 'C')
		{
			game->c_color = line;
		}
	// char	**splitted;
	// int		i;
	// splitted = ft_split(line + 2, ',');
	// if (line[0] == 'F')
	// 	game->f_color = ft_calloc(4, sizeof(int));
	// else if (line[0] == 'C')
	// 	game->c_color = ft_calloc(4, sizeof(int));
	// i = 0;
	// while (i < 3)
	// {
	// 	if (line[0] == 'F')
	// 	{
	// 		printf("if\n");
	// 		game->f_color[i] = ft_atoi(splitted[i]);
	// 	}
	// 	else if (line[0] == 'C')
	// 	{
	// 		printf("else if\n");
	// 		game->c_color[i] = ft_atoi(splitted[i]);
	// 	}
	// 	++i;
	// }
	// free(splitted);
}
