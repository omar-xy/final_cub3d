/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:17:41 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/03 23:58:24 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

t_ren	init_struct(t_cub *cub, double angle_ray)
{
	t_ren	r;
	
	r.distance_to_wall = get_ray_length(cub, angle_ray) * cos(angle_ray - cub->player.angle);
	r.wall_projection = (cub->mlx->width / 2) / tan(30 * M_PI / 180);
	r.wall = ( 64 / r.distance_to_wall) * r.wall_projection;
	r.start = (cub->mlx->height / 2) - (r.wall / 2);
	return (r);
}

void	put_ceiling(t_cub *cub, t_ren r, int *i, int j)
{
	while (*i < r.start)
	{
		if (*i < cub->mlx->height && j < cub->mlx->width && *i > 0 && j > 0)
		{
			mlx_put_pixel(cub->img, j, *i, rgb(cub->map.ceiling.r, cub->map.ceiling.g, cub->map.ceiling.b, 255));
		}
		(*i)++;
	}
}

void	put_floor(t_cub *cub, int *i, int j)
{
	while (*i < cub->mlx->height)
	{
		if (*i < cub->mlx->height && j < cub->mlx->width && *i > 0 && j > 0)
		{
			mlx_put_pixel(cub->img, j, *i, rgb(cub->map.floor.r, cub->map.floor.g, cub->map.floor.b, 255));
		}
		(*i)++;
	}
}
