/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:39:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/03/22 23:57:09 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim( char const *s1, char const *set)
{
	char	*dst;
	size_t	idx;
	size_t	i;
	size_t	j;
	size_t	len_s1;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	i = 0;
	while (i < len_s1 && ft_strchr(set, s1[i]))
		i++;
	j = len_s1;
	while (j >= 0 && ft_strchr(set, s1[j - 1]) && j > i)
		j--;
	dst = (char *)malloc(j - i + 1);
	if (!dst)
		return (NULL);
	idx = 0;
	while (i < j)
		dst[idx++] = s1[i++];
	dst[idx] = '\0';
	return (dst);
}
