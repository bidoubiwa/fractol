/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 20:56:15 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_path	*add_chain(int x, int y, t_path *begin)
{
	t_path	*tmp;

	tmp = ft_memalloc(sizeof(t_path));
	if (begin == NULL)
		tmp->next = NULL;
	else
		tmp->next = begin;
	tmp->x = x;
	tmp->y = y;
	return (tmp);
}

void	free_path(t_path *begin)
{
	t_path *tmp;

	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
}

int		iter_buddha(t_iter *iter, int nbr_iter, t_screen *scr, int pixel)
{
	t_path	*path;
	t_path	*tmp;
	int		i;
	double	pixel_x;
	double	pixel_y;
	double	x_tmp;

	path = NULL;
	pixel_x = 0;
	pixel_y = 0;
	iter->o_x = iter->x;
	iter->o_y = iter->y;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN) 
			path = add_chain((int)round(pixel_x), (int)round(pixel_y), path);
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		pixel_x = (((iter->x - scr->fractal->start_x) * (0.5 * scr->width * scr->fractal->zoom)) / scr->ratio_x) + (scr->width * 0.5) + scr->min_scr_x;
		pixel_y = (scr->height * 0.5) - (iter->y - scr->fractal->start_y) * ((0.5 * scr->fractal->zoom * scr->height) / scr->ratio_y) + scr->min_scr_y;
		i++;
	}
	if (((iter->x * iter->x) + (iter->y * iter->y)) > 4 && i != scr->fractal->iteration && i > 10)
	{
		tmp = path;
		while (path)
		{
			scr->data_addr[(path->y * WIDTH_SCREEN) + path->x] = scr->data_addr[(path->y * WIDTH_SCREEN) + path->x] + 0x161616;
			path = path->next;
		}
		free_path(tmp);
		path = NULL;
		tmp = NULL;
	}
	else
	{
		free_path(path);
		tmp = NULL;
		path = NULL;
	}
	return (0);
}

void	*thread_buddha(void *arg)
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
				iter_buddha(&iter, scr->fractal->iteration, scr, ((y * WIDTH_SCREEN) + x));
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

int		buddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	nbr_screen = get_screen_by_fractal_name(env, 'b');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);	
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_buddha, (void *)screens[i]) == -1)
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
