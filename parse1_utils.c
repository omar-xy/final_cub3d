/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:03:19 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 22:08:31 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void	store_clr(t_cub *cub, char **str, char h)
{
	char	*trimed_str;
	int		bool_color;
	char	*tmp;

	bool_color = 0;
	tmp = *str;
	trimed_str = ft_strtrim(&tmp[2], " ");
	bool_color = parse_color(cub, trimed_str, h);
	if (bool_color == 0)
	{
		free(trimed_str);
		ft_error(cub, "Error: in color\n");
		exit(0);
	}
	free(trimed_str);
}

int	store_textures(t_cub *cub, char *line)
{
	char	*str;

	str = ft_strtrim(line, "\n");
	if (!str)
		return (0);
	if (!ft_strncmp(str, "NO ", 3))
		cub->map.no_path = ft_strtrim(&str[2], " ");
	else if (!ft_strncmp(str, "SO ", 3))
		cub->map.so_path = ft_strtrim(&str[2], " ");
	else if (!ft_strncmp(str, "WE ", 3))
		cub->map.we_path = ft_strtrim(&str[2], " ");
	else if (!ft_strncmp(str, "EA ", 3))
		cub->map.ea_path = ft_strtrim(&str[2], " ");
	else if (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
	{
		if (!ft_strncmp(str, "F ", 2))
			store_clr(cub, &str, 'F');
		else
			store_clr(cub, &str, 'C');
	}
	else
		return (free(str), ft_error(cub, "Error: in map\n"));
	return (free(str), 1);
}

bool	detect_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] == '1')
		return (true);
	return (false);
}

int	check_textures(t_cub *cub)
{
	if (!cub->map.no_path || !cub->map.so_path \
		|| !cub->map.we_path || !cub->map.ea_path \
		|| !cub->map.floor.floor || !cub->map.ceiling.ceiling)
		return (0);
	if (open(cub->map.no_path, O_RDONLY) < 0 \
		|| open(cub->map.so_path, O_RDONLY) < 0 \
		|| open(cub->map.we_path, O_RDONLY) < 0 \
		|| open(cub->map.ea_path, O_RDONLY) < 0)
		return (0);
	return (1);
}
