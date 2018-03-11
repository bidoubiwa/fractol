/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_circle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:37:00 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/11 19:36:12 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		draw_circle(t_env *env)
{
	int		y;
	int		x;
	double	real_y;
	double	real_x;

	double	saturation;
	double	hue;

	y = 0;
	while (y < env->color_size)
	{
		x = WIDTH_SCREEN - env->color_size;
		real_y = 0 - (y - (double)env->color_size / 2.0) / (0.5 * env->color_size);
		while (x < WIDTH_SCREEN)
		{
			real_x = ((WIDTH_SCREEN - x) - env->color_size / 2.0) / (0.5 * env->color_size);
			if ((real_x * real_x) + (real_y * real_y) <= 1)
			{
				if (real_y == 0 && real_x >= 0)
					hue = 0;
				else if (real_y == 0 && real_x < 0)
					hue = 180;
				else if (real_x == 0 && real_y > 0)
					hue = 90;
				else if (real_x == 0 && real_y < 0)
					hue = 270;
				else	
					hue = ft_to_degrees(atan2(real_y,real_x));
				saturation = sqrt((real_x * real_x) + (real_y * real_y));
				printf("x : %f y : %f hue : %d\n", real_x, real_y, (int)round(hue));
				env->data_addr[(y * WIDTH_SCREEN) + x]  = hsv_calculator((int)round(hue), 1);
//				env->data_addr[(y * WIDTH_SCREEN) + x]  = 0x00FF0000;
				
			}
			x++;
		}
		y++;
	}
}
