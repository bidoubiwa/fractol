/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:09:03 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 14:52:40 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_screen_ratio(double width, double height, t_screen *screen)
{
	if (width >= height)
	{
		screen->ratio_x = width / height;
		screen->ratio_y = 1;
	}
	else
	{
		screen->ratio_x = 1;
		screen->ratio_y = height / width;
	}
}

int			get_x_min(int order)
{
	if (order == 1)
		return (0);
	else
		return (WIDTH_SCREEN - (WIDTH_SCREEN / 5));
}

int			get_x_max(int order)
{
	(void) order;	
	return (WIDTH_SCREEN);
}

int			get_y_min(int order)
{
	if (order == 1 || order == 2)
		return (0);
	else if (order == 3)
		return (HEIGHT_SCREEN / 3);
	else
		return (HEIGHT_SCREEN - (HEIGHT_SCREEN / 3));
}

int			get_y_max(int order)
{
	if (order == 1 || order == 4)
		return (HEIGHT_SCREEN);
	else if (order == 2)
		return (HEIGHT_SCREEN / 3);
	else
		return (HEIGHT_SCREEN - (HEIGHT_SCREEN / 3));
}
