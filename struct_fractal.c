/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:35:54 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 17:43:13 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			get_screen_by_fractal_name(t_env *env, char c)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		dprintf(1,"i : %d name : %c\n", i , env->screen[i].fractal->name);
		if (env->screen[i].fractal->name == c)
			return (i);
		i++;
	}
	return (i);
}

t_fractal		*get_fractal(int order)
{
	t_fractal	*fractal;

	if (!(fractal = ft_memalloc(sizeof(t_fractal))))
		return (NULL);
	if (order == 1 || order == 2)
	{
		fractal->f = (order == 1) ? &mandelbrot : &julia;
		fractal->iteration = (order == 1) ? 15 : 35;
		fractal->name = (order == 1) ? 'm' : 'j';
		fractal->iteration = 15;
		fractal->zoom = 0.5;
	}
	else if (order == 3)
	{
		fractal->f = &antibuddhabrot;
		fractal->name = 'a';
		fractal->iteration = 100;
		fractal->zoom = 0.5;
	}
	else if (order == 4)
	{
		fractal->name = 'b';
		fractal->f = &buddhabrot;
		fractal->iteration = 100;
		fractal->zoom = 0.5;
	}
	return (fractal);
}
