/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:52:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 17:39:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		x_new_pos(t_screen *scr, double start_x, double af_x, char zoom)
{
	if (zoom)
	{
		if (af_x >= 0)
			scr->fractal->start_x = scr->fractal->start_x +
				fdim(fmax(af_x, start_x), fmin(af_x, start_x));
		else
			scr->fractal->start_x = scr->fractal->start_x -
				fdim(fmax(af_x, start_x), fmin(af_x, start_x));
	}
	else
	{
		if (af_x >= 0)
			scr->fractal->start_x = scr->fractal->start_x -
				fdim(fmax(af_x, start_x), fmin(af_x, start_x));
		else
			scr->fractal->start_x = scr->fractal->start_x +
				fdim(fmax(af_x, start_x), fmin(af_x, start_x));
	}
}

void		y_new_pos(t_screen *scr, double start_y, double af_y, char zoom)
{
	if (zoom)
	{
		if (af_y >= 0)
			scr->fractal->start_y = scr->fractal->start_y +
				fdim(fmax(af_y, start_y), fmin(af_y, start_y));
		else
			scr->fractal->start_y = scr->fractal->start_y -
				fdim(fmax(af_y, start_y), fmin(af_y, start_y));
	}
	else
	{
		if (af_y >= 0)
			scr->fractal->start_y = scr->fractal->start_y -
				fdim(fmax(af_y, start_y), fmin(af_y, start_y));
		else
			scr->fractal->start_y = scr->fractal->start_y +
				fdim(fmax(af_y, start_y), fmin(af_y, start_y));
	}
}

int			zoom(int button, int x, int y, t_env *env)
{
	t_screen	*scr;
	double		start_y;
	double		af_y;
	double		start_x;
	double		af_x;

	if (env->julia_loop == 0)
	{
		scr = env->screen[0];
		start_x = scale_big_screen_x(scr, x);
		start_y = scale_big_screen_y(scr, y);
		if (button == 2 || button == 4)
			scr->fractal->zoom = scr->fractal->zoom / 1.1;
		else if (button == 1 || button == 5)
			scr->fractal->zoom = scr->fractal->zoom * 1.1;
		af_x = scale_big_screen_x(scr, x);
		af_y = scale_big_screen_y(scr, y);
		(button == 2 || button == 4) ? y_new_pos(scr, start_y, af_y, 0) :
			y_new_pos(scr, start_y, af_y, 1);
		(button == 2 || button == 4) ? x_new_pos(scr, start_x, af_x, 0) :
			x_new_pos(scr, start_x, af_x, 1);
		display_screen_one(env);
	}
	return (0);
}
