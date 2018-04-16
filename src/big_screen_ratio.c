/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_screen_ratio.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:27:14 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 17:39:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		scale_big_screen_y(t_screen *scr, int y)
{
	double real_y;

	real_y = 0 - (scr->ratio_y * ((y - scr->height / 2.0)
				/ (0.5 * scr->fractal->zoom * scr->height)));
	return (real_y);
}

double		scale_big_screen_x(t_screen *scr, int x)
{
	double real_x;

	real_x = scr->ratio_x * ((x - scr->width / 2.0) /
			(0.5 * scr->fractal->zoom * scr->width));
	return (real_x);
}
