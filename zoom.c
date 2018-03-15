/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:52:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 13:52:40 by cvermand         ###   ########.fr       */
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
	double old_zoom;

	scr = get_screen_ptr_by_fractal_name(env, 'm');

	// VERIFIER SI PT DANS FENETRE DU CENTRE
	old_zoom = scr->fractal->zoom;
	start_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * scr->fractal->zoom * HEIGHT_SCREEN));
	start_x =  1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * scr->fractal->zoom  * WIDTH_SCREEN);
	if (button == 2)
		scr->fractal->zoom = scr->fractal->zoom / 1.1;
	else
		scr->fractal->zoom = scr->fractal->zoom * 1.1;	
	af_x =  ((1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5  * scr->fractal->zoom * WIDTH_SCREEN)));
	af_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * scr->fractal->zoom * HEIGHT_SCREEN));
	if (af_x >= 0)
		scr->fractal->start_x = scr->fractal->start_x + fdim(fmax(af_x,start_x),fmin(af_x, start_x));
	else
		scr->fractal->start_x = scr->fractal->start_x - fdim(fmax(af_x,start_x), fmin(af_x, start_x));
	if (af_y >= 0)
		scr->fractal->start_y = scr->fractal->start_y + fdim(fmax(af_y,start_y), fmin(af_y, start_y));
	else
		scr->fractal->start_y = scr->fractal->start_y - fdim(fmax(af_y,start_y),fmin(af_y, start_y));
	scr->fractal->iteration = scr->fractal->iteration + 1;
	clear_image(env);
	mandelbrot(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

