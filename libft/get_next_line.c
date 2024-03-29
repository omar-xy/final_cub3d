/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:44:52 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/03 01:23:31 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_to_line(int fd, char *line)
{
	char	*buff;
	int		rd_byt;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_byt = 1;
	while ((ft_strchr(line, '\n') == NULL) && rd_byt != 0)
	{
		rd_byt = read(fd, buff, BUFFER_SIZE);
		if (rd_byt == -1)
		{
			if (line)
				free(line);
			free(buff);
			return (NULL);
		}
		buff[rd_byt] = '\0';
		line = ft_strjoin_free(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*ret_valu;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_read_to_line(fd, line);
	if (!line)
		return (NULL);
	ret_valu = ft_get_line(line);
	line = ft_new_line(line);
	return (ret_valu);
}
