/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 14:58:47 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_env *env, t_iter *iter)
{
	//env->start_x = -0.25;
	env->loop = 0;
	env->color = 0;
	env->color_size = 200;
	env->start_x = 0.00;
	env->start_y = 0.00;
	env->zoom = 0.5;
	env->iteration = 15;
	env->iter = iter;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "titre");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	env->data_addr = (unsigned int*)mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->bytes_per_line, &env->endian);
}

int		main()
{
	t_env	env;
	t_iter	iter;

	init_mlx(&env, &iter);
	iter.o_x = 0.4;
	iter.o_y = 0.6;

	mandelbrot(&env);
	//antibuddhabrot(&env);
	//buddhabrot(&env)
	//	julia(&env, &iter);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	events_listener(&env);
	mlx_loop(env.mlx);
}
