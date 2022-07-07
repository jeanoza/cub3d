/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/07 17:24:29 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init(t_game *game)
{
	//FIXME: this is example : 2nd and 3rd parametre have to be changed by input(parsing)
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1240, 720, "cub3d");
}

int	close_game_win_ctrl(t_game *game)
{
	if (mlx_destroy_window(game->mlx, game->win))
	{
		printf("Error\nDestroy window failed\n");
		free_game(game);
		exit(EXIT_FAILURE);
	}
	free_game(game);
	printf("Closed by win x button\n");
	exit(EXIT_SUCCESS);
}

// FIXME: version with parsing
int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		exit(EXIT_FAILURE);
	game = ft_calloc(1, sizeof(t_game));
	if (parse(av, game))
	{
		init(game);
		print_game(game);
		mlx_hook(game->win, EVENT_EXIT_WIN, 0, close_game_win_ctrl, game);
		mlx_loop(game->mlx);
	}

	return (EXIT_SUCCESS);
}




//FIXME: version to only exec
// void parse_a_la_rache(t_game *game)
// {
// 	int	fd;
// 	int	i,j;

// 	fd = open("./maps/basic.cub", O_RDONLY);
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, "NO", 2))
// 			game->no_path = line;
// 		else if (ft_strncmp(line, "SO", 2))
// 			game->so_path = line;
// 		else if (ft_strncmp(line, "WE", 2))
// 			game->we_path = line;
// 		else if (ft_strncmp(line, "EA", 2))
// 			game->ea_path = line;
// 		line = get_next_line(fd);
// 	}
// }

// int main(void)
// {
// 	t_game	*game;

// 	game = ft_calloc(1, sizeof(t_game));


// 	return (EXIT_SUCCESS);
// }