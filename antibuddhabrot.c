/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 15:34:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		color_anti(t_screen *scr, int pixel, int i)
{
	unsigned int	pal;

	pal = scr->palettes[scr->palette][i % 5];
	if (scr->palette == 4)
	{
		scr->data_addr[pixel] = merging_alpha(((i * (pal >> 16) % 255) << 16)
				+ (((i * (pal >> 8)) % 255) << 8)
				+ (i * (pal) % 255), scr->data_addr[pixel], 0.2);
	}
	else
		scr->data_addr[pixel] = merging_alpha(
				scr->palettes[scr->palette][i % 5], scr->data_addr[pixel], 0.2);
}

int			iter_anti(t_iter *iter, int nbr_iter, t_screen *scr)
{
	double			x_tmp;
	int				i;
	int				pixel_x;
	int				pixel_y;
	int				pixel;

	iter->o_x = iter->x;
	iter->o_y = iter->y;
	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		pixel = get_pixel_index(pixel_x, pixel_y);
		if (is_in_screen(scr, pixel_x, pixel_y) && i > 50)
			color_anti(scr, pixel, i);
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y;
		pixel_x = reverse_scale_screen_x(scr, iter->x);
		pixel_y = reverse_scale_screen_y(scr, iter->y);
		i++;
	}
	return (0);
}

void		*thread_anti(void *arg)
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
				iter_anti(&iter, scr->fractal->iteration, scr);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

int			antibuddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'a');
	if (!(screens = init_args(screens, nbr_screen, env)))
		safe_error_exit(env, "Malloc of threading screens failed");
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_anti,
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
