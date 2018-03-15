/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 16:51:30 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


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

void		clear_and_redraw(t_env *env)
{
	clear_image(env);
	display_fractals(env);
}

void		events_listener(t_env *env)
{
//	mlx_loop_hook(env->win, loop_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
}
