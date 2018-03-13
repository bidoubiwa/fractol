/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 17:44:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 19:56:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_args(t_env **c_env, int nbr, t_env *env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		c_env[i]->screen = &env->screen[nbr];
		c_env[i]->zoom = env->screen[nbr].fractal->zoom;
		c_env[i]->iteration = env->screen[nbr].fractal->iteration;
		c_env[i]->width = env->screen[nbr].width;
		c_env[i]->height = env->screen[nbr].height;
		i++;
	}

/*	c_env[1]->screen = &env->screen[nbr];
	c_env[2]->screen = &env->screen[nbr];
	c_env[3]->screen = &env->screen[nbr];*/
	init_arg_limits(env->screen[nbr].min_x + env->screen[nbr].width / 2, env->screen[nbr].min_y , 
			c_env[0], env);
	init_arg_limits(env->screen[nbr].min_x , env->screen[nbr].min_y, c_env[1], env);
	init_arg_limits(env->screen[nbr].min_x +  env->screen[nbr].width / 2,env->screen[nbr].min_y + env->screen[nbr].height / 2, c_env[2], env);
	init_arg_limits(env->screen[nbr].min_x, env->screen[nbr].min_y + env->screen[nbr].height / 2, c_env[3], env);	


}


void	init_arg_limits(int min_x, int min_y, t_env *arg, t_env *env)
{
	arg->iter = env->iter;
	arg->min_x = min_x;
	arg->min_y = min_y;
	arg->data_addr = env->data_addr;
	arg->zoom = env->zoom;
	arg->start_x = env->start_x;
	arg->start_y = env->start_y;
	arg->iteration = env->iteration;
	if (min_x == 0)
		arg->max_x = WIDTH_SCREEN / 2;
	else if (min_x != 0)
		arg->max_x = WIDTH_SCREEN;
	if (min_y == 0)
		arg->max_y = HEIGHT_SCREEN / 2;
	else if (min_y != 0)
		arg->max_y = HEIGHT_SCREEN;
}

