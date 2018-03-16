/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/16 15:19:04 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			change_iterations(int keycode, t_env *env)
{
	if (keycode == KEY_MINUS)
		env->screen[0]->fractal->iteration = env->screen[0]->fractal->iteration - 10;
	if (keycode == KEY_EQUAL)
		env->screen[0]->fractal->iteration = env->screen[0]->fractal->iteration + 10;
	display_screen_one(env);
	return (0);
}

void		clear_image(t_env *env)
{
	int		i;

	i = 0;
	while (i < HEIGHT_SCREEN * WIDTH_SCREEN)
	{
		if (env->data_addr[i] != 0)
			env->data_addr[i] = 0;
		i++;
	}
}

void		clear_zone(int zone, t_env *env)
{
	t_screen 	*scr;
	int			x;
	int			y;

	scr = env->screen[zone - 1];
	y = scr->min_y;
	while (y <= scr->max_y)
	{
		x = scr->min_x;
		while (x <= scr->max_x)
		{
			if (env->data_addr[y * WIDTH_SCREEN + x] != 0)
				env->data_addr[y * WIDTH_SCREEN + x] = 0;
			x++;
		}
		y++;
	}
}

void		clear_and_redraw(t_env *env)
{
	clear_image(env);
	display_fractals(env);
}

void		events_listener(t_env *env)
{
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
	mlx_hook(env->win, MOTION_NOTIFY, PTR_MOTION_MASK, julia_loop, env);
	mlx_hook(env->win, KEY_PRESS, KEY_PRESS_MASK, change_iterations, env);
}
