/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:15:08 by otaraki           #+#    #+#             */
/*   Updated: 2024/02/02 22:09:47 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3d.h"

int count_towd_arr(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void free_towd(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int is_digit(t_cub *cub, char **str, int i, int j)
{
	i = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (free_towd(str), ft_error(cub, "Error: Wrong color3\n"));
			j++;
		}
		i++;
	}
	return (1);
}

int count_comas(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

int  parse_color(t_cub *cub, char *line, char flag)
{
	int i;
	int j;
	char **str;

	i = 0;
	j = 0;
	if (!line)
		return (ft_error(cub, "Error: Wrong color0\n"));
	if (!count_comas(line))
		return (ft_error(cub, "Error: Wrong color1\n"));
	str = ft_split(line, ',');
	i = count_towd_arr(str);
	if (i != 3)
		return (free_towd(str), ft_error(cub, "Error: Wrong color2\n"));
	if (!is_digit(cub, str, i , j))
		return (0);
	if (!set_color(cub, str, flag))
		return (free_towd(str), ft_error(cub, "Error: Wrong color4\n"));
	return (free_towd(str), 1);
}
