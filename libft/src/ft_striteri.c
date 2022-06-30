/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:50:45 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 12:14:50 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			f(i, &s[i]);
			++i;
		}
	}
}
/*
#include <stdio.h>
void	ft_toupper_test(unsigned int index, char *s)
{
	if (s[index] >= 'a' && s[index] <= 'z')
		s[index] -= 32;
}
int main(void)
{
	char	test_str[100] = "hello";
	ft_striteri(test_str, &ft_toupper_test);
	printf("result:%s\n", test_str);
	return (0);
}
*/