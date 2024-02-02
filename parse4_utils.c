/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:39:50 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 22:09:38 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

int set_color(t_cub *cub, char **str, char flag)
{
	if (flag == 'F' || flag == 'C')
	{
		if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255)\
			|| (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255)\
			|| (ft_atoi(str[2]) < 0 || ft_atoi(str[2]) > 255))
			return (0);
		if (flag == 'F')
		{
			cub->map.floor.floor = "F";
			cub->map.floor.r = ft_atoi(str[0]);
			cub->map.floor.g = ft_atoi(str[1]);
			cub->map.floor.b = ft_atoi(str[2]);
		}
		else
		{
			cub->map.ceiling.ceiling = "C";
			cub->map.ceiling.r = ft_atoi(str[0]);
			cub->map.ceiling.g = ft_atoi(str[1]);
			cub->map.ceiling.b = ft_atoi(str[2]);
		}
	}
	return 1;
}


void    calculate_map_size(t_cub *cub)
{
	int i;
	int j;
	int max_width;

	i = 0;
	max_width = 0;
	while (cub->map.store_map[i])
		i++;
	cub->map.height = i;
	i = 0;
	while(cub->map.store_map[i])
	{
		j = 0;
		while(cub->map.store_map[i][j])
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	cub->map.width = max_width;
}

void fill_empty_spaces(t_cub *cub)
{
	int i;
	int j;
	char **map;

	map = cub->map.store_map;
	i = -1;
	while(map[++i])
	{
		j = ft_strlen(map[i]);
		while(j < cub->map.width)
		{
			cub->map.store_map[i] = ft_strjoin_free(map[i], " ");
			j++;
		}
	}
}

int	ft_error(t_cub *cub, char *str)
{
	char	*s;
	char	*e;
	char	*w;
	char	*n;

	if (str)
		ft_putstr_fd(str, 2);
	if (cub != NULL)
	{
		s = cub->map.so_path;
		e = cub->map.ea_path;
		w = cub->map.we_path;
		n = cub->map.no_path;
		if (cub->map.store_map)
			free_towd(cub->map.store_map);
		free(s);
		free(e);
		free(w);
		free(n);
		cub->map.so_path = NULL;
		cub->map.ea_path = NULL;
		cub->map.we_path = NULL;
		cub->map.no_path = NULL;
	}
	return (0);
}