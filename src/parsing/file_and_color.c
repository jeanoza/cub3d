/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_and_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 06:54:18 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/20 18:25:48 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_color(char **s, t_game *game)
{
	int		i;
	int		tmp;
	char	*tm;

	i = 0;
	check_textures_extention(game, *s);
	while ((*s)[i] >= 'A' && (*s)[i] <= 'Z')
		i++;
	if ((*s)[i] != ' ')
	{
		ft_putstr_fd("Error\nMissing space in textures\n", 2);
		free_game(game);
		exit(1);
	}
	while ((*s)[i] == ' ')
		i++;
	tmp = open_file(*s + i, game);
	close(tmp);
	tm = *s;
	*s = ft_strdup(*s + i);
	free(tm);
}

static char	*trim_spl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != ' ')
			return (NULL);
		i++;
	}
	i = 0;
	while (s[i] == ' ')
		i++;
	return (s + i);
}

static int	check_range(char **sp)
{
	char	*tmp;
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (sp[i])
	{
		tmp = ft_itoa(ft_atoi(sp[i]));
		if (!trim_spl(sp[i]) || strncmp(tmp, trim_spl(sp[i]), ft_strlen(tmp))
			|| (ft_atoi(sp[i]) < 0 || ft_atoi(sp[i]) > 255))
			err = 1;
		free(tmp);
		i++;
	}
	if (err == 1)
		ft_putstr_fd("Error\nColor out of range\n", 2);
	if (i != 3)
		ft_putstr_fd("Error\nExactly 3 attributes are needed\n", 2);
	if (err || i != 3)
		return (1);
	return (0);
}

static void	check_floor_ceil(t_game *game, char *s, char **spl)
{
	int	i;

	i = 0;
	while (s[i] >= 'A' && s[i] <= 'Z')
		i++;
	if (s[i] != ' ')
	{
		ft_putstr_fd("Error\nMissing space in color\n", 2);
		free_2d_array((void **)spl);
		free_game(game);
		exit(1);
	}
	if (check_range(spl))
	{
		free_2d_array((void **)spl);
		free_game(game);
		exit(1);
	}
	free_2d_array((void **)spl);
}

void	check_file_and_color(t_game *game)
{
	char	**spl;

	if ((game->ccolor)[ft_strlen(game->ccolor) - 1] == ','
		|| (game->fcolor)[ft_strlen(game->fcolor) - 1] == ',')
	{
		ft_putstr_fd("Error\nExactly 3 attributes are needed\n", 2);
		free_game(game);
		exit(1);
	}
	if (check_digit(game->ccolor) || check_digit(game->fcolor))
	{
		ft_putstr_fd("Error\nForbidden char in color\n", 2);
		free_game(game);
		exit(1);
	}
	spl = put_floor_ceil(game, game->ccolor);
	check_floor_ceil(game, game->ccolor, spl);
	spl = put_floor_ceil(game, game->fcolor);
	check_floor_ceil(game, game->fcolor, spl);
	trim_color(&game->no_path, game);
	trim_color(&game->ea_path, game);
	trim_color(&game->we_path, game);
	trim_color(&game->so_path, game);
}
