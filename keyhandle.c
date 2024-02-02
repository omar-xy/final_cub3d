/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 04:23:52 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/02 13:05:24 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void    close_window(t_cub *cub)
{
    mlx_close_window(cub->mlx);
    exit(EXIT_SUCCESS);
}

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

int is_up_down(t_player player)
{
    if (player.move_up == 1)
        return (1);
    if (player.move_down == -1)
        return (-1);
    return (0);
}

int is_left_right(t_player player)
{
    if (player.look_left == -1)
        return (-1);
    if (player.look_right == 1)
        return (1);
    return (0);
}

void move_dir(t_cub *cub, int *walk, float *angl)
{
    if(cub->player.move_right)
    {
        *angl = cub->player.angle + M_PI_2;
        *walk = 1;
    }
    else if(cub->player.move_left)
    {
        *angl = cub->player.angle - M_PI_2;
        *walk = 1;
    }
    else 
        *angl = cub->player.angle;
}

void move_player(t_cub *cub, int turn_D, int walk_D)
{
    float i;
    float  j;
    float angle;

    turn_D = is_left_right(cub->player);
    walk_D = is_up_down(cub->player);
    cub->player.angle = normalize_angle(cub->player.angle + (5 * (M_PI / 180) * turn_D));
    move_dir(cub, &walk_D, &angle);
    j = cub->player.x + (cos(angle) * 5 * walk_D);
    i = cub->player.y + (sin(angle) * 5 * walk_D);
    if (cub->map.store_map[(((int)i) / TILE_SIZE)][(((int)j) / TILE_SIZE)] == '1')// check next tile
        return ;
    if (cub->map.store_map[((int)i / TILE_SIZE)][(int)(cub->player.x / TILE_SIZE)] == '1')// check next tile
        return ;
    if (cub->map.store_map[(int)(cub->player.y / TILE_SIZE)][((int)j / TILE_SIZE)] == '1')// check next tile
        return ;
    cub->player.x = j;
    cub->player.y = i;
    raycaster(cub);
}

int key_press(mlx_key_data_t key_data, t_cub *cub)
{
    (void)key_data;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_ESCAPE))
        close_window(cub);
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_UP) || mlx_is_key_down(cub->mlx ,MLX_KEY_W))
        cub->player.move_up = 1;
    else
        cub->player.move_up = 0;
    if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN) || mlx_is_key_down(cub->mlx ,MLX_KEY_S))
        cub->player.move_down = -1;
    else
        cub->player.move_down = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_LEFT))
        cub->player.look_left = -1;
    else
        cub->player.look_left = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_RIGHT))
        cub->player.look_right = 1;
    else  
        cub->player.look_right = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_D))
        cub->player.move_right = 1;
    else  
        cub->player.move_right = 0;
    if (mlx_is_key_down(cub->mlx ,MLX_KEY_A))
        cub->player.move_left = 1;
    else  
        cub->player.move_left = 0;
    return (0);
}

// int    key_relase(mlx_key_data_t key_data, t_cub *cub)
// {
//     (void)key_data;
//     if (mlx_is_key_down(cub->mlx ,MLX_KEY_UP))
//         cub->player.move_up = 0;
//     if (mlx_is_key_down(cub->mlx ,MLX_KEY_LEFT))
//         cub->player.move_left = 0;
//     if (mlx_is_key_down(cub->mlx ,MLX_KEY_RIGHT))
//         cub->player.move_right = 0;
//     if (mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
//         cub->player.move_down = 0;  
//     return (0);

// }

// void    keyhandle(void *cub)
// {
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_ESCAPE))
//     {
//         close_window(cub);
//     }
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_UP))
//         move_player(cub, 0, 1);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_DOWN))
//         move_player(cub, 0, -1);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_LEFT))
//         move_player(cub, -1, 0);
//     if (mlx_is_key_down(cub->mlx.mlx, MLX_KEY_RIGHT))
//         move_player(cub, 1, 0);
// }