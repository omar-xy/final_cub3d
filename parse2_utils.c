/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:52:04 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 22:18:01 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

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
	while (cub->map.store_map[++i])
	{
		j = -1;
		while (cub->map.store_map[i][++j])
		{
			if (!condition_check(cub, cub->map.store_map, i, j))
				return (0);
			if (cub->map.store_map[i][j] == 'N' || cub->map.store_map[i][j] == 'S' \
				|| cub->map.store_map[i][j] == 'W' || cub->map.store_map[i][j] == 'E')
			{
				cub->player.x = j * 64 + (64 / 2);
				cub->player.y = i * 64 + (64 / 2);
				cub->player.dir = cub->map.store_map[i][j];
				cub->map.store_map[i][j] = '0';
			}
		}
	}
	if (cub->player.dir == '\0')
		return (0);
	return (1);
}

int	ft_store_data(t_cub *cub, int count, char *hold_file)
{
	char	*tmp_line;

	tmp_line = NULL;
	if (count != 6)
		return (ft_error(NULL, "Error: Wrong number of textures, 1\n"));
	tmp_line = ft_strtrim(hold_file, "\n");
	cub->map.store_map = ft_split(tmp_line, '\n');
	calculate_map_size(cub);
	fill_empty_spaces(cub);
	free(tmp_line);
	return (1);
}

static int	check_flg(t_cub *cub, int flg, char *line)
{
	if (flg == 1)
		return (ft_error(cub, "Error: Wrong map, 0\n"));
	if (!store_textures(cub, line))
		return (ft_error(cub, "Error: Wrong texture !1\n"));
	return (1);
}

int	ft_parse_map(t_cub *cub, int fd, char **hold_file, int *count)
{
	char	*line;
	int		flg;

	flg = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((detect_map(line) || line[0] == '\n'))
		{
			if (detect_map(line))
				flg = 1;
			*hold_file = ft_strjoin_free(*hold_file, line);
		}
		if (line[0] != '\n' && !detect_map(line))
		{
			if (!check_flg(cub, flg, line))
				return (free(*hold_file), free(line), 0);
			(*count)++;
		}
		free(line);
	}
	return (free(line), 1);
}
