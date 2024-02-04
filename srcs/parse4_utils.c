/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:39:50 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/04 03:48:13 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	set_color(t_cub *cub, char **str, char flag)
{
	if (flag == 'F' || flag == 'C')
	{
		if ((ft_atoi(str[0]) < 0 || ft_atoi(str[0]) > 255) \
			|| (ft_atoi(str[1]) < 0 || ft_atoi(str[1]) > 255) \
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
	return (1);
}

void	calculate_map_size(t_cub *cub)
{
	int		i;
	int		j;
	int		max_width;

	i = 0;
	max_width = 0;
	while (cub->map.info[i])
		i++;
	cub->map.height = i;
	i = 0;
	while (cub->map.info[i])
	{
		j = 0;
		while (cub->map.info[i][j])
			j++;
		if (j > max_width)
			max_width = j;
		i++;
	}
	cub->map.width = max_width;
}

void	fill_empty_spaces(t_cub *cub)
{
	char	**map;
	int		i;
	int		j;

	map = cub->map.info;
	i = -1;
	while (map[++i])
	{
		j = ft_strlen(map[i]);
		while (j < cub->map.width)
		{
			cub->map.info[i] = ft_strjoin_free(map[i], " ");
			j++;
		}
	}
}

void free_path(t_cub *cub)
{
	char	*s;
	char	*e;
	char	*w;
	char	*n;
	
	s = cub->map.so_img->path;
	e = cub->map.ea_img->path;
	w = cub->map.we_img->path;
	n = cub->map.no_img->path;
	free(s);
	free(e);
	free(w);
	free(n);
}

int	ft_error(t_cub *cub, char *str)
{

	if (str)
		ft_putstr_fd(str, 2);
	if (cub != NULL)
	{
		if (cub->map.info)
			free_towd(cub->map.info);
		free_path(cub);
		free(cub->map.so_img->img);
		free(cub->map.ea_img->img);
		free(cub->map.we_img->img);
		free(cub->map.no_img->img);
		free(cub->map.so_img);
		free(cub->map.ea_img);
		free(cub->map.we_img);
		free(cub->map.no_img);
	}
	return (0);
}
