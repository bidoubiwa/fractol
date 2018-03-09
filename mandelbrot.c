/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/09 17:53:51 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_plane(t_env *env, t_lim *lim)
{
	(void) env;
	lim->min_w = -3;
	lim->max_w = 3;
	lim->max_h = 2;
	lim->min_h = -2;
}

double	y_plane_coord(int y, t_lim *lim)
{
	double		h_scale;
	double		i_scale;
	double		dim;

	h_scale = 1 - ((double)y / (double)HEIGHT_SCREEN);
	dim = fdim((double)lim->max_h, (double)lim->min_h);
	//printf("dim : %f  ", dim);
	i_scale = (dim * h_scale) - dim / 2;
	return (i_scale);
}

double	x_plane_coord(int x, t_lim *lim)
{
	double		w_scale;
	double		x_scale;
	double		dim;

	w_scale = ((double)x / (double)WIDTH_SCREEN);
	dim = fdim((double)lim->max_w, (double)lim->min_w);
//	printf("dim : %f  ", dim);
	x_scale = (dim * w_scale) - dim / 2;
	return (x_scale);
}

int		iter_mandel(t_iter *iter, int nbr_iter, t_env *env, int pixel)
{
	double x_tmp;

	if (nbr_iter == 0)
		return (0);
	else
	{
		//dire = iter->x * iter->x + (2 * iter->x * iter->y) - iter->y * iter->y + iter->o_x + iter->o_y;
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = (x_tmp * iter->y) + (x_tmp * iter->y) + iter->o_y; 
		//x_dim = fdim((double)lim->max_w, (double)lim->min_w);
//		printf("dire : %f ", dire);
		if (iter->x >= -2 && iter->x <= 2 && iter->y <= 2 && iter->y >= -2)
		{
//			printf("pos : %d x : %f y : %f ",pixel, x_tmp, iter->y);
//			printf("new x : %f new y : %f \n", iter->x, iter->y);
			if (nbr_iter == 3)
				env->data_addr[pixel]  = mlx_get_color_value(env->mlx, 0x00FFFFFF);
			else if  (nbr_iter == 2)
				env->data_addr[pixel]  = mlx_get_color_value(env->mlx, 0x00FF0000);
			else 
				env->data_addr[pixel]  = mlx_get_color_value(env->mlx, 0x0000FF00);
	}
		return (iter_mandel(iter, nbr_iter - 1 , env, pixel));
	}

}


int		mandelbrot(t_env *env)
{
	t_lim	lim;
	int		x;
	int		y;
	t_iter	iter;
	double	real_y;
	double	real_x;

	init_plane(env, &lim);
	y = 0;
	real_y = 0;
	while (y < HEIGHT_SCREEN)
	{
		x = 0;
		real_y = y_plane_coord(y, &lim);
	//	printf("i : %f\n", real_y);
		while (x < WIDTH_SCREEN)
		{
			real_x = x_plane_coord(x, &lim);
		//	printf("x : %f\n", real_x);
			iter.o_x = real_x;
			iter.o_y = real_y;
			iter.x = real_x;
			iter.y = real_y;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
			{
			//	printf("x : %d y : %d x : %f y : %f \n", x, y, iter.x, iter.y);
				iter_mandel(&iter, env->iter, env, (y * WIDTH_SCREEN) + x);
			}
			x++;
		}	
		y++;
	}
	return (1);
}
