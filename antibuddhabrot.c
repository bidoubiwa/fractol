/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/19 15:22:08 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iter_anti(t_iter *iter, int nbr_iter, t_screen *scr)
{
	double		x_tmp;
	int			i;
	double		pixel_x;
	double		pixel_y;

	iter->o_x = iter->x;
	iter->o_y = iter->y;
	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		if ((int)round(pixel_x) > scr->min_scr_x && (int)round(pixel_x) < scr->max_scr_x
				&& (int)round(pixel_y) > scr->min_scr_y && (int)round(pixel_y) < scr->max_scr_y && i > 50)
		{
			scr->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] = scr->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] + 0x040404;
		}
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
  		pixel_x = (((iter->x - scr->fractal->start_x) * (0.5 * scr->width * scr->fractal->zoom)) / scr->ratio_x) + (scr->width * 0.5) + scr->min_scr_x;
  		pixel_y = (scr->height * 0.5) - (iter->y - scr->fractal->start_y) * ((0.5 * scr->fractal->zoom * scr->height) / scr->ratio_y) + scr->min_scr_y;
		i++;
	}
	return (0);
}

void	*thread_anti(void *arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
	y = scr->min_y;
	while (y < scr->max_y)
	{
		x = scr->min_x;
		real_y  = 0 - (scr->ratio_y * (((y - scr->min_scr_y) - scr->height / 2.0) / 
			(0.5 * scr->fractal->zoom * scr->height))) + scr->fractal->start_y;
		while (x < scr->max_x)
		{
			iter.y = real_y;
			iter.x = scr->ratio_x * (((x - scr->min_scr_x) - scr->width / 2.0) / (0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
				iter_anti(&iter, scr->fractal->iteration, scr);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}


int		antibuddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'a');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);	
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_anti, (void *)screens[i]) == -1)
		{
			perror("pthread_create");
			return EXIT_FAILURE;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free_screens(screens);
	return (1);
}
