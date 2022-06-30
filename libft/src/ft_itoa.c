/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:49:36 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 14:39:46 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len_from_n(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (10);
	len = 0;
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

static void	ft_putnbr(char *str_n, int n, int i)
{
	if (n > 9)
		ft_putnbr(str_n, n / 10, i - 1);
	str_n[i] = (n % 10) + '0';
}

static char	*ft_strcpy(char *dst, char const *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_itoa(int n)
{
	char		*str_n;
	size_t		len;

	len = get_len_from_n(n);
	if (n < 0)
		++len;
	str_n = malloc(sizeof(char) * (len + 1));
	if (str_n)
	{
		if (n == -2147483648)
			ft_strcpy(str_n, "-2147483648");
		else
		{
			if (n < 0)
			{
				str_n[0] = '-';
				n = -n;
			}
			ft_putnbr(str_n, n, len - 1);
			str_n[len] = '\0';
		}
		return (str_n);
	}
	return (NULL);
}
/*
#include<stdio.h>
int main(void)
{
	char *str1 = ft_itoa(-2147483648);
	char *str2 = ft_itoa(-483648);
	printf("%s\n", str1);
	printf("%s\n", str2);
	free(str1);
	free(str2);
	// while (1);
	return (0);
}
*/