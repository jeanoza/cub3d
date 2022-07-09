/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/09 15:38:56 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		exit(EXIT_FAILURE);
	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		init(game);
	}

	return (EXIT_SUCCESS);
}
