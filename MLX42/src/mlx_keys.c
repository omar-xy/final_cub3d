/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 21:06:45 by W2Wizard          #+#    #+#             */
/*   Updated: 2024/01/20 16:59:45 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_key_t key_hook = ((mlx_ctx_t*)mlx->context)->key_hook;
	const mlx_key_data_t callback_data = {
		key,
		action,
		scancode,
		mods,
	};

	key_hook.func(callback_data, key_hook.param);
}

//= Public =//

void amlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->key_hook.func = func;
	mlxctx->key_hook.param = param;
	glfwSetKeyCallback(mlx->window, mlx_key_callback);
}

bool mlx_is_key_down(mlx_t* mlx, keys_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
