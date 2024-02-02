/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:20:47 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 22:22:55 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

int	ft_parse_cub(t_cub *cub, char *arg)
{
	int		fd;
	char	*hold_file;
	int		count;

	count = 0;
	hold_file = ft_strdup("");
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (free(hold_file), ft_error(NULL, "Error\nCan't open file\n"));
	ft_bzero(&cub->map, sizeof(t_map));
	ft_bzero(cub, sizeof(t_cub));
	if (!ft_parse_map(cub, fd, &hold_file, &count))
		return (free(hold_file), 0);
	if (!ft_store_data(cub, count, hold_file))
		return (free(hold_file), ft_error(cub, "Error: Wrong map, 1 \n"));
	if (!check_textures(cub))
		return (free(hold_file), ft_error(cub, "Error: Wrong texture P \n"));
	if (!check_map(cub))
		return (free(hold_file), ft_error(cub, "Error: Wrong map, 2 \n"));
	free(hold_file);
	hold_file = NULL;
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	char	*str;

	cub.player.fov = M_PI / 3;
	if (argc != 2)
		return (ft_error(NULL, "Error\nWrong number of arguments\n"));
	str = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (!str || ft_strncmp(str, ".cub", 5))
		return (ft_error(NULL, "Error: the map must end with .cub\n"));
	if (!ft_parse_cub(&cub, argv[1]))
		return (ft_error(NULL, "ft_parse_cub() failed\n"));
	check_angle(&cub);
	init_window(&cub);
	mlx_image_to_window(cub.mlx, cub.img, 0, 0);
	texture_init(&cub);
	mlx_key_hook(cub.mlx, (void *)key_press, &cub);
	mlx_loop_hook(cub.mlx, (void *)move_player, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	ft_error(&cub, NULL);
	free_towd(cub.map.store_map);
	return (0);
}
