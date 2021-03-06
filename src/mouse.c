/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:39:50 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 21:07:31 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			check_zone(int x, int y, t_env *env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (x > env->screen[i]->min_x && x <= env->screen[i]->max_x &&
				y > env->screen[i]->min_y && y <= env->screen[i]->max_y)
			return (env->screen[i]->order);
		i++;
	}
	return (0);
}

int			julia_loop(int x, int y, t_env *env)
{
	int			zone;
	t_screen	*scr;
	double		new_x;
	double		new_y;

	if (env->julia_loop == 1)
	{
		zone = check_zone(x, y, env);
		scr = env->screen[zone - 1];
		if (zone == 1 && scr->fractal->name == 'j')
		{
			new_x = scale_screen_x(scr, x);
			new_y = scale_screen_y(scr, y);
			if (new_x >= -2 && new_x <= 2)
				scr->fractal->const_x = new_x;
			if (new_y >= -2 && new_x <= 2)
				scr->fractal->const_y = new_y;
			clear_zone(zone, env);
			display_screen_one(env);
		}
	}
	return (0);
}

void		switch_screens(int button, int zone, t_env *env)
{
	t_fractal	*tmp;

	if (button == 1)
	{
		tmp = env->screen[0]->fractal;
		env->screen[0]->fractal = env->screen[zone - 1]->fractal;
		env->screen[zone - 1]->fractal = tmp;
		clear_and_redraw(env);
	}
}

int			move_mouse(int button, int x, int y, t_env *env)
{
	int		zone;

	zone = check_zone(x, y, env);
	if (zone == 1 && env->zoom_enable == 1)
		zoom(button, x, y, env);
	return (1);
}

int			mouse_hook(int button, int x, int y, t_env *env)
{
	int		zone;

	if (x <= 0 || y <= 0)
		return (0);
	zone = check_zone(x, y, env);
	if (zone != 1)
		switch_screens(button, zone, env);
	else if (zone == 1 && env->zoom_enable == 1)
		zoom(button, x, y, env);
	return (1);
}
