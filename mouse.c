/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:45:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/16 11:22:37 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			check_zone(int x, int y, t_env *env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (x > env->screen[i]->min_x && x < env->screen[i]->max_x && y > env->screen[i]->min_y && y < env->screen[i]->max_y)
			return (env->screen[i]->order);
		i++;
	}
	return (0);
}

void		switch_screens(int button, int zone, t_env *env)
{
	t_fractal	*tmp;

	if (button == 1)
	{
		//dprintf(1, "zone = %d\n", zone);
		tmp = env->screen[0]->fractal;
		env->screen[0]->fractal = env->screen[zone - 1]->fractal;
		env->screen[zone - 1]->fractal = tmp;
		clear_and_redraw(env);
		//dprintf(1, "jusqu'ici tout va bien\n");
	}
}

int			mouse_hook(int button, int x, int y, t_env *env)
{
	int		zone;

	zone = check_zone(x, y, env);
	if (zone == 1)
		zoom(button, x, y, env);
	if (zone != 1)
		switch_screens(button, zone, env);
	return (0);
}

