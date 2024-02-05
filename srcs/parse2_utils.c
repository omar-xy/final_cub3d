/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:52:04 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/05 02:05:37 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	condition_check(t_cub *cub, char **map, int i, int j)
{
	if (!(map[i][j] == 'N' || map[i][j] == 'S' \
		|| map[i][j] == 'W' || map[i][j] == 'E' \
		|| map[i][j] == '0' || map[i][j] == '1' || map[i][j] == ' '))
		return (0);
	if (i == 0 || i == cub->map.height - 1 \
		|| j == 0 || j == cub->map.width - 1)
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
	}
	else if (i > 0 && j > 0 && (i < cub->map.height - 1) \
		&& (j < cub->map.width - 1)
		&& (map[i][j] == '0' || map[i][j] == 'N' \
		|| map[i][j] == 'S' || map[i][j] == 'W' \
		|| map[i][j] == 'E'))
	{
		if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ' \
		|| map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
			return (0);
	}
	return (1);
}

int	check_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	cub->player.dir = '\0';
	while (cub->map.info[++i])
	{
		j = -1;
		while (cub->map.info[i][++j])
		{
			if (!condition_check(cub, cub->map.info, i, j))
				return (0);
			if (cub->map.info[i][j] == 'N' || cub->map.info[i][j] == 'S' \
				|| cub->map.info[i][j] == 'W' || cub->map.info[i][j] == 'E')
			{
				if (cub->player.dir != '\0')
					return (0);
				cub->player.x = j * 64 + (64 / 2);
				cub->player.y = i * 64 + (64 / 2);
				cub->player.dir = cub->map.info[i][j];
				cub->map.info[i][j] = '0';
			}
		}
	}
	return ((cub->player.dir != '\0'));
}

void	ft_store_data(t_cub *cub, char *hold_file)
{
	char	*tmp_line;

	tmp_line = NULL;
	tmp_line = ft_strtrim(hold_file, "\n");
	cub->map.info = ft_split(tmp_line, '\n');
	free(tmp_line);
	calculate_map_size(cub);
	fill_empty_spaces(cub);
}

int	check_flg(t_cub *cub, int flg, char *line)
{
	if (flg == 1)
		return (ft_error(cub, "Error: in map\n"));
	if (!store_textures(cub, line))
		exit(0);
	return (1);
}
