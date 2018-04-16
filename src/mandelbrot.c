/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 18:31:52 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		color_mandel(t_screen *scr, int pixel, int i)
{
	unsigned int	pal;

	pal = scr->palettes[scr->palette][i % 5];
	if (scr->palette == 4)
		scr->data_addr[pixel] = ((i * (pal >> 16) % 255) << 16) +
			(((i * (pal >> 8)) % 255) << 8) + (i * (pal) % 255);
	else
		scr->data_addr[pixel] = pal;
}

void		mandelbrot_iter(t_iter *iter, t_screen *scr, int x, int y)
{
	int				i;
	double			input_y;
	double			input_x;
	double			x_tmp;
	int				nbr_iter;

	nbr_iter = scr->fractal->iteration;
	input_x = iter->x;
	input_y = iter->y;
	i = 0;
	while (((iter->x * iter->x) + (iter->y * iter->y)) < 4 && i <= nbr_iter)
	{
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + input_x;
		iter->y = 2 * (x_tmp * iter->y) + input_y;
		i++;
	}
	if (i < nbr_iter)
		(i > 1) ? color_mandel(scr, get_pixel_index(x, y), i) : 0;
}

char		is_in_safe_range(double real_x, double real_y)
{
	if (real_x >= -0.52 && real_x <= 0.25 && real_y <= 0.5 && real_y >= -0.5)
		return (1);
	else if (real_x >= -1.15 && real_x <= -0.85 &&
			real_y <= 0.2 && real_y >= -0.2)
		return (1);
	return (0);
}

void		*thread_mandelbrot(void *arg)
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
			if (is_in_safe_range(iter.x, iter.y))
				scr->data_addr[get_pixel_index(x, y)] = 0x000000;
			if (((iter.x * iter.x) + (iter.y * iter.y)) < 4)
				mandelbrot_iter(&iter, scr, x, y);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

int			mandelbrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'm');
	if (!(screens = init_args(screens, nbr_screen, env)))
		safe_error_exit(env, "Malloc of threading screens failed");
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &thread_mandelbrot,
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
