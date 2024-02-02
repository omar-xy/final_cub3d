/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:23:30 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/01 21:12:48 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

double  distance(double x1, double x2, double y1, double y2)
{
    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void    check_directions(t_cub *cub, double angle_ray)
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

double     horizontal_inter(t_cub *cub, double angle_ray)
{
    double  xa;
    double  ya;
    double  y;
    
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
    {
        cub->ray.xh = xa;
        cub->ray.yh = ya;
        return (distance(xa, cub->player.x, ya, cub->player.y));
    }
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


    // if (cub->ray.up_or_down)
    // {
    //     xa--;
    // }
    while (is_wall(cub, xa, ya + y) != 1)
    {
        // if (xa > cub->map.width * TILE_SIZE || ya > cub->map.height * TILE_SIZE && (xa < 0 && ya < 0))
        //     break;
        xa += cub->ray.deltax;
        ya += cub->ray.deltay;
    }
    cub->ray.xh = xa;
    cub->ray.yh = ya;
    return (distance(xa, cub->player.x, ya, cub->player.y));
}

double     vertical_inter(t_cub *cub, double angle_ray)
{
    double  xa;
    double  ya;
    double  x;

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
    {
        cub->ray.xv = xa;
        cub->ray.yv = ya;
        return (distance(xa, cub->player.x, ya, cub->player.y));
    }
    cub->ray.deltax = 64;
    cub->ray.deltay = 64 * tan(angle_ray);
    if (cub->ray.right_or_left == 0)
        cub->ray.deltax *= -1;
    if (cub->ray.up_or_down == 1 && cub->ray.deltay > 0)
        cub->ray.deltay *= -1;
    if (cub->ray.up_or_down == 0 && cub->ray.deltay < 0) 
        cub->ray.deltay *= -1;

    while (is_wall(cub, xa + x, ya) != 1)
    {
        xa += cub->ray.deltax;
        ya += cub->ray.deltay;
    }
    cub->ray.xv = xa;
    cub->ray.yv = ya;
    return (distance(xa, cub->player.x, ya, cub->player.y));
}

double     get_ray_length(t_cub *cub, double angle_ray)
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

t_img *init_img(t_cub *cub)
{
    t_img *img = NULL;
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
            img = cub->map.so_img;
        else
            img = cub->map.no_img;
    }
    return (img);
}

void    rendering(t_cub *cub, double angle_ray, int j)
{
    int w_w = cub->mlx->width ;
    int w_h = cub->mlx->height ;
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
            mlx_put_pixel(cub->img, j, i, rgb_to_int(cub->map.ceiling.r, cub->map.ceiling.g, cub->map.ceiling.b, 255));
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
            mlx_put_pixel(cub->img, j, i, rgb_to_int(cub->map.floor.r, cub->map.floor.g, cub->map.floor.b, 255));
        }
        i++;
    }
}

void    raycaster(t_cub *cub)
{
    int window_width = cub->mlx->width;
    double  mini_angle = FOV_ANGLE / window_width;// 0.0523599 WINDOW_WIDTH (num_col )
    double  angle_ray = normalize_angle(cub->player.angle - (FOV_ANGLE / 2));
    int     j = 0;
    // printf("%f : ray angle\n", angle_ray);
    // printf("%f : limit\n",  cub->player.angle + (FOV_ANGLE / 2));
    // printf("%f : fov\n", (FOV_ANGLE / 2));
    while (angle_ray < cub->player.angle - (FOV_ANGLE / 2) + 10 && j < window_width)
    {
        // printf("salam\n");
        // draw_line(angle_ray, cub->player.x, cub->player.y, get_ray_length(cub, angle_ray), cub);
        rendering(cub, angle_ray, j);
        angle_ray = normalize_angle(mini_angle + angle_ray);
        j++;
    }
}


int     is_wall(t_cub *cub, double x, double y)
{
    
    int w_w = (int)(x / 64);
    int w_h = (int)(y / 64) ;
    
    if (w_w >= cub->map.width || w_h >= cub->map.height || w_w < 0 || w_h < 0)
        return 1;
    if (cub->map.store_map[(int)(y / 64)][(int)(x / 64)] == '1')
        return 1;
    return 0;
}


void    init_window(t_cub *cub)
{
    int w_w = WINDOW_WIDTH;
    int w_h = WINDOW_HEIGHT;
    
    cub->player.move_down = 0;
    cub->player.move_up = 0;
    cub->player.move_left = 0;
    cub->player.move_right = 0;
    cub->player.look_left = 0;
    cub->player.look_right = 0;
    cub->mlx = mlx_init(w_w, w_h, "Cub3D", false);
    cub->img = mlx_new_image(cub->mlx, w_w, w_h); 
}
// void    draw_line(double angle, double x, double y, double len, t_cub *cub)
// {
//     int w_w = cub->map.width ;
//     int w_h = cub->map.height ;
//     int i = 0;
//     int xx;
//     int yy;
//     while (i < len)
//     {
//         xx = cos(angle) * i;
//         yy = sin(angle) * i;
//         if ((x + xx) < w_w && (y + yy) < w_h && (x + xx) > 0 && (y + yy) > 0)
//             mlx_put_pixel(cub->img, (int)x + xx, (int)y + yy, 0xfff);
//         i++;
//     }
// }
// void    draw_player(t_cub *cub)
// {  
    
//     mlx_put_pixel(cub->img, (int)cub->player.x, (int)cub->player.y, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x, (int)cub->player.y + 1, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x, (int)cub->player.y - 1, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x + 1, (int)cub->player.y, 0xffffff);
//     mlx_put_pixel(cub->img, (int) - 1, (int)cub->player.y, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x - 1, (int)cub->player.y - 1, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x - 1, (int)cub->player.y + 1, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x + 1, (int)cub->player.y + 1, 0xffffff);
//     mlx_put_pixel(cub->img, (int)cub->player.x + 1, (int)cub->player.y - 1, 0xffffff);
//     int i;
//     int xx;
//     int yy;
    
//     i = 0;
//     while (i < 20)
//     {
//         xx = cos(cub->player.angle) * i;
//         yy = sin(cub->player.angle) * i;
//         mlx_put_pixel(cub->img, (int)cub->player.x + xx, (int)cub->player.y + yy, 0xffffff);
//         i++;
//     }

// }


// static int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }


// void    draw(t_cub *cub)
// {
//     int w_w = cub->map.width ;
//     int w_h = cub->map.height ;
    
//     //         int color = ft_pixel(
// 	// rand() % 0xFF, // R
// 	// rand() % 0xFF, // G
// 	// rand() % 0xFF, // B
// 	// rand() % 0xFF );
//     for (int i = 0; i <  w_h; i++)
//     {
//         // printf("%s\n", cub->map.store_map[i]);
//         for (int j = 0; j < w_w; j++)
//         {
//             if(cub->map.store_map[i / TILE_SIZE][j / TILE_SIZE] == '1')
//             {
                
//                 mlx_put_pixel(cub->img, j, i, 0x159463);
//             }
//             else if(cub->map.store_map[i / 64][j / 64] == 'N')// 'N' is the player 
//             {
//                 mlx_put_pixel(cub->img, (int)cub->player.y, (int)cub->player.x, 0xffffff);
                
//             }
//             else
//                 mlx_put_pixel(cub->img, j, i, get_ceiling(&cub->map.ceiling));
//         }
//     }
//     mlx_put_pixel(cub->img, (int)cub->player.y, (int)cub->player.x, 0xffffff);
//     for (int i = 0; i <= w_w; i++)
//     {
//         for (int j = 0; j < w_h; j = j + 64)
//         {
//             mlx_put_pixel(cub->img, i, j, 0xADFF2F);
//         }
//     }
//     for (int i = 0; i <= w_h; i = i + 64)
//     {
//         for (int j = 0; j < w_w; j++)
//         {
//             mlx_put_pixel(cub->img, i, j, 0xADFF2F);
//         }
//     }
// }
