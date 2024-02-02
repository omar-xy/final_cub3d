/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_png.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:11:29 by W2Wizard          #+#    #+#             */
/*   Updated: 2024/01/25 19:25:42 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

mlx_texture_t* mlx_load_png(const char* path)
{
	
	MLX_NONNULL(path);

	mlx_texture_t* image;
	if (!(image = malloc(sizeof(mlx_texture_t))))
		return ((void*)mlx_error(MLX_MEMFAIL));

	uint32_t error;
	image->bytes_per_pixel = BPP;
	if ((error = lodepng_decode32_file(&image->pixels, &image->width, &image->height, path)))
	{
		free(image);
		// Explicitly print error on purpose
		fprintf(stderr, "MLX42: LodePNG: %s\n", lodepng_error_text(error));
		return ((void*)mlx_error(MLX_INVPNG));
	}
	return (image);
}
