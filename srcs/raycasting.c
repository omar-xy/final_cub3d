/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:23:30 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/04 14:40:56 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

double	horizontal_inter(t_cub *cub, double angle_ray)
{
	double	xa;
	double	ya;
	double	y;

	check_directions(cub, angle_ray);
	if (cub->ray.up_or_down == 1)
		y = -1;
	else
		y = 1;
	ya = (int)cub->player.y - ((int)cub->player.y % 64);
	if (cub->ray.up_or_down == 0)
		ya += 64;
	xa = cub->player.x + (ya - cub->player.y) / tan(angle_ray);
	if (is_wall(cub, xa, ya + y))
		return (cub->ray.xh = xa, cub->ray.yh = ya,
			distance(xa, cub->player.x, ya, cub->player.y));
	checks_for_horizontal(cub, angle_ray);
	while (is_wall(cub, xa, ya + y) != 1)
	{
		xa += cub->ray.deltax;
		ya += cub->ray.deltay;
	}
	cub->ray.xh = xa;
	cub->ray.yh = ya;
	return (distance(xa, cub->player.x, ya, cub->player.y));
}

double	vertical_inter(t_cub *cub, double angle_ray)
{
	double	xa;
	double	ya;
	double	x;

	check_directions(cub, angle_ray);
	if (cub->ray.right_or_left == 1)
		x = 1;
	else
		x = -1;
	xa = (int)cub->player.x - ((int)cub->player.x % 64);
	if (cub->ray.right_or_left == 1)
		xa += 64;
	ya = cub->player.y + (xa - cub->player.x) * tan(angle_ray);
	if (is_wall(cub, xa + x, ya) != 0)
		return (cub->ray.xv = xa, cub->ray.yv = ya,
			distance(xa, cub->player.x, ya, cub->player.y));
	checks_for_vertical(cub, angle_ray);
	while (is_wall(cub, xa + x, ya) != 1)
	{
		xa += cub->ray.deltax;
		ya += cub->ray.deltay;
	}
	cub->ray.xv = xa;
	cub->ray.yv = ya;
	return (distance(xa, cub->player.x, ya, cub->player.y));
}

void	rendering(t_cub *cub, double angle_ray, int j)
{
	int		i;
	int		w_w;
	int		w_h;
	t_img	*img;

	i = 0;
	img = init_img(cub);
	w_w = cub->mlx->width;
	w_h = cub->mlx->height;
	init_struct(cub, &cub->ren, angle_ray, img);
	put_ceiling(cub, cub->ren, &i, j);
	while (i < cub->ren.start + cub->ren.wall)
	{
		if (i < w_h && j < w_w && i > 0 && j > 0)
		{
			cub->ren.n_ratio = (i - cub->ren.start) * \
			((double)img->height / cub->ren.wall);
			mlx_put_pixel(cub->img, j, i, \
			img->img[cub->ren.ratio + (cub->ren.n_ratio * img->width)]);
		}
		i++;
	}
	put_floor(cub, &i, j);
}
