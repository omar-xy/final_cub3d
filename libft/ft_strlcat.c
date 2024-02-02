/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:59:57 by otaraki           #+#    #+#             */
/*   Updated: 2022/11/03 00:43:39 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;
	size_t	j;

	j = 0;
	i = 0;
	if (dstsize)
	{
		dstlen = ft_strlen(dst);
		srclen = ft_strlen(src);
		if (dstsize < dstlen)
			return (dstsize + srclen);
		while (dst[i])
			i++;
		if (!dst[i])
		{
			while (src[j] && i < dstsize - 1)
				dst[i++] = src[j++];
			dst[i] = '\0';
		}
		return (dstlen + srclen);
	}
	return (ft_strlen(src));
}
