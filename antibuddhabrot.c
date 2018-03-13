/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 14:58:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		antibuddhabrot(t_env *env)
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
					if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN && i > 20) 
					{

						env->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] = env->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] + 0x040404;
					}	
					x_tmp = iter.x;
					y_tmp = iter.y;
					iter.x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + real_x;
					iter.y = 2 * (x_tmp * y_tmp) + real_y;
				
					pixel_x = (((iter.x - env->start_x) * (0.5 * WIDTH_SCREEN * env->zoom)) / 1.5) + (WIDTH_SCREEN * 0.5);
					pixel_y = (HEIGHT_SCREEN * 0.5) - (iter.y - env->start_y) * (0.5 * env->zoom * HEIGHT_SCREEN);
					
					i++;
				}
			}
			x++;
		}
		y++;
	}	
	return (1);
}
