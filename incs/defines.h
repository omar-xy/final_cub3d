/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:30:54 by otaraki           #+#    #+#             */
/*   Updated: 2024/01/30 01:09:14 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "cub3d.h"

# define TRUE 1
# define FALSE 0
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_EXIT 17
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TILE_SIZE 64
# define WINDOW_WIDTH 1090
# define WINDOW_HEIGHT 1090
# define FOV_ANGLE (60 * (M_PI / 180)) 
# define NUM_RAYS 60
# define MINIMAP_SCALE_FACTOR 0.3
# define FPS 30
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define NUM_TEXTURES 5

#endif