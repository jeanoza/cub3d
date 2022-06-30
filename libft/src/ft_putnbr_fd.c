/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:50:22 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 09:45:44 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd((n % 10 + 48), fd);
}
/*
int main(int ac, char **av)
{
	int	fd;

	(void)ac;
	fd = open("./test/test.txt", O_WRONLY);
	ft_putnbr_fd(atoi(av[1]), fd);
	close(fd);
	return (0);
}
*/