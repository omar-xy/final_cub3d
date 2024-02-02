/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:11:58 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 21:57:51 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

void	texture_init(t_cub *cub)
{
	cub->map.no_img = ft_calloc(sizeof(t_img), 1);
	cub->map.so_img = ft_calloc(sizeof(t_img), 1);
	cub->map.we_img = ft_calloc(sizeof(t_img), 1);
	cub->map.ea_img = ft_calloc(sizeof(t_img), 1);
	cub->map.no_img->path = cub->map.no_path;
	cub->map.so_img->path = cub->map.so_path;
	cub->map.we_img->path = cub->map.we_path;
	cub->map.ea_img->path = cub->map.ea_path;
	inital_text(cub->map.no_img);
	inital_text(cub->map.so_img);
	inital_text(cub->map.we_img);
	inital_text(cub->map.ea_img);
}

int	check_png(char *path)
{
	int	i;

	i = ft_strlen(path);
	if (path[i - 1] != 'g' || path[i - 2] != 'n' || path[i - 3] != 'p'\
		|| path[i - 4] != '.')
		return (0);
	return (1);
}

void	inital_text(t_img *img)
{
	mlx_texture_t	*t;
	unsigned int	*bf;
	unsigned int	j;
	unsigned int	i;

	if (!check_png(img->path))
	{
		ft_error(NULL, "Error: texture must end with.png\n");
		exit(0);
	}
	t = mlx_load_png(img->path);
	img->height = t->height;
	img->width = t->width;
	bf = ft_calloc(sizeof(unsigned int), (img->width * img->height));
	if (!bf)
		exit(0);
	i = 0;
	j = 0;
	while (i < img->height * img->width)
	{
		bf[i++] = rgb(t->pixels[j], t->pixels[j + 1], t->pixels[j + 2], 255);
		j += 4;
	}
	img->img = bf;
	mlx_delete_texture(t);
}

void	check_angle(t_cub *cub)
{
	if (cub->player.dir == 'E')
		cub->player.angle = 0;
	else if (cub->player.dir == 'S')
		cub->player.angle = M_PI / 2;
	else if (cub->player.dir == 'W')
		cub->player.angle = M_PI;
	else if (cub->player.dir == 'N')
		cub->player.angle = 3 * M_PI / 2;
	else
		cub->player.angle = 0;
}

int	rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
