/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriel <mabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 23:00:40 by mabriel           #+#    #+#             */
/*   Updated: 2022/05/31 23:00:56 by mabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	do_pwd(void)
{
	char	s[4096];

	if (getcwd(s, 4096))
	{
		printf("%s\n", s);
		return (0);
	}
	else
	{
		ft_putstr_fd("Error locating current directory\n", 2);
		return (1);
	}
}
