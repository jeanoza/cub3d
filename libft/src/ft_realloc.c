/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kychoi <kychoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:12:21 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/05/26 15:16:03 by kychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function:  ft_realloc
 * --------------------
 * Create new void pointer and copy all memory of old pointer.
 * Then, free old pointer.
 *
 * Attention!!
 * Think well length of pointer
 * ex:
 * 	- If you use realloacte for add one char * in char **,
 *	- Usage will be like the next line:
 *		_new = ft_realloc(_old, sizeof(char *) * (ELEM_NUM_IN_OLD + 1)
 *							, sizeof(char *) * (ELEM_NUM_IN_OLD + 2))
 *	- As last element in table is NULL in general, you muste think about that
 * old_ptr: address of old pointer
 * old_len: length of old pointer (length * sizeof(ELEMENT_IN_TABLE))
 * new_len: length of new pointer (length * sizeof(ELEMENT_TO_PUT))
 * returns: ascii number of c if contains else 0
 */
void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len)
{
	char	*new_ptr;

	new_ptr = malloc(new_len);
	if (!new_ptr)
		return (NULL);
	ft_bzero(new_ptr, new_len);
	ft_memcpy(new_ptr, old_ptr, old_len);
	free(old_ptr);
	return (new_ptr);
}
