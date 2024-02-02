/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:13:08 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 10:57:01 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char *s, char c)
{
	int	wc;
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	wc = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
		wc++;
	}
	return (wc);
}

static size_t	word_len(char *str, char del)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != del)
		i++;
	return (i);
}

static void	ft_clear(char **buff)
{
	size_t	i;

	i = 0;
	if (buff != NULL)
	{
		while (buff[i])
		{
			free(buff[i]);
			i++;
		}
	}
	free(buff);
}

static char	**alloc_for_words(char *s, char c, char **res)
{
	int	wc;
	int	wl;
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	wc = 0;
	while (s[i])
	{
		wl = word_len(&s[i], c);
		res[wc] = ft_substr(s, i, wl);
		if (!res[wc])
			return (ft_clear(res), NULL);
		i += wl;
		while (s[i] == c && s[i])
			i++;
		wc++;
	}
	res[wc] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**res;
	char	*target;

	if (!s)
		return (NULL);
	target = (char *)s;
	i = count_word(target, c);
	res = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!res)
		return (NULL);
	alloc_for_words(target, c, res);
	return (res);
}
