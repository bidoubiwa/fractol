/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:30:59 by pfaust            #+#    #+#             */
/*   Updated: 2018/03/19 13:32:24 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_julia_loop(t_env *env)
{
	if (env->julia_loop)
		env->julia_loop = 0;
	else
		env->julia_loop = 1;
	if (env->zoom_enable)
		env->zoom_enable = 0;
	if (env->show_info)
		display_screen_one(env);
}

int			enable_zoom(t_env *env)
{
	if (env->zoom_enable)
		env->zoom_enable = 0;
	else
		env->zoom_enable = 1;
	if (env->julia_loop)
		env->julia_loop = 0;
	if (env->show_info)
		display_screen_one(env);
	return (0);
}

int			change_palette(t_env *env, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		if (env->palette == 0)
			env->palette = 4;
		else
			env->palette--;
	}
	if (keycode == KEY_RIGHT)
	{
		if (env->palette == 4)
			env->palette = 0;
		else
			env->palette++;
	}
	clear_and_redraw(env);
	return (0);
}

int			key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_FAILURE);
	}
	if (keycode == KEY_I)
		toggle_info_menu(env);
	if (keycode == KEY_Z)
		enable_zoom(env);
	if (keycode == KEY_L)
		set_julia_loop(env);
	if (keycode == KEY_M)
		set_menu(env);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		change_palette(env, keycode);
	return (0);
}
