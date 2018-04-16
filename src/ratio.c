/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:08:01 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 17:13:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		scale_screen_y(t_screen *scr, int y)
{
	double real_y;

	real_y = 0 - (scr->ratio_y * (((y - scr->min_scr_y) - scr->height / 2.0)
				/ (0.5 * scr->fractal->zoom * scr->height)))
				+ scr->fractal->start_y;
	return (real_y);
}

double		scale_screen_x(t_screen *scr, int x)
{
	double real_x;

	real_x = scr->ratio_x * (((x - scr->min_scr_x) - scr->width / 2.0) /
			(0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
	return (real_x);
}

int			reverse_scale_screen_x(t_screen *scr, double iter)
{
	double pixel_x;

	pixel_x = (((iter - scr->fractal->start_x) *
				(0.5 * scr->width * scr->fractal->zoom)) / scr->ratio_x)
				+ (scr->width * 0.5) + scr->min_scr_x;
	return ((int)round(pixel_x));
}

int			reverse_scale_screen_y(t_screen *scr, double iter)
{
	double pixel_y;

	pixel_y = (scr->height * 0.5) - (iter - scr->fractal->start_y) *
		((0.5 * scr->fractal->zoom * scr->height) / scr->ratio_y)
		+ scr->min_scr_y;
	return ((int)round(pixel_y));
}

int			get_pixel_index(int pixel_x, int pixel_y)
{
	return ((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x);
}
