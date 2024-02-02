/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:42:41 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/19 18:41:00 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)// check if nuLL
{
	char	*p;

	p = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, ft_strlen(s1) + 1);
	return (p);
}
