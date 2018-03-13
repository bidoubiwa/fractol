/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 19:36:27 by cvermand         ###   ########.fr       */
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
	//double		input_x;
	t_iter		iter;
	t_env		*env;

	env = arg;
	y = env->min_y;
	while (y < env->max_y)
	{
		x =  env->min_x;
		input_y  = (0 - (y - env->screen->min_y) - env->screen->height / 2.0) / (0.5 * env->zoom * env->screen->height) + env->start_y;
		while (x < env->max_x)
		{
			iter.x = 1.5 * ((x - env->screen->min_x) - env->screen->width / 2.0) / (0.5 * env->zoom * env->screen->width) + env->start_x ;
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

int		mandelbrot(t_env *env)
{
	pthread_t	thread[4];
	t_env		**c_env;
	int			i;
	int			screen;

	
	c_env = NULL;
	i = 0;
	if (!(c_env = malloc(sizeof(t_env*))))
		return (0);
	while (i < 4)
	{
		printf("TEST\n");
		if (!(c_env[i] = malloc(sizeof(t_env))))
				return (0);
		i++;
	}
	screen = get_screen_by_fractal_name(env, 'j');
	init_args(c_env, screen, env);
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
