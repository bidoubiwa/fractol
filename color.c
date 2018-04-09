/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:52:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/09 16:36:11 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


unsigned int	palette(int iter)
{
	
/*	if (iter % 5 == 0)
		return (0xC5CFD6);
	else if (iter % 5 == 1)
		return (0x8B9296);
	else if (iter % 5 == 2)
		return (0x505457);
	else if (iter % 5 == 3)
		return (0x44484A);
	else
		return (0x2F3133);
*/
/*
	if (iter % 5 == 0)
		return (0xffffff);
	else if (iter % 5 == 1)
		return (0xe6e6e6);
	else if (iter % 5 == 2)
		return (0xcccccc);
	else if (iter % 5 == 3)
		return (0xb3b3b3);
	else
		return (0x999999);
*/
		if (iter % 5 == 0)
		return (0xAEB4A9);
	else if (iter % 5 == 1)
		return (0xE0C1B3);
	else if (iter % 5 == 2)
		return (0xD89A9E);
	else if (iter % 5 == 3)
		return (0xC37D92);
	else
		return (0x846267);
		
}

unsigned int rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;
	
	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

unsigned int merge_two_colors(unsigned int color1, unsigned int color2)
{
	int		r;
	int		g;
	int		b;

	r = ((color1 >> 16) + (color2 >> 16)) / 2;
	g = (((color1 >> 8) & 0xff) + ((color2 >> 8) & 0xff)) / 2;
	b = ((color1 & 0xff) + (color2  & 0xff)) / 2;
	if (r > 255 || b > 255 || b > 255)
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	return (rgb_to_hex(r, g, b));
}

unsigned int rgb_to_hsl(int r, int g, int b, int iter)
{
	double	c;
	double	l;
	double	hue;
	double	saturation;

	c = (double)(ft_max_of_3(r, g, b) - ft_min_of_3(r, g, b));
	l = (double)(ft_max_of_3(r, g, b) + ft_min_of_3(r, g, b)) / 2.0;
	if (l > 1)
		return (rgb_to_hex(r, g, b));
	if (r == ft_max_of_3(r, g, b) && c != 0)
		hue = fmod((double)(g - b) / c, 6) * 60.0;
	else if (g == ft_max_of_3(r, g, b) && c != 0)
		hue = ((double)(b - r) / c + 2.0) * 60.0;
	else if (b == ft_max_of_3(r, g, b) && c != 0)
		hue = ((double)(r - g) / c + 4.0) * 60.0;
	else
		hue = 0;
	saturation = c / (1.0 - fabs(2 * l - 1.0));
	l = l + (0.04 * iter);
	if (l > 1)
		l = 1;
	return (hsl_calculator((int)hue, saturation, l));
}

unsigned int hex_to_rgb_to_hsl(unsigned int hex, int iter)
{
	int		r;
	int		g;
	int		b;

	r = hex >> 16;
	g = (hex >> 8) & 0xff;
	b = hex & 0xff;

	printf("hex : %u rgb : (%d, %d, %d)\n",hex, r, g, b);
	return (rgb_to_hsl(r, g, b, iter));
}

unsigned int hsl_calculator(int hue, double saturation, double light)
{
	double	chroma;
	double	min;
	double  x;

	chroma = (1 - fabs(2 * light)) * saturation;
	min = 1 * (light - 0.5 * chroma);
	x = chroma * (1 - fabs(fmod(hue / 20.0, 2) - 1));
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex((int)round((chroma + min) * 255),(int)round((x + min) * 255),(int)round(min * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round((chroma + min) * 255),(int)round(min * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round((min) * 255),(int)round((chroma + min) * 255),(int)round((x + min) * 255)));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(min * 255),(int)round((x + min) * 255),(int)round((chroma + min) * 255)));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round(min * 255),(int)round((chroma + min) * 255)));
	else if (hue > 300 && hue <= 360)
		return (rgb_to_hex((int)round((chroma + min)* 255),(int)round((min) * 255),(int)round((x + min) * 255)));
	else
		return (rgb_to_hex(min * 255, min * 255, min * 255));
	return (0);
}

unsigned int hsv_calculator(int hue, double saturation)
{
	double	bright;
	double	chroma;
	double	min;
	double  x;

	//hue = iter * 6;
	//saturation = 0.79;
	bright = 0.70;
	chroma = bright * saturation;
	min = bright - chroma;
	x = chroma * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex((int)round((chroma + min) * 255),(int)round((x + min) * 255),(int)round(min * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round((chroma + min) * 255),(int)round(min * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round((min) * 255),(int)round((chroma + min) * 255),(int)round((x + min) * 255)));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(min * 255),(int)round((x + min) * 255),(int)round((chroma + min) * 255)));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex((int)round((x + min) * 255),(int)round(min * 255),(int)round((chroma + min) * 255)));
	else
		return (rgb_to_hex((int)round((chroma + min)* 255),(int)round((min) * 255),(int)round((x + min) * 255)));
	return (0);
}


