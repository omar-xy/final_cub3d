/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:09:17 by otaraki           #+#    #+#             */
/*   Updated: 2022/10/22 02:04:12 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = (ft_strlen(str));
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (&str[i]);
		if (i == 0)
			return (NULL);
		i--;
	}
	return (NULL);
}
