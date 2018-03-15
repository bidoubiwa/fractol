/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:44:15 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 21:51:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		toggle_first_screen_size(t_env *env)
{
	env->screen[0]->max_x = get_x_max(1, env->show_menu);
	env->screen[0]->width = ft_dim(env->screen[0]->max_x, env->screen[0]->min_x);
	get_screen_ratio((double)env->screen[0]->width, (double)env->screen[0]->height, env->screen[0]);
}

void		set_menu(t_env *env)
{
	if (env->show_menu)
		env->show_menu = 0;
	else
		env->show_menu = 1;
	toggle_first_screen_size(env);
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


