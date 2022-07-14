/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/14 02:09:30 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		exit_error_file(NULL, 0);
	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		//print_game(game);
		//free_game(game);
		//init(game);
		//maxime(game);
	}
	else
		return (EXIT_FAILURE);
	free_game(game);
	return (EXIT_SUCCESS);
}
