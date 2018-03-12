/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/12 14:32:16 by cvermand         ###   ########.fr       */
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
					x_tmp = iter.x;
					y_tmp = iter.y;
					iter.x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + real_x;
					iter.y = 2 * (x_tmp * y_tmp) + real_y;
					//env->data_addr[(y * WIDTH_SCREEN) + x] = palette(i);
					//					printf("pixel x : %d pixel y : %d")
					i++;
				}
				if (((iter.x * iter.x) + (iter.y * iter.y)) > 4)
				{
					pixel_x = (((iter.x - env->start_x) * (0.5 * WIDTH_SCREEN * env->zoom)) / 1.5) + (WIDTH_SCREEN * 0.5);
					pixel_y = (HEIGHT_SCREEN * 0.5) - (iter.y - env->start_y) * (0.5 * env->zoom * HEIGHT_SCREEN);
				//	if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN) 
				//	{
				//		env->data_addr[(int)((round(pixel_y) * WIDTH_SCREEN) + round(pixel_x))] = env->data_addr[(int)((round(pixel_y) * WIDTH_SCREEN) + round(pixel_x))] +  0x262626;
				//	}
					if (i > 3)
						env->data_addr[(y * WIDTH_SCREEN) + x] = i * 0x040404;
				}
			}
			x++;
		}
		y++;
	}	
	return (1);
}
