/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:59:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/17 16:08:54 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	toggle_info_menu(t_env *env)
{
	if(env->show_info)
	{
		env->show_info = 0;
		display_screen_one(env);
	}
	else
	{
		env->show_info = 1;
		display_screen_one(env);
	}
}

void	display_info_menu(t_env *env)
{
	char	*iterations;

	mlx_string_put(env->mlx, env->win, 10, 15, 0xFFFFFF, "Zoom (Z) : ");
	if	(env->zoom_enable)
		mlx_string_put(env->mlx, env->win, 120, 15, 0x0ad66f, "Y");
	else 
		mlx_string_put(env->mlx, env->win, 120, 15, 0xd60a29, "N");
	mlx_string_put(env->mlx, env->win, 140, 15, 0xFFFFFF, "Loop (L) :");
	if	(env->julia_loop)
		mlx_string_put(env->mlx, env->win, 250, 15, 0x0ad66f, "Y");
	else 
		mlx_string_put(env->mlx, env->win, 250, 15, 0xd60a29, "N");
	mlx_string_put(env->mlx, env->win, 270, 15, 0xFFFFFF, "Iterations :");
	iterations = ft_itoa(env->screen[0]->fractal->iteration);
	mlx_string_put(env->mlx, env->win, 400, 15, 0xFFFFFF, iterations);
	ft_strdel(&iterations);
}
