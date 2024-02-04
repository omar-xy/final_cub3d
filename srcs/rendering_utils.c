/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 08:17:41 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/04 14:42:39 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init_struct(t_cub *cub, t_ren *ren, double angle_ray, t_img *img)
{
	ren->distance_to_wall = get_ray_length(cub, angle_ray) * \
	cos(angle_ray - cub->player.angle);
	ren->wall_projection = (cub->mlx->width / 2) / tan(30 * M_PI / 180);
	ren->wall = (64 / ren->distance_to_wall) * ren->wall_projection;
	ren->start = (cub->mlx->height / 2) - (ren->wall / 2);
	if (cub->ray.vertical_hit == true)
		ren->ratio = (cub->ray.yv / 64 - (int)(cub->ray.yv / 64)) * img->width;
	else if (cub->ray.horizontal_hit == true)
		ren->ratio = (cub->ray.xh / 64 - (int)(cub->ray.xh / 64)) * img->width;
}

void	put_ceiling(t_cub *cub, t_ren r, int *i, int j)
{
	while (*i < r.start)
	{
		if (*i < cub->mlx->height && j < cub->mlx->width && *i > 0 && j > 0)
		{
			mlx_put_pixel(cub->img, j, *i, \
			rgb(cub->map.ceiling.r, cub->map.ceiling.g, \
			cub->map.ceiling.b, 255));
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
			mlx_put_pixel(cub->img, j, *i, \
			rgb(cub->map.floor.r, cub->map.floor.g, cub->map.floor.b, 255));
		}
		(*i)++;
	}
}
