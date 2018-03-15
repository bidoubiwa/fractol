/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:44:15 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 13:48:22 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			key_hook(int keycode, t_env *env)
{
	if (keycode == 123)
	{
		env->iter->o_x = env->iter->o_x - 0.01;
		clear_image(env);
		julia(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == 124)
	{
		env->iter->o_x = env->iter->o_x + 0.01;
		clear_image(env);
		julia(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_FAILURE);
	}
	if (keycode == KEY_L)
	{
		if (env->loop)
			env->loop = 0;
		else
			env->loop = 1;
		printf("KEY L :  %d\n", env->loop);
	}

	if (keycode == KEY_C)
		color_menu(env);
	return (0);
}


