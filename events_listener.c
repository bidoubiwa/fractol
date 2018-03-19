/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/19 13:14:06 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			change_iterations(int keycode, t_env *env)
{
	if (keycode == KEY_MINUS)
	{
		if (env->screen[0]->fractal->iteration - 10 <= 5)
			env->screen[0]->fractal->iteration = 5;
		else
			env->screen[0]->fractal->iteration 
				= env->screen[0]->fractal->iteration - 10;
	}
	if (keycode == KEY_EQUAL)
		env->screen[0]->fractal->iteration
			= env->screen[0]->fractal->iteration + 10;
	display_screen_one(env);
	return (0);
}

void		events_listener(t_env *env)
{
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, MOTION_NOTIFY, PTR_MOTION_MASK, julia_loop, env);
	mlx_hook(env->win, KEY_PRESS, KEY_PRESS_MASK, change_iterations, env);
}
