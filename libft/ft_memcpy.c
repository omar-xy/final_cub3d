/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:43:44 by otaraki           #+#    #+#             */
/*   Updated: 2022/10/21 21:51:47 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*dst;
	char	*src;

	dst = (char *)s1;
	src = (char *)s2;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (s1);
}
