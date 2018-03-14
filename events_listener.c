/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/14 18:48:15 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


void		clear_image(t_env *env)
{
	int		i;

	i = 0;
	while (i < HEIGHT_SCREEN * WIDTH_SCREEN)
	{
		if (env->data_addr[i] != 0)
			env->data_addr[i] = 0;
		i++;
	}
}

void			color_menu(t_env *env)
{
	if (!env->color)
	{
		draw_circle(env);	
		env->color = 1;
	}
	else
	{
		env->color = 1;
		clear_image(env);
		mandelbrot(env);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int			key_hook(int keycode, t_env *env)
{
	if (keycode == 123)
	{
		env->iter->o_x = env->iter->o_x - 0.01;
		clear_image(env);
		julia(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == 124)
	{
		env->iter->o_x = env->iter->o_x + 0.01;
		clear_image(env);
		julia(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == KEY_ESCAPE)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_FAILURE);
	}
	if (keycode == KEY_L)
	{
		if (env->loop)
			env->loop = 0;
		else
			env->loop = 1;
		printf("KEY L :  %d\n", env->loop);
	}

	if (keycode == KEY_C)
		color_menu(env);
	return (0);
}

int			mandelbrot_zoom(int button, int x, int y, t_env *env)
{
	t_screen	*scr;
	double	start_y;
	double	af_y;
	double	start_x;
	double	af_x;
	double old_zoom;

	scr = get_screen_ptr_by_fractal_name(env, 'm');

	// VERIFIER SI PT DANS FENETRE DU CENTRE
	old_zoom = scr->fractal->zoom;
	start_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * scr->fractal->zoom * HEIGHT_SCREEN));
	start_x =  1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * scr->fractal->zoom  * WIDTH_SCREEN);
	if (button == 2)
		scr->fractal->zoom = scr->fractal->zoom / 1.1;
	else
		scr->fractal->zoom = scr->fractal->zoom * 1.1;	
	af_x =  ((1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5  * scr->fractal->zoom * WIDTH_SCREEN)));
	af_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * scr->fractal->zoom * HEIGHT_SCREEN));
	if (af_x >= 0)
		scr->fractal->start_x = scr->fractal->start_x + fdim(fmax(af_x,start_x),fmin(af_x, start_x));
	else
		scr->fractal->start_x = scr->fractal->start_x - fdim(fmax(af_x,start_x), fmin(af_x, start_x));
	if (af_y >= 0)
		scr->fractal->start_y = scr->fractal->start_y + fdim(fmax(af_y,start_y), fmin(af_y, start_y));
	else
		scr->fractal->start_y = scr->fractal->start_y - fdim(fmax(af_y,start_y),fmin(af_y, start_y));
	scr->fractal->iteration = scr->fractal->iteration + 1;
	clear_image(env);
	mandelbrot(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

int		loop_hook( int x, int y, t_env *env)
{
	if (env->loop)
	{
		printf("x : %d y: %d\n", x, y);
	}
	return (1);
}

int			mouse_hook(int z, int x, int y, t_env *env)
{
	//double	af_y;
	//double	af_x;
	unsigned int color;

	printf("button : %d\n", z);
	if (env->color && (x > WIDTH_SCREEN - env->color_size) && y < env->color_size)
	{
		color = env->data_addr[y * WIDTH_SCREEN + x];
		printf("color : %#x\n", color);	
	}
	else {
		mandelbrot_zoom(z, x, y, env);
	}
	return (0);
}

void		events_listener(t_env *env)
{
//	mlx_loop_hook(env->win, loop_hook, env);
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
}
