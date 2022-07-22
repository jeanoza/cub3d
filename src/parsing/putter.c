/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 12:10:02 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/22 20:37:31 by mabriel          ###   ########.fr       */
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

static int	check_digits(char *s)
{
	int	i;

	i = 0;
	while (!ft_isdigit(s[i]))
		i++;
	while (ft_isdigit(s[i]))
		i++;
	while (1)
	{
		if (s[i] == 0 || s[i] == ',')
			break ;
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	check_splitt(char **split, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (!ft_isdigit(split[i][j]))
			j++;
		if (check_digits(split[i] + j))
		{
			free_2d_array((void **)split);
			ft_putstr_fd("Error\nColor error\n", 2);
			free_game(game);
			exit(1);
		}
		i++;
	}
}

char	**put_floor_ceil(t_game *game, char *line)
{
	char	**splitted;
	int		encoded_color;

	if (line[1] != ' ')
	{
		ft_putstr_fd("Error\nMissing space in textures\n", 2);
		free_game(game);
		exit(1);
	}
	splitted = ft_split(line + 2, ',');
	if (!splitted[0] || !splitted[1] || !splitted[2])
	{
		free_2d_array((void **)splitted);
		ft_putstr_fd("Error\nMissing one RGB value in color\n", 2);
		free_game(game);
		exit(1);
	}
	check_splitt(splitted, game);
	encoded_color = encode_rgb(ft_atoi(splitted[0]),
			ft_atoi(splitted[1]), ft_atoi(splitted[2]));
	if (line[0] == 'F')
		game->f_color = encoded_color;
	else if (line[0] == 'C')
		game->c_color = encoded_color;
	return (splitted);
}

void	check_textures_extention(t_game *game, char *s)
{
	if (check_extension(s, ".xpm"))
	{
		ft_putstr_fd("Error\nBad extention for texture (must be .xpm)\n", 2);
		free_game(game);
		exit(1);
	}
}
