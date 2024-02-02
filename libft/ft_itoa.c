/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:17:09 by otaraki           #+#    #+#             */
/*   Updated: 2022/11/03 21:37:28 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_n(int n)
{
	int			i;
	int			s;
	long long	nb;

	i = 0;
	nb = (long long)n;
	s = -1;
	if (nb <= 0)
	{
		nb = nb * s;
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*ft_checkcheck(char	*ptr, int len, long long num)
{
	if (num < 0)
	{
		ptr[0] = '-';
		num *= -1;
		while (--len != 0)
		{
			ptr[len] = '0' + num % 10;
			num /= 10;
		}
		return (ptr);
	}
	while (len-- != 0)
	{
		ptr[len] = '0' + num % 10;
		num /= 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			len;
	long long	num;

	len = ft_len_n(n);
	num = (long long)n;
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_checkcheck(ptr, len, num));
}
