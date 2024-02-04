/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 05:52:11 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/04 03:52:12 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	close_window(t_cub *cub)
{
	ft_error(cub, "Window closed\n");
	mlx_close_window(cub->mlx);
	exit(EXIT_SUCCESS);
}

void	move_dir(t_cub *cub, int *walk, float *angl)
{
	if (cub->player.move_right)
	{
		*angl = cub->player.angle + M_PI_2;
		*walk = 1;
	}
	else if (cub->player.move_left)
	{
		*angl = cub->player.angle - M_PI_2;
		*walk = 1;
	}
	else
		*angl = cub->player.angle;
}

void	move_player(t_cub *cub, int turn_D, int walk_D)
{
	float	i;
	float	j;
	float	angle;

	turn_D = is_left_right(cub->player);
	walk_D = is_up_down(cub->player);
	cub->player.angle = normalize_angle(cub->player.angle
			+ (5 * (M_PI / 180) * turn_D));
	move_dir(cub, &walk_D, &angle);
	j = cub->player.x + (cos(angle) * 5 * walk_D);
	i = cub->player.y + (sin(angle) * 5 * walk_D);
	if (cub->map.info[(((int)i) / TILE_SIZE)]
		[(((int)j) / TILE_SIZE)] == '1')
		return ;
	if (cub->map.info[((int)i / TILE_SIZE)]
		[(int)(cub->player.x / TILE_SIZE)] == '1')
		return ;
	if (cub->map.info[(int)(cub->player.y / TILE_SIZE)]
		[((int)j / TILE_SIZE)] == '1')
		return ;
	cub->player.x = j;
	cub->player.y = i;
	raycaster(cub);
}

void	supply_check(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub->player.move_up = 1;
	else
		cub->player.move_up = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->player.move_down = -1;
	else
		cub->player.move_down = 0;
}

int	key_press(mlx_key_data_t key_data, t_cub *cub)
{
	(void)key_data;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		close_window(cub);
	supply_check(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player.look_left = -1;
	else
		cub->player.look_left = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player.look_right = 1;
	else
		cub->player.look_right = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub->player.move_right = 1;
	else
		cub->player.move_right = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub->player.move_left = 1;
	else
		cub->player.move_left = 0;
	return (0);
}
