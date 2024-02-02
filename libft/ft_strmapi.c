/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:27:03 by otaraki           #+#    #+#             */
/*   Updated: 2022/11/02 21:03:02 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*target;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	target = (char *)malloc(len_s + 1 * sizeof(char));
	if (!target)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		target[i] = f(i, s[i]);
		i++;
	}
	target[i] = '\0';
	return (target);
}
