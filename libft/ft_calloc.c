/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 04:05:07 by otaraki           #+#    #+#             */
/*   Updated: 2022/11/03 15:54:27 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		*ptr;
	size_t	over;

	over = count * size;
	if (over != 0 && (over / count) != size)
		return (NULL);
	ptr = malloc(over);
	if (ptr != NULL)
		ft_bzero(ptr, over);
	return (ptr);
}
