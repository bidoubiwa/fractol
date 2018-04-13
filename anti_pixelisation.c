/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_pixelisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:08:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/13 20:08:47 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int merging_alpha_beta(unsigned int a, unsigned int o, double alpha, double beta)
{
	double			r;
	double			g;
	double			b;

	r = (double)(a >> 16) / 255.0 * alpha + ((double)(o >> 16) / 255.0) * (beta * (1.0 - alpha));
	g = (double)((a >> 8) & 0xff) / 255.0 * alpha + ((double)((o >> 8) & 0xff) / 255.0) * (beta * (1.0 - alpha));
	b = (double)(a & 0xff) / 255 * alpha + ((double)(o & 0xff) / 255) * (beta * (1.0 - alpha));
	return (ft_rgb_to_hex((int)round(r * 255),(int)round(g * 255),(int)round(b * 255)));
}

void		pixel_contour(int x, int y, t_screen *scr, t_env *env)
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
			if (is_in_true_screen(scr, x + small_x, y + small_y))
			{
				env->data_addr[get_pixel_index(x, y)] = merging_alpha_beta(
						env->data_addr[get_pixel_index(x, y)], 
						env->data_addr[get_pixel_index(x + small_x, y + small_y)], 0.5, 1);
			}
			small_x++;
		}
		small_y++;
	}
}

int					anti_pixelisation(t_env *env)
{
	int			x;
	int			y;
	t_screen	*scr;

	y = 0;
	scr = env->screen[0];
	while (y < scr->max_y)
	{
		x = 0;
		while (x < scr->max_y)
		{
			pixel_contour(x, y, scr, env);
			x++;
		}
		y++;
	}
	return (1);
}

