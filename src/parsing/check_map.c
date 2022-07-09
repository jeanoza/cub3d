/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:25:20 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 04:09:45 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid(int c)
{
	if (c == '1' || c == ' ' || c == '0')
		return (1);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (2);
	return (0);
}

static int	check_forbidden_char(t_game *game)
{
	int		i;
	int		j;
	int		nbr;
	char	**map;

	map = game->map;
	i = 0;
	nbr = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid(map[i][j]))
				return (-2);
			if (is_valid(map[i][j]) == 2)
				nbr++;
			j++;
		}
		i++;
	}
	return (nbr - 1);
}

static void	check_forb_char_player(t_game *game)
{
	int ret;
	int	err;

	err = 0;
	ret = check_forbidden_char(game);
	if (ret == -2 && ++err)
		ft_putstr_fd("Error\nForbidden char in map\n", 2);
	else if ((ret > 0 || ret == -1) && ++err)
		ft_putstr_fd("Error\nOnly 1 player needed\n", 2);
	if (err)
	{
		free_game(game);
		exit (1);
	}
}

///tmp
void	print_array(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}
void	free_array(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	check_map(t_game *game)
{
	char **tok_map;
	
	check_forb_char_player(game);
	tok_map = tokenize(game, game->map);
	(void)tok_map;
	print_array(tok_map);
	free_array(tok_map);
}