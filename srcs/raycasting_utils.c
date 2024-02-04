/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:30:58 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/04 00:15:06 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	checks_for_horizontal(t_cub *cub, double angle_ray)
{
	if (tan(angle_ray) == 0)
		cub->ray.deltax = 64;
	else
		cub->ray.deltax = 64 / tan(angle_ray);
	cub->ray.deltay = 64;
	if (cub->ray.up_or_down == 1)
		cub->ray.deltay *= -1;
	if (cub->ray.right_or_left == 0 && cub->ray.deltax > 0)
		cub->ray.deltax *= -1;
	if (cub->ray.right_or_left == 1 && cub->ray.deltax < 0)
		cub->ray.deltax *= -1;
}

void	checks_for_vertical(t_cub *cub, double angle_ray)
{
	cub->ray.deltax = 64;
	cub->ray.deltay = 64 * tan(angle_ray);
	if (cub->ray.right_or_left == 0)
		cub->ray.deltax *= -1;
	if (cub->ray.up_or_down == 1 && cub->ray.deltay > 0)
		cub->ray.deltay *= -1;
	if (cub->ray.up_or_down == 0 && cub->ray.deltay < 0)
		cub->ray.deltay *= -1;
}

void	raycaster(t_cub *cub)
{
	int		window_width;
	double	mini_angle;
	double	angle_ray;
	int		j;

	window_width = cub->mlx->width;
	mini_angle = FOV_ANGLE / window_width;
	angle_ray = normalize_angle(cub->player.angle - (FOV_ANGLE / 2));
	j = 0;
	while (j < window_width)
	{
		rendering(cub, angle_ray, j);
		angle_ray = normalize_angle(mini_angle + angle_ray);
		j++;
	}
}

double	get_ray_length(t_cub *cub, double angle_ray)
{
	cub->ray.horizontal_hit = false;
	cub->ray.vertical_hit = false;
	cub->ray.h_dis = horizontal_inter(cub, angle_ray);
	cub->ray.v_dis = vertical_inter(cub, angle_ray);
	if (cub->ray.h_dis > cub->ray.v_dis)
	{
		cub->ray.vertical_hit = true;
		return (cub->ray.v_dis);
	}
	cub->ray.horizontal_hit = true;
	return (cub->ray.h_dis);
}
