/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:33:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/11 17:15:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iter_julia(t_iter *iter, int nbr_iter, t_env *env, int pixel)
{
	double x_tmp;
	int		i;

	i = 0;
	while (i <= nbr_iter)
	{
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		if ((iter->x * iter->x) + (iter->y * iter->y) <= 4)
		{
			env->data_addr[pixel]  = palette(i);
		}
	//	return (iter_julia(iter, nbr_iter - 1 , env, pixel));
		i++;
	}
	return (0);
}


int		julia(t_env *env, t_iter *iter)
{
	int		x;
	int		y;
	double	real_y;

	y = 0;
	while (y < HEIGHT_SCREEN)
	{
		x = 0;
		real_y  = (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN) + env->start_y;
		while (x < WIDTH_SCREEN)
		{
			iter->y = real_y;
			iter->x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom * WIDTH_SCREEN) + env->start_x ;
//			printf("c x : %f c y : %f x : %f y : %f\n", iter->o_x, iter->o_y, iter->x, iter->y);
			if (iter->x >= -2 && iter->x <= 2 && iter->y <= 2 && iter->y >= -2)
			{
				iter_julia(iter, env->iteration, env, (y * WIDTH_SCREEN) + x);
			}
			x++;
		}	
		y++;
	}
	return (1);
}
