/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:50:26 by kychoi            #+#    #+#             */
/*   Updated: 2022/01/28 13:58:07 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}
/*
int main(int ac, char **av)
{
	int	fd;

	(void)ac;
	fd = open("./test/test.txt", O_WRONLY);
	ft_putstr_fd(av[1], fd);
	close(fd);
	return (0);
}
*/