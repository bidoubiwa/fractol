/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_hsv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:41:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 18:15:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;

	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

unsigned int	hsv_calculator(double hue, double saturation, double bright)
{
	double	c;
	double	m;
	double	x;
	int		cm;
	int		xm;

	c = bright * saturation;
	m = bright - c;
	x = c * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	cm = (int)round((c + m) * 255);
	xm = (int)round((x + m) * 255);
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex(cm, xm, (int)round(m * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex(xm, xm, (int)round(m * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round(m * 255), cm, xm));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(m * 255), xm, cm));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex(xm, (int)round(m * 255), cm));
	else
		return (rgb_to_hex(cm, (int)round((m) * 255), xm));
	return (0);
}
