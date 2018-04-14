/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:40:54 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/14 21:07:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_julia(t_fractal *fractal)
{
	fractal->f = &julia;
	fractal->iteration = 35;
	fractal->name = 'j';
	fractal->zoom = 0.5;
	fractal->const_x = 0.24;
	fractal->const_y = -0.56;
}

void	init_mandelbrot(t_fractal *fractal)
{
	fractal->f = &mandelbrot;
	fractal->iteration = 36;
	fractal->name = 'm';
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}

void	init_antibuddhabrot(t_fractal *fractal)
{
	fractal->f = &antibuddhabrot;
	fractal->name = 'a';
	fractal->iteration = 100;
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}

void	init_buddhabrot(t_fractal *fractal)
{
	fractal->name = 'b';
	fractal->f = &buddhabrot;
	fractal->iteration = 300;
	fractal->zoom = 0.5;
	fractal->const_x = 0;
	fractal->const_y = 0;
}
