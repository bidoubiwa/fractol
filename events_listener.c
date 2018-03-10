/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/10 19:48:27 by cvermand         ###   ########.fr       */
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
//	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int			key_hook(int keycode, t_env *env)
{
	if (keycode == 123)
	{
		env->iter->o_x = env->iter->o_x - 0.1;
		clear_image(env);
		julia(env, env->iter);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == 124)
	{
		env->iter->o_x = env->iter->o_x + 0.1;
		printf("x iter : %f\n", env->iter->o_x);
		clear_image(env);
		julia(env, env->iter);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	}
	if (keycode == 53)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int			mouse_hook(int z, int x, int y, t_env *env)
{
	double	start_y;
	double	af_y;
	double	start_x;
	double	af_x;
	double old_zoom;
	//(void)env;
	(void)z;
	//printf("Zoom avt : %f zoom apres : %f \n", env->zoom, env->zoom + 0.5);	
	printf("x : %d y: %d\n",x, y);
	//env->start_y = (y - HEIGHT_SCREEN / 2.0) / (0.5  * HEIGHT_SCREEN);
	old_zoom = env->zoom;
	start_x =  1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom  * WIDTH_SCREEN);
	start_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN));	
	//printf("r bef : %f i bef: %f\n",start_x,start_y);
	env->zoom = env->zoom + 0.3;	
	af_x =  ((1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5  * env->zoom * WIDTH_SCREEN)));
	af_y = 0 - ( (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN));

	printf("%8f | %8f | %8f\n", old_zoom, start_x, start_y);
	printf("%8f | %8f | %8f\n", env->zoom, af_x, af_y);
	if (af_x >= 0)
		env->start_x = env->start_x + fdim(fmax(af_x,start_x),fmin(af_x, start_x));
	else
		env->start_x = env->start_x - fdim(fmax(af_x,start_x), fmin(af_x, start_x));
	if (af_y >= 0)
		env->start_y = env->start_y + fdim(fmax(af_y,start_y), fmin(af_y, start_y));
	else
		env->start_y = env->start_y - fdim(fmax(af_y,start_y),fmin(af_y, start_y));
	//printf("r : %f i: %f\n",env->start_x,env->start_y);
	printf("max : %f min : %f\n", fmax(af_y, start_y), fmin(af_y, start_y));
//	printf("%8s | %8s | %8s\n", "zoom", "r", "i");
//	printf("------------------------------------------------------------------\n");
//	if (old_zoom == 0.5)
	printf("%8f | %8f | %8f\n", env->zoom, env->start_x, env->start_y);

	env->iteration = env->iteration + 2;
	//env->start_x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom *WIDTH_SCREEN) + start_x;
	clear_image(env);
	mandelbrot(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);

	return (0);
}

void		events_listener(t_env *env)
{
	mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
}