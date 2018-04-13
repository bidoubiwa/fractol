/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:59:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/13 18:32:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_screen	**create_screens(t_screen **screens)
{
	int		i;

	i = 0;
	if (!(screens = ft_memalloc(sizeof(t_screen *) * 4)))
		return (NULL);
	while (i < 4)
	{
		if (!(screens[i] = ft_memalloc(sizeof(t_screen))))
			return (NULL);
		i++;
	}
	return (screens);
}


t_screen	**init_screens(t_screen **screen, char menu_on, char *param)
{
	int		i;
	int		p;

	i = 0;
	if (!(screen = create_screens(screen)))
		return (NULL);
	while (i < 4)
	{	
		p = get_order(param[0], i + 1);
		screen[i]->min_x = get_x_min(i + 1);
		screen[i]->max_x = get_x_max(i + 1, menu_on);
		screen[i]->min_y = get_y_min(i + 1);
		screen[i]->max_y = get_y_max(i + 1);
		screen[i]->width = ft_dim(screen[i]->max_x, screen[i]->min_x);
		screen[i]->height = ft_dim(screen[i]->max_y, screen[i]->min_y);
		get_screen_ratio((double)screen[i]->width,
				(double)screen[i]->height, screen[i]);
		if (!(screen[i]->fractal = get_fractal(p)))
			return (0);
		screen[i]->order = i + 1;
		i++;
	}
	return (screen);
}
