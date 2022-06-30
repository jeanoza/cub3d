/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:08:13 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/12 14:54:29 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_res_parsing(t_cmd **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds && cmds[i])
	{
		printf("	cmd[%d]->name: `%s`\n", i, cmds[i]->name);
		j = 0;
		while (cmds[i]->args && cmds[i]->args[j])
		{
			printf("\t- args[%d]: `%s`\n", j, cmds[i]->args[j]);
			++j;
		}
		j = 0;
		while (cmds[i]->redirs && cmds[i]->redirs[j])
		{
			printf("\t\t- redirs[%d]->op: `%d`\n", j, cmds[i]->redirs[j]->op);
			printf("\t\t- redirs[%d]->file: `%s`\n", j, cmds[i]->redirs[j]->file);
			++j;
		}
		++i;
	}
}

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