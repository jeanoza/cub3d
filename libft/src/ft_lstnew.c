/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:22:02 by kychoi            #+#    #+#             */
/*   Updated: 2021/12/02 14:48:05 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->content = content;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	t_list	*list;

	list = ft_lstnew("hello");
	printf("content: %s\n", (char *)list->content);
	return (0);
}
*/