/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:38:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/13 19:50:50 by cvermand         ###   ########.fr       */
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

int			set_anti_pixel(t_env *env)
{
	if (env->anti_pixel)
		env->anti_pixel = 0;
	else
		env->anti_pixel = 1;
	display_screen_one(env);
	return (0);

}

int			change_palette(t_env *env)
{
	if (env->palette == 0)
		env->palette = 4;
	else
		env->palette--;
	clear_and_redraw(env);
	return (0);
}

int			key_hook(int keycode, t_env *env)
{
	printf("key : %d\n", keycode);
	if (keycode == KEY_ESCAPE)
		safe_exit(env);
	if (keycode == KEY_P)
		set_anti_pixel(env);
	if (keycode == KEY_I)
		toggle_info_menu(env);
	if (keycode == KEY_Z)
		enable_zoom(env);
	if (keycode == KEY_L)
		set_julia_loop(env);
	if (keycode == KEY_M)
		set_menu(env);
	if (keycode == KEY_SPACEBAR)
		change_palette(env);
	return (0);
}
