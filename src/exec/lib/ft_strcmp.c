/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:15:10 by mabriel           #+#    #+#             */
/*   Updated: 2022/02/17 17:15:30 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strcmp(char *s, char *d)
{
	size_t	i;

	i = 0;
	if (!s || !d)
		return (0);
	while (s[i] && d[i] && s[i] == d[i])
		i++;
	if (i == ft_strlen(s) && ft_strlen(s) == ft_strlen(d))
		return (1);
	return (0);
}
