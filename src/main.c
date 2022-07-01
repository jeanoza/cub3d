/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:27:41 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/01 16:31:40 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Function:  parse
 * --------------------------------------------------------------------------
 * Verify line is validate or not by parse_error function.
 * returns:	NULL | [t_map *map1, t_map *map2...,]
 */
t_map	**parse(int ac, char **av)
{
	int	fd;
	char *line;
	int	i;

	if (ac != 2)
		return (NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
		{
			printf("%c(%d) ", line[i], line[i]);
			++i;
		}
		printf("\n");
		line = get_next_line(fd);
	}
	return (0);
}

int	main(int ac, char **av)
{

	if (parse(ac, av))
	{
		//e

	}
	return (0);
}