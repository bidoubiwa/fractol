/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:45:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 13:50:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int			mouse_hook(int button, int x, int y, t_env *env)
{
	//double	af_y;
	//double	af_x;
	unsigned int color;

	printf("button : %d\n", button);
	if (env->color && (x > WIDTH_SCREEN - env->color_size) && y < env->color_size)
	{
		color = env->data_addr[y * WIDTH_SCREEN + x];
		printf("color : %#x\n", color);	
	}
	else {
		mandelbrot_zoom(button, x, y, env);
	}
	return (0);
}


