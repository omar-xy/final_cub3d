/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:23:30 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/03 23:58:21 by otaraki          ###   ########.fr       */
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
	int w_w = cub->mlx->width;
	int w_h = cub->mlx->height;
	double  distance_to_wall = get_ray_length(cub, angle_ray) * cos(angle_ray - cub->player.angle);
	double  wall_projection = (w_w / 2) / tan(30 * M_PI / 180);
	double  wall = ( 64 / distance_to_wall) * wall_projection;
	double  start = (w_h / 2) - (wall / 2);

	int ratio;
	int n_ratio;

	t_img *img = init_img(cub);
	if (cub->ray.vertical_hit == true)
		ratio = (cub->ray.yv / TILE_SIZE - (int)(cub->ray.yv / TILE_SIZE)) * img->width;
	else if (cub->ray.horizontal_hit == true)
		ratio = (cub->ray.xh / TILE_SIZE - (int)(cub->ray.xh / TILE_SIZE)) * img->width; 
	int i = 0;
	while (i < start)
	{
		if (i < w_h && j < w_w && i > 0 && j > 0)
		{
			mlx_put_pixel(cub->img, j, i, rgb(cub->map.ceiling.r, cub->map.ceiling.g, cub->map.ceiling.b, 255));
		}
		i++;
	}
	while (i < start + wall)
	{
		if (i < w_h && j < w_w && i > 0 && j > 0)
		{
			n_ratio = (i - start) * ((double)img->height / wall);
			mlx_put_pixel(cub->img, j, i, img->img[ratio + (n_ratio * img->width)]);
		}
		i++;
	}
	while (i < w_h)
	{
		if (i < w_h && j < w_w && i > 0 && j > 0)
		{
			mlx_put_pixel(cub->img, j, i, rgb(cub->map.floor.r, cub->map.floor.g, cub->map.floor.b, 255));
		}
		i++;
	}
}
