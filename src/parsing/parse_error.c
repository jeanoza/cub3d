/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:40:34 by mabriel           #+#    #+#             */
/*   Updated: 2022/07/09 23:23:42 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid(int c)
{
	if (c == '1' || c == ' ' || c == '0')
		return (1);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (2);
	return (0);
}

int	forest_help(t_game *game, int code)
{
	int	i;

	i = 0;
	game->count += 1;
	if (code == 1 && game->no_path && ++i)
		game->err = 1;
	if (code == 2 && game->so_path && ++i)
		game->err = 1;
	if (code == 3 && game->we_path && ++i)
		game->err = 1;
	if (code == 4 && game->ea_path && ++i)
		game->err = 1;
	if (code == 5 && game->fcolor && ++i)
		game->err = 1;
	if (code == 6 && game->ccolor && ++i)
		game->err = 1;
	if (i)
	{
		ft_putstr_fd("Error\nDuplicated texture at line :", 2);
		ft_putnbr_fd(game->line, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

int	open_file(char *s, t_game *game)
{
	int	fd;
	
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		perror(s);
		free_game(game);
		exit(1);
	}
	return (fd);
}

void	error_parsing(t_error err_code, char *msg, t_game *game)
{
	if (err_code == ERR_LINE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("While parsing at line ", 2);
		ft_putnbr_fd(game->line, 2);
		ft_putstr_fd(" :[", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("]\n", 2);
		free(msg);
		if (game->count < 7)
			ft_putstr_fd("MISSING OR DISORGANIZED TEXTURE\n", 2);
	}
	if (err_code == ERR_MAP)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("While parsing at line ", 2);
		ft_putnbr_fd(game->line - *msg, 2);
		ft_putstr_fd("\nEmpty line in map\n", 2);
		free_game(game);
		exit(1);
	}
	game->err = 1;
}

void	exit_error_file(t_game *game, int err_code)
{
	if (err_code == 1)
	{
		ft_putstr_fd("Error\nInvalid file extention (must be .cub)\n", 2);
		free_game(game);
	}
	if (err_code == 0)
		ft_putstr_fd("Error\nOne file needed\n", 2);
	exit(1);
}
