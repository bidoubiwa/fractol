/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:52:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/10 17:26:53 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			zoom(int button, int x, int y, t_env *env)
{
	t_screen	*scr;
	double	start_y;
	double	af_y;
	double	start_x;
	double	af_x;

	if (env->julia_loop == 0)
	{
		scr = env->screen[0];
		start_y = 0 - (scr->ratio_y * ( (y - scr->height / 2.0) / (0.5 * scr->fractal->zoom * scr->height)));
		start_x = scr->ratio_x * (x - scr->width / 2.0) / (0.5 * scr->fractal->zoom  * scr->width);
		if (button == 2 ||  button == 4)
			scr->fractal->zoom = scr->fractal->zoom / 1.1;
		else if (button == 1 || button == 5)
			scr->fractal->zoom = scr->fractal->zoom * 1.1;
		af_x =  ((scr->ratio_x * (x - scr->width / 2.0) / (0.5  * scr->fractal->zoom * scr->width)));
		af_y = 0 - (scr->ratio_y * ((y - scr->height / 2.0) / (0.5 * scr->fractal->zoom * scr->height)));
		if (af_x >= 0)
			scr->fractal->start_x = scr->fractal->start_x + fdim(fmax(af_x,start_x),fmin(af_x, start_x));
		else
			scr->fractal->start_x = scr->fractal->start_x - fdim(fmax(af_x,start_x), fmin(af_x, start_x));
		if (af_y >= 0)
			scr->fractal->start_y = scr->fractal->start_y + fdim(fmax(af_y,start_y), fmin(af_y, start_y));
		else
			scr->fractal->start_y = scr->fractal->start_y - fdim(fmax(af_y,start_y),fmin(af_y, start_y));
		display_screen_one(env);
	}
	return (0);
}
