/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:37:32 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/10 16:13:35 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_env(t_env *env, char *av)
{
	env->param = av;
	env->show_menu = 1;
	env->show_info = 1;
	env->julia_loop = 0;
	env->zoom_enable = 0;
	env->color = 0;
	env->color_size = 200;
	if (!(set_palettes(env)))
		return (0);
	env->palette = 0;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "Fractol");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	if (!(env->data_addr = (unsigned int*)mlx_get_data_addr(env->img,
			&env->bits_per_pixel, &env->bytes_per_line, &env->endian)))
		return (0);
	return (1);
}

