/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandle_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 06:07:50 by ahamrad           #+#    #+#             */
/*   Updated: 2024/02/03 23:57:02 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

int	is_up_down(t_player player)
{
	if (player.move_up == 1)
		return (1);
	if (player.move_down == -1)
		return (-1);
	return (0);
}

int	is_left_right(t_player player)
{
	if (player.look_left == -1)
		return (-1);
	if (player.look_right == 1)
		return (1);
	return (0);
}
