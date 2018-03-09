/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/09 22:34:33 by cvermand         ###   ########.fr       */
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
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

/*int			key_hook(int keycode, t_env *env)
{
	if (keycode == 83 || keycode == 84 || keycode == 86 ||
			keycode == 88 || keycode == 91 || keycode == 92)
		rotation(env, keycode);
	if (keycode == 78 || keycode == 69)
		zoom(env, keycode);
	if (keycode >= 123 && keycode <= 126)
		movement(env, keycode);
	if (keycode == 49)
		reset(env);
	if (keycode == 53)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		free_all(env, env->matrix);
		exit(EXIT_FAILURE);
	}
	return (0);
}*/

int			mouse_hook(int z, int x, int y, t_env *env)
{
	t_lim	lim;
	double	mouse_y;
	double	mouse_x;
	double	start_y;
	double	start_x;

	//(void)env;
	printf("et si\n");
	(void)z;
	init_plane(env, &lim);
	//real_y = y_plane_coord(y, &lim);
	//real_x = x_plane_coord(x, &lim);
	start_y = (y - HEIGHT_SCREEN / 2.0) / (0.5 * 1.25 * HEIGHT_SCREEN);
	start_x =  1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * 1.25 * WIDTH_SCREEN);
	mouse_y = (y - HEIGHT_SCREEN / 2.0) / (0.5 * 1.25 * HEIGHT_SCREEN) + start_y;
	mouse_x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * 1.25 *WIDTH_SCREEN) + start_x;
	mlx_string_put(env->mlx, env->win, 50, 50, 0x00ffffff, ft_itoa(x));
	mlx_string_put(env->mlx, env->win, 50, 100, 0x00ffffff, ft_itoa(y));
	env->zoom = env->zoom + 0.5;	
//	printf("x : %d y : %d \n", x, y);
//	printf("real_x : %f real_y : %f \n", real_x, real_y);

//	x_tmp = real_x;
//	real_x = (x_tmp * x_tmp) - (real_y * real_y) + x_tmp;
//	real_y = 2 * (x_tmp * real_y) + real_y; 
//	printf("real_x : %f real_y : %f \n", real_x, real_y);
	clear_image(env);
	mandelbrot(env, mouse_x, mouse_y);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);

	return (0);
}

void		events_listener(t_env *env)
{
	//mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
}
