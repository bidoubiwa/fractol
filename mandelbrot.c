/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 14:44:58 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void	mandelbrot_iter(t_env *env, t_iter *iter, int x, int y)
{
	int		i;
	double	input_y;
	double	input_x;
	double	x_tmp;
	double	y_tmp;

	input_x = iter->x;
	input_y = iter->y;
	i = 0;
	while (((iter->x * iter->x) + (iter->y * iter->y)) < 4 && i <= env->iteration)
	{
		x_tmp = iter->x;
		y_tmp = iter->y;
		iter->x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + input_x;
		iter->y = 2 * (x_tmp * y_tmp) + input_y;
		env->data_addr[(y * WIDTH_SCREEN) + x] = palette(i);
		i++;
	}
}

char	is_in_safe_range(double real_x, double real_y)
{
	if (real_x >= -0.52 && real_x <= 0.25 && real_y <= 0.5 && real_y >= -0.5)
		return (1);
	else if (real_x >= -1.15 && real_x <= -0.85 && real_y <= 0.2 && real_y >= -0.2)
		return (1);
	return (0);
}

void	*thread_mandelbrot(void *arg)
{
	int			x;
	int			y;
	double		input_y;
	double		input_x;
	t_iter		iter;
	t_env		*env;

	env = arg;
	y = env->min_y;
	while (y < env->max_y)
	{
		x =  env->min_x;
		input_y = (0 - (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN)) + env->start_y;
		while (x < env->max_x)
		{
			input_x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom * WIDTH_SCREEN) + env->start_x;
			iter.x = input_x;
			iter.y = input_y;
			if (is_in_safe_range(iter.x, iter.y))
				env->data_addr[(y * WIDTH_SCREEN) + x] = palette(1);
			else if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
			{
//				printf("je boucle \n");
				mandelbrot_iter(env, &iter, x, y);
			}
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

void	init_arg(int min_x, int min_y, t_env *arg, t_env *env)
{
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

int		mandelbrot(t_env *env)
{
	pthread_t	thread[4];
	t_env		c_env[4];
	int			i;

	init_arg(WIDTH_SCREEN / 2, 0, &c_env[0], env);
	init_arg(0, 0, &c_env[1], env);
	init_arg(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, &c_env[2], env);
	init_arg(0 ,HEIGHT_SCREEN / 2, &c_env[3], env);
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_mandelbrot, (void *)&c_env[i]) == -1) 
		{
			perror("pthread_create");
			return EXIT_FAILURE;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join (thread[i], NULL);
		i++;
	}
	return (0);
}
