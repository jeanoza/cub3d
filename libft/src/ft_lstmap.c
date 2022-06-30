/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:30:08 by kyubongchoi       #+#    #+#             */
/*   Updated: 2021/12/02 14:47:02 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;

	(void)del;
	if (lst)
	{
		new_list = ft_lstnew(f(lst->content));
		lst = lst->next;
		while (lst)
		{
			ft_lstadd_back(&new_list, ft_lstnew(f(lst->content)));
			lst = lst->next;
		}
		return (new_list);
	}
	return (NULL);
}
/*
static	void	*ft_str_toupper(void *str)
{
	int	i;
	char	*new_str;

	new_str = malloc(sizeof(char) * ft_strlen((char *)str) + 1);
	i = 0;
	while (((char *)str)[i])
	{
		new_str[i] = ft_toupper(((char *)str)[i]);
		++i;
	}
	new_str[i] = 0;
	return (new_str);
}

#include<stdio.h>
int	main(void)
{
	t_list	*list;
	t_list	*new_list;

	list = ft_lstnew("test1");
	list->next = ft_lstnew("test2");
	list->next->next = ft_lstnew("test3");
	new_list = ft_lstmap(list, ft_str_toupper, free);
	while (new_list)
	{
		printf("%s\n", (char *)new_list->content);
		new_list = new_list->next;
	}
	// while (1);
	return (0);
}
*/