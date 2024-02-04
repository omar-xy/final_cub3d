/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:14:10 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/04 14:05:54 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "defines.h"

typedef struct s_floor
{
	char	*floor;
	int		r;
	int		g;
	int		b;
}				t_floor;

typedef struct s_ceiling
{
	char	*ceiling;
	int		r;
	int		g;
	int		b;
}				t_ceiling;

typedef struct s_img
{
	unsigned int	*img;
	unsigned int	height;
	unsigned int	width;
	char			*path;
}				t_img;

typedef struct s_map
{
	int			width;
	int			height;
	t_floor		floor;
	t_ceiling	ceiling;
	t_img		*no_img;
	t_img		*so_img;
	t_img		*we_img;
	t_img		*ea_img;
	char		**info;
}				t_map;

typedef struct s_player
{
	int		move_up;
	int		move_down;
	int		look_left;
	int		look_right;
	int		move_left;
	int		move_right;
	double	x;
	double	y;
	char	dir;
	double	fov; // 60
	double	angle; // 3 * M_PI / 2
}				t_player;

typedef struct s_ray
{
	bool	vertical_hit;
	bool	horizontal_hit;
	double	v_dis;
	double	h_dis;
	double	xh;
	double	yh;
	double	xv;
	double	yv;
	double	deltax;
	double	deltay;
	int		up_or_down;
	int		right_or_left;
	double	angle_ray;
}				t_ray;

typedef struct s_ren
{
	double	distance_to_wall;
	double	wall_projection;
	double	wall;
	double	start;
	int 	ratio;
	int		n_ratio;
}				t_ren;

typedef struct s_cub
{
	
	t_map		map;
	t_player	player;
	t_ray		ray;
	mlx_t		*mlx;
	t_ren 		ren;
	mlx_image_t	*img;
}				t_cub;

int		ft_parse_map(t_cub *cub, int fd, char **hold_file);
void	ft_store_data(t_cub *cub, char *hold_file);
bool	detect_map(char *line);
int		store_textures(t_cub *cub, char *line);
int		parse_color(t_cub *cub, char *line, char flag);
int		set_color(t_cub *cub, char **str, char flag);
void	calculate_map_size(t_cub *cub);
void	fill_empty_spaces(t_cub *cub);
int		check_map(t_cub *cub);
int		check_textures(t_cub *cub);
int		ft_error(t_cub *cub, char *str);
void	check_angle(t_cub *cub);
void	init_window(t_cub *cub);
void	inital_text(t_img *img, t_cub *cub);
void	texture_init(t_cub *cub);
void	free_towd(char **str);
int		rgb(int r, int g, int b, int a);
int		key_press(mlx_key_data_t key_data, t_cub *cub);
int		is_wall(t_cub *cub, double x, double y);
void	raycaster(t_cub *cub);
void	rendering(t_cub *cub, double angle_ray, int j);
void	move_player(t_cub *cub, int turn_D, int walk_D);
double	normalize_angle(double angle);
t_img	*init_img(t_cub *cub);
void	init_window(t_cub *cub);
void	check_directions(t_cub *cub, double angle_ray);
double	distance(double x1, double x2, double y1, double y2);
int		is_wall(t_cub *cub, double x, double y);
void	checks_for_vertical(t_cub *cub, double angle_ray);
void	checks_for_horizontal(t_cub *cub, double angle_ray);
double	get_ray_length(t_cub *cub, double angle_ray);
double	horizontal_inter(t_cub *cub, double angle_ray);
double	vertical_inter(t_cub *cub, double angle_ray);
double	normalize_angle(double angle);
int		is_up_down(t_player player);
int		is_left_right(t_player player);
void	init_struct(t_cub *cub, t_ren *ren, double angle_ray, t_img *img);
void	put_ceiling(t_cub *cub, t_ren r, int *i, int j);
void	put_floor(t_cub *cub, int *i, int j);

#endif