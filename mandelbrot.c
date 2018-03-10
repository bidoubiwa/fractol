/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/10 19:33:11 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*int		iter_mandel(t_iter *iter, int nbr_iter, t_env *env, int pixel)
  {
//double x_tmp;
int			i;

i = 0;
while (i <= nbr_iter)
{
//	x_tmp = iter->x;
//	iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
//	iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
//	if ((iter->x * iter->x) + (iter->y * iter->y) <= 4)
//	{
env->data_addr[pixel] = 0xFFFFFF;
//	}
//	return (iter_mandel(iter, nbr_iter - 1 , env, pixel));
i++;
}
return (0);
}*/


int		mandelbrot(t_env *env)
{
	int		x;
	int		y;
	int		i;
	t_iter	iter;
	double	real_y;
	double	real_x;
	double x_tmp;
	double y_tmp;

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
					env->data_addr[(y * WIDTH_SCREEN) + x] = palette(i);
					i++;
				}
			}
			x++;
		}
		y++;
	}	
	return (1);
}
