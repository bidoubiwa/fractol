/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/12 14:40:42 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		clear_image_white(t_env *env)
{
	int		i;

	i = 0;
	while (i < HEIGHT_SCREEN * WIDTH_SCREEN)
	{
		if (env->data_addr[i] != 0)
			env->data_addr[i] = 0;
		i++;
	}
}


int		buddhabrot_bis(t_env *env)
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
				i = 0;
				while (((iter.x * iter.x) + (iter.y * iter.y)) < 4 &&  i <= env->iteration)
				{
				}

			}
			x++;
		}
		y++;
	}	
	return (1);
}
