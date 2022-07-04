/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:08:13 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/07/04 23:55:32 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_game(t_game *game)
{
	int i;

	printf("\n[%p]game\n", game);
	printf("\n  [%p]game->mlx\n", game->mlx);
	printf("\n  [%p]game->win\n", game->win);
	printf("\n  [%p]game->player\n", game->player);
	printf("\n  [%p]game->map:\n", game->map);
	i = 0;
	while (game->map && game->map[i])
	{
		printf("    [%p]game->map[%d]%s", game->map[i], i, game->map[i]);
		++i;
	}
}


//TODO: change to CUBE\n3D
void	put_header(void)
{
	printf(
		MAG"/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */\n\n"
		RED"     .^. .  _    \n"
		YEL"    /: ||`\\/ \\\\~  ,       \n"
		GRN"  , [   &    / \\ y'      ###   ###  ####   ###    #  ####   \n"
		CYN" {v':   `\\   / `&~-,    #  # #  #    #    #  #   #    #    \n"
		BLU"'y. '    |`   .  ' /   #   #   #    #    #   #  #    # \n"
		MAG" \\   '  .       , y   #       #   ####  #    ###   #### \n"
		RED" v .        '     v   \n"
		YEL" V  .~.      .~.  V    ######  #     # ###### #      # \n"
		GRN" : (  0)    (  0) :   /_____  #_____# #_____ #      # \n"
		CYN"  i `'`      `'` j         / #     # #      #      # \n"
		BLU"   i     __    ,j    ###### #     # ###### ###### ###### \n"
		MAG"    `\\%%`~....~'&         \n"
		RED" <~o' /  \\/` \\-s,                This is NOT a big shell \n"
		YEL"  o.~'.  )(  r  .o ,.  \n"
		GRN" o',  %%``\\/``& : 'bF  \n"
		CYN"d', ,ri.~~-~.ri , +h  \n"
		BLU"`oso' d`~..~`b 'sos`                          Created by \n"
		MAG"     d`+ II +`b                       mabriel and kychoi \n"
		RED"     i_:_yi_;_y                              at 42 Paris \n\n"
		YEL"/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */\n"
		GRN);
}

//RED -> YEL -> GRN -> CYN -> BLU -> MAG
/*

   ###   ###  ####   ###    #  ####   
  #  # #  #    #    #  #   #    #    
 #   #   #    #    #   #  #    #  
#       #   ####  #    ###   #### 

    ######   #    # #####  #      #
   /_____   #____# #____  #      #
        /  #    # #      #      #
  ######  #    # ###### ###### ######

              This is NOT a big shell



                           Created by
		           mabriel and kychoi
				          at 42 Paris
						  
*/