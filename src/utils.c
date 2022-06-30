/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:38:59 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/06/16 14:47:24 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_2d_array(void **_2d_array)
{
	int	i;

	if (!_2d_array)
		return ;
	i = 0;
	while (_2d_array && _2d_array[i])
	{
		free(_2d_array[i]);
		++i;
	}
	free(_2d_array);
}

void	merci_encore_norm(char **strp, char *left, char *right)
{
	free(*strp);
	*strp = NULL;
	*strp = ft_strjoin_free_all(left, right);
}

int	count_el(void **_2d_array)
{
	int	i;

	i = 0;
	while (_2d_array && _2d_array[i])
	{
		++i;
	}
	return (i);
}

/*
 * Function:  contains
 * --------------------
 * Verify if c exist in charset entry.
 *			
 * charset: entry of characters to compare with c
 * c: character given
 * returns: ascii number of c if contains else 0
 */
int	contains(const char *charset, char c)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (c);
		++i;
	}
	return (0);
}

/*
 * Function:  is_redir_op
 * --------------------
 * Verify if c is redirection operator('<' | '>' | '|')
 *			
 * c: character given
 * returns: 1 if contains else 0
 */
int	is_redir_op(char c)
{
	if (contains(CHAR_OP, c))
		return (1);
	return (0);
}
