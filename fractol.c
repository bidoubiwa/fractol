/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/09 17:54:04 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_env *env)
{
	env->iter = 3;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "titre");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	env->data_addr = (unsigned int*)mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->bytes_per_line, &env->endian);
}

int		main()
{
	t_env	env;

	init_mlx(&env);
	mandelbrot(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_loop(env.mlx);
}
