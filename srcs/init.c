/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:06:35 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/04 03:50:39 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init_window(t_cub *cub)
{
	int	w_w;
	int	w_h;

	w_w = WINDOW_WIDTH;
	w_h = WINDOW_HEIGHT;
	cub->player.move_down = 0;
	cub->player.move_up = 0;
	cub->player.move_left = 0;
	cub->player.move_right = 0;
	cub->player.look_left = 0;
	cub->player.look_right = 0;
	cub->mlx = mlx_init(w_w, w_h, "Cub3D", false);
	if (!cub->mlx)
	{
		ft_error(cub, "Error: mlx failed\n");
		exit(EXIT_FAILURE);
	}
	cub->img = mlx_new_image(cub->mlx, w_w, w_h);
	if (!cub->img || mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0)
	{
		ft_error(cub, "Error: mlx failed\n");
		exit(EXIT_FAILURE);
	}
}

t_img	*init_img(t_cub *cub)
{
	t_img	*img;

	img = NULL;
	if (cub->ray.vertical_hit == true)
	{
		if (cub->ray.right_or_left == 1)
			img = cub->map.ea_img;
		else
			img = cub->map.we_img;
	}
	else if (cub->ray.horizontal_hit == 1)
	{
		if (cub->ray.up_or_down == 1)
			img = cub->map.no_img;
		else
			img = cub->map.so_img;
	}
	return (img);
}

void	check_directions(t_cub *cub, double angle_ray)
{
	if (angle_ray > 0 && angle_ray < M_PI)
		cub->ray.up_or_down = 0;
	else
		cub->ray.up_or_down = 1;
	if (angle_ray > (M_PI / 2) && angle_ray < (3 * M_PI / 2))
		cub->ray.right_or_left = 0;
	else
		cub->ray.right_or_left = 1;
}

double	distance(double x1, double x2, double y1, double y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

int	is_wall(t_cub *cub, double x, double y)
{
	int	w_w;
	int	w_h;

	w_w = (int)(x / 64);
	w_h = (int)(y / 64);
	if (w_w >= cub->map.width || w_h >= cub->map.height || w_w < 0 || w_h < 0)
		return (1);
	if (cub->map.info[(int)(y / 64)][(int)(x / 64)] == '1')
		return (1);
	return (0);
}
