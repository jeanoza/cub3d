/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:46:19 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 14:48:16 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}
/*
#include <stdio.h>
int main(void)
{
	t_list	*lst1 = ft_lstnew((void *)"first");
	t_list	*lst2 = ft_lstnew((void *)"second");
	t_list	*lst3 = ft_lstnew((void *)"third");

	lst1->next = lst2;
	lst2->next = lst3;
	printf("result:%d\n", ft_lstsize(lst1));
	return (0);
}
*/