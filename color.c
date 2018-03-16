/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:52:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/16 17:53:49 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;
	
	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

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


