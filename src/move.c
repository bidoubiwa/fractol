/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:00:58 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 17:11:53 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		move_keys(int button, t_env *env)
{
	t_screen	*scr;
	double		tmp;
	double		ratio;
	double		ratio_x;
	double		after_x;

	scr = env->screen[0];
	ratio = 1 / (scr->fractal->zoom + 20);
	ratio_x = scale_screen_x(scr, 0);
	after_x = scale_screen_x(scr, 35);
	ratio = ratio_x - after_x;
	tmp = scr->fractal->start_y;
	if (button == KEY_LEFT)
		scr->fractal->start_x = scr->fractal->start_x - ratio;
	else if (button == KEY_RIGHT)
		scr->fractal->start_x = scr->fractal->start_x + ratio;
	else if (button == KEY_UP)
		tmp = tmp + ratio;
	else if (button == KEY_DOWN)
		tmp = tmp - ratio;
	scr->fractal->start_y = tmp;
	display_screen_one(env);
	return (1);
}
