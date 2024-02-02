/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:19:19 by otaraki           #+#    #+#             */
/*   Updated: 2022/10/21 22:19:50 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)haystack;
	if (needle[i] == 0)
		return (str);
	if (!len)
		return (0);
	while (str[i] && (i < len))
	{
		j = 0;
		while (str[i + j] && str[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == 0)
			return (&str[i]);
		else
			i++;
	}
	return (NULL);
}
