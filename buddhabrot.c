/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 21:09:59 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		first_iter_buddha(t_iter *iter, int nbr_iter, int *i)
{
	double	x_tmp;

	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && *i <= nbr_iter)
	{
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y;
		*i = *i + 1;
	}
}

void		correct_path_iter(t_iter *iter, int nbr_iter, t_screen *scr)
{
	int				i;
	int				pixel_x;
	int				pixel_y;
	double			x_tmp;

	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		if (is_in_screen(scr, pixel_x, pixel_y))
			color_buddha(scr, get_pixel_index(pixel_x, pixel_y), i);
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y;
		pixel_x = (int)round(0 - (((iter->y - scr->fractal->start_x) *
						(0.5 * scr->width * scr->fractal->zoom)) / scr->ratio_x)
				+ (scr->width * 0.5) + scr->min_scr_x);
		pixel_y = reverse_scale_screen_y(scr, 0 - iter->x);
		i++;
	}
}

int			iter_buddha(t_iter *iter, int nbr_iter, t_screen *scr)
{
	int		i;

	iter->o_x = iter->x;
	iter->o_y = iter->y;
	i = 0;
	first_iter_buddha(iter, nbr_iter, &i);
	if (((iter->x * iter->x) + (iter->y * iter->y)) > 4 &&
			i < scr->fractal->iteration && i < nbr_iter)
	{
		iter->x = iter->o_x;
		iter->y = iter->o_y;
		correct_path_iter(iter, nbr_iter, scr);
	}
	return (0);
}

void		*thread_buddha(void *arg)
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
		real_y = scale_screen_y(scr, y);
		while (x < scr->max_x)
		{
			iter.y = real_y;
			iter.x = scale_screen_x(scr, x);
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
				iter_buddha(&iter, scr->fractal->iteration, scr);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

int			buddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'b');
	if (!(screens = init_args(screens, nbr_screen, env)))
		safe_error_exit(env, "Malloc of threading screens failed");
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_buddha,
					(void *)screens[i]) == -1)
			safe_error_exit(env, "pthread create failed");
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
