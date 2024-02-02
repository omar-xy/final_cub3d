/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:44:07 by otaraki           #+#    #+#             */
/*   Updated: 2023/12/06 18:36:43 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	dst = (char *)s;
	while (dst[i])
	{
		if (dst[i] == (char)c)
			return (&dst[i]);
		i++;
	}
	if (dst[i] == (char)c)
		return (&dst[i]);
	return (NULL);
}
