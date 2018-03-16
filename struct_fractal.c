/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:35:54 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/16 14:57:17 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_screen		*get_screen_ptr_by_fractal_name(t_env *env, char c)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		if (env->screen[i]->fractal->name == c)
			return (env->screen[i]);
		i++;
	}
	return (env->screen[0]);
}


int			get_screen_by_fractal_name(t_env *env, char c)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		if (env->screen[i]->fractal->name == c)
			return (i);
		i++;
	}
	return (i);
}

void		free_fractal(t_screen	**screens)
{
	int			i;
	t_fractal	*fractal;

	i = 0;
	while (i < 4)
	{
		fractal = screens[i]->fractal;
		free(fractal);
		screens[i]->fractal = NULL;
		i++;
	}
}

t_fractal		*get_fractal(int order)
{
	t_fractal	*fractal;

	if (!(fractal = ft_memalloc(sizeof(t_fractal))))
		return (NULL);
	fractal->start_x = 0;
	fractal->start_y = 0;	
	if (order == 1)
		init_mandelbrot(fractal);
	else if (order == 2)
		init_julia(fractal);
	else if (order == 3)
		init_buddhabrot(fractal);
	else if (order == 4)
		init_antibuddhabrot(fractal);
	return (fractal);
}
