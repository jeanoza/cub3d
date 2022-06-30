/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:04:51 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 14:45:59 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
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
	printf("result:%s\n", (char *)(ft_lstlast(NULL)->content));
	return (0);
}
*/