/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/12 16:08:17 by cvermand         ###   ########.fr       */
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
		//printf("x : %d\n", begin->x);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
}

int		buddhabrot(t_env *env)
{
	int		x;
	int		y;
	int		i;
	t_iter	iter;
	double	real_y;
	double	real_x;
	double	x_tmp;
	double	y_tmp;
	double	pixel_x;
	double	pixel_y;
	t_path	*tmp;
	t_path	*path;


	y = 0;
	real_y = 0;
	while (y < HEIGHT_SCREEN)
	{
		x = 0;
		real_y = (0 - (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN)) + env->start_y;
		while (x < WIDTH_SCREEN)
		{
				real_x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom * WIDTH_SCREEN) + env->start_x;
				iter.x = real_x;
				iter.y = real_y;
			if (real_x >= -2 && real_x <= 2 && real_y <= 2 && real_y >= -2)
			{
				path = NULL;
				i = 0;
				while (((iter.x * iter.x) + (iter.y * iter.y)) < 4 &&  i <= env->iteration)
				{
					x_tmp = iter.x;
					y_tmp = iter.y;
					iter.x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + real_x;
					iter.y = 2 * (x_tmp * y_tmp) + real_y;
				
					pixel_x = (((iter.x - env->start_x) * (0.5 * WIDTH_SCREEN * env->zoom)) / 1.5) + (WIDTH_SCREEN * 0.5);
					pixel_y = (HEIGHT_SCREEN * 0.5) - (iter.y - env->start_y) * (0.5 * env->zoom * HEIGHT_SCREEN);
					if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN) 
					{
						path = add_chain((int)round(pixel_x), (int)round(pixel_y), path);
						
					}	
					//env->data_addr[(y * WIDTH_SCREEN) + x] = palette(i);
					//					printf("pixel x : %d pixel y : %d")
					i++;
				}
				if (((iter.x * iter.x) + (iter.y * iter.y)) > 4 && i != env->iteration && i > 10)
				{
					tmp = path;
					while (path)
					{
						env->data_addr[(path->y * WIDTH_SCREEN) + path->x] = env->data_addr[(path->y * WIDTH_SCREEN) + path->x] +  0x080808;
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
			}
			x++;
		}
		y++;
	}	
	return (1);
}
