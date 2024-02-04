/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/04 15:00:16 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void close_all(t_cub *cub)
{
	close(cub->map.no_img->path);
	close(cub->map.so_img->path);
	close(cub->map.we_img->path);
	close(cub->map.ea_img->path);
}

void	init_struct_imgs(t_cub *cub)
{
	ft_bzero(&cub->map, sizeof(t_map));
	ft_bzero(cub, sizeof(t_cub));
	cub->map.no_img = ft_calloc(sizeof(t_img), 1);
	cub->map.so_img = ft_calloc(sizeof(t_img), 1);
	cub->map.we_img = ft_calloc(sizeof(t_img), 1);
	cub->map.ea_img = ft_calloc(sizeof(t_img), 1);
}

int	ft_parse_cub(t_cub *cub, char *arg)
{
	int		fd;
	char	*hold_file;
	int		count;

	count = 0;
	hold_file = ft_strdup("");
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (free(hold_file), ft_error(NULL, "Error:\nCan't open file\n"));
	init_struct_imgs(cub);
	if (!ft_parse_map(cub, fd, &hold_file))
		return (free(hold_file), 0);
	if (!check_textures(cub))
		return (free(hold_file), 0);
	if (!check_map(cub))
		return (free(hold_file), 0);
	free(hold_file);
	hold_file = NULL;
	close(fd);
	return (1);
}

void	fun(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	char	*str;

	atexit(fun);
	if (argc != 2)
		return (ft_error(NULL, "Error\nWrong number of arguments\n"));
	str = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (!str || ft_strncmp(str, ".cub", 5))
		return (ft_error(NULL, "Error: the map must end with .cub\n"));
	if (!ft_parse_cub(&cub, argv[1]))
		exit(1);
	check_angle(&cub);
	init_window(&cub);
	texture_init(&cub);
	mlx_key_hook(cub.mlx, (void *)key_press, &cub);
	mlx_loop_hook(cub.mlx, (void *)move_player, &cub);
	mlx_loop(cub.mlx);
	close_all(&cub);
	ft_error(&cub, NULL);
	mlx_terminate(cub.mlx);
	return (0);
}
