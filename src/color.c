/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:52:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 21:10:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			color_buddha(t_screen *scr, int pixel, int i)
{
	unsigned int	pal;

	pal = scr->palettes[scr->palette][i % 5];
	if (scr->palette == 4)
	{
		scr->data_addr[pixel] = merging_alpha(((i * (pal >> 16) % 255) << 16)
				+ (((i * (pal >> 8)) % 255) << 8)
				+ (i * (pal) % 255), scr->data_addr[pixel], 0.1);
	}
	else
		scr->data_addr[pixel] = merging_alpha(
				scr->palettes[scr->palette][i % 5], scr->data_addr[pixel], 0.1);
}

unsigned int	merging(unsigned int a, unsigned int o,
		double alpha, double beta)
{
	double			r;
	double			g;
	double			b;

	r = (double)(a >> 16) / 255.0 * alpha +
		((double)(o >> 16) / 255.0) * (beta * (1.0 - alpha));
	g = (double)((a >> 8) & 0xff) / 255.0 * alpha +
		((double)((o >> 8) & 0xff) / 255.0) * (beta * (1.0 - alpha));
	b = (double)(a & 0xff) / 255 * alpha +
		((double)(o & 0xff) / 255) * (beta * (1.0 - alpha));
	return (ft_rgb_to_hex(
				(int)round(r * 255), (int)round(g * 255), (int)round(b * 255)));
}

unsigned int	merging_alpha(unsigned int a, unsigned int o, double alpha)
{
	double			r;
	double			g;
	double			b;

	r = (double)(a >> 16) / 255.0 * alpha +
		(double)(o >> 16) / 255.0 * (1.0 - alpha);
	g = (double)((a >> 8) & 0xff) / 255.0 * alpha +
		(double)((o >> 8) & 0xff) / 255.0 * (1.0 - alpha);
	b = (double)(a & 0xff) / 255 * alpha +
		(double)(o & 0xff) / 255 * (1.0 - alpha);
	return (ft_rgb_to_hex((int)round(r * 255),
				(int)round(g * 255), (int)round(b * 255)));
}

unsigned int	merge_two_colors(unsigned int color1, unsigned int color2)
{
	int		r;
	int		g;
	int		b;

	r = ((color1 >> 16) + (color2 >> 16)) / 2;
	g = (((color1 >> 8) & 0xff) + ((color2 >> 8) & 0xff)) / 2;
	b = ((color1 & 0xff) + (color2 & 0xff)) / 2;
	return (ft_rgb_to_hex(r, g, b));
}
