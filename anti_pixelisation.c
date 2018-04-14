/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_pixelisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:08:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 21:20:31 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	followup(int *i, int *close, int sy, t_env *env)
{
	int				sx;
	t_screen		*scr;
	unsigned int	new;
	unsigned int	base;

	base = env->data_addr[get_pixel_index(i[0], i[1])];
	new = 0;
	scr = env->screen[0];
	sx = -1;
	while (sx < 2)
	{
		if (is_in_true_screen(scr, i[0] + sx, i[1] + sy) &&
				!(sx == 0 && sy == 0))
		{
			if (base == env->data_addr[get_pixel_index(sx + i[0], sy + i[1])])
				*close = *close + 1;
			new = merging(base, env->data_addr[get_pixel_index(sx + i[0],
						sy + i[1])], 0.1, 1);
		}
		sx++;
	}
	return (new);
}

void			pixel_cleanup(int x, int y, t_screen *scr, t_env *env)
{
	int				sy;
	unsigned int	new;
	int				close;
	int				i[2];

	(void)scr;
	i[0] = x;
	i[1] = y;
	new = 0;
	close = 0;
	sy = -1;
	while (sy < 2)
	{
		new = followup(i, &close, sy, env);
		sy++;
	}
	if (close < 2)
		env->data_addr[get_pixel_index(x, y)] = new;
}

void			pixel_contour(int x, int y, t_screen *scr, t_env *env)
{
	int				small_x;
	int				small_y;
	unsigned int	base;

	base = env->data_addr[get_pixel_index(x, y)];
	small_y = -1;
	while (small_y < 2)
	{
		small_x = -1;
		while (small_x < 2)
		{
			if (is_in_true_screen(scr, x + small_x, y + small_y) &&
					!(small_x == 0 && small_y == 0))
			{
				env->data_addr[get_pixel_index(x + small_x, y + small_y)] =
					merging(env->data_addr[get_pixel_index(x, y)],
							env->data_addr[get_pixel_index(x + small_x,
								y + small_y)], 0.1, 1);
			}
			small_x++;
		}
		small_y++;
	}
}

void			loop_around(void (*f)(int, int, t_screen*, t_env*), t_env *env,
		t_screen *scr)
{
	int			x;
	int			y;

	y = 0;
	while (y < scr->max_y)
	{
		x = 0;
		while (x < scr->max_x)
		{
			f(x, y, scr, env);
			x++;
		}
		y++;
	}
}

int				anti_pixelisation(t_env *env)
{
	t_screen	*scr;

	scr = env->screen[0];
	loop_around(&pixel_cleanup, env, scr);
	loop_around(&pixel_contour, env, scr);
	return (1);
}
