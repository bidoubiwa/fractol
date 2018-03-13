/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:33:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 19:54:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iter_julia(t_iter *iter, int nbr_iter, t_env *env, int pixel)
{
	double x_tmp;
	int		i;

	i = 0;
	while (i <= nbr_iter)
	{
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		
		if ((iter->x * iter->x) + (iter->y * iter->y) <= 4)
		{
			env->data_addr[pixel]  = palette(i);
		}
		i++;
	}
	return (0);
}

void	init_iter(t_iter *iter, t_env *env)
{
	iter->o_x = env->iter->o_x;
	iter->o_y = env->iter->o_y;
}

void	*thread_julia(void	*arg)
{
	int		x;
	int		y;
	double	real_y;
	t_iter	iter;
	t_env	*env;

		printf("zoom : %f\n",env->zoom );
		printf("height : %d\n", env->screen->height);
		printf("min_y : %d\n", env->min_y);

	env = arg;
	dprintf(1,"julia\n");
	init_iter(&iter, env);
	y = env->min_y;
	while (y < env->max_y)
	{
		x = env->min_x;
//		printf("min_y : %d height : %d zoom : %f\n", env->screen->min_y, env->screen->height, env->zoom);
		real_y  = ((y - (double)env->min_y) - (double)env->height / 2.0) / (0.5 * env->zoom * (double)env->height) + env->start_y;
		while (x < env->max_x)
		{
			iter.y = real_y;
			iter.x = 1.5 * ((x - env->screen->min_x) - env->screen->width / 2.0) / (0.5 * env->zoom * env->screen->width) + env->start_x ;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
			{
				iter_julia(&iter, env->iteration, env, ((y * WIDTH_SCREEN) + x));
			}
			x++;
		}	
		y++;
	}
	pthread_exit(NULL);
}

int			julia(t_env *env)
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
		printf("env : %zu\n", sizeof(t_env));
		if (!(c_env[i] = malloc(sizeof(t_env))))
				return (0);
		i++;
	}
	screen = get_screen_by_fractal_name(env, 'j');
	printf("avant init\n");
	init_args(c_env, screen, env);
	printf("apres init\n");
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_julia, (void *)c_env[i]) == -1) 
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
