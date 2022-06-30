/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:46:46 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/28 17:20:23 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}
/*
#include<stdio.h>
int main(void)
{
	t_list	*l = ft_lstnew(ft_strdup("test1"));
	l->next = ft_lstnew(ft_strdup("test2"));
	printf("l->content			:%p\n", l->content);
	printf("(l->next)	:%p\n", (l->next)->content);
	ft_lstclear(&l, free);
	printf("l->content			:%p\n", l->content);
	printf("(l->next)	:%p\n", (l->next)->content);
	return (0);
}
*/