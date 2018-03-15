/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:44:15 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 16:52:52 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_menu(t_env *env)
{
	if (env->show_menu)
		env->show_menu = 0;
	else
		env->show_menu = 1;
	env->screen[0]->max_x = get_x_max(1, env->show_menu);
	clear_and_redraw(env);
}

int			key_hook(int keycode, t_env *env)
{
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
	}
	if (keycode == KEY_M)
		set_menu(env);
	if (keycode == KEY_C)
		color_menu(env);
	return (0);
}


