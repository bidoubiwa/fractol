/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/13 19:16:01 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_env *env, t_iter *iter)
{
	//env->start_x = -0.25;
	env->loop = 0;
	env->color = 0;
	env->color_size = 200;
	env->start_x = 0.00;
	env->start_y = 0.00;
	env->zoom = 0.5;
	env->iteration = 45;
	env->iter = iter;
	iter->o_x = 0.4;
	iter->x = 0;
	iter->o_y = 0.6;	
	iter->y = 0;	
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "titre");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	env->data_addr = (unsigned int*)mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->bytes_per_line, &env->endian);
}

int		init_screen(t_screen *screen, int i)
{
	screen->min_x = get_x_min(i + 1);
	screen->max_x = get_x_max(i + 1);
	screen->min_y = get_y_min(i + 1);
	screen->max_y = get_y_max(i + 1);
	screen->width = ft_dim(screen->max_x, screen->min_x);
	screen->height = ft_dim(screen->max_y, screen->min_y);
	if (!(screen->fractal = get_fractal(i + 1)))
		return (0);
	screen->order = i;
	return (1);
}

int		main()
{
	t_env		env;
	t_iter		iter;
	t_screen	screens[4];
	int			i;
	
	i = 0;
	init_mlx(&env, &iter);
	env.screen = screens;
	while (i < 4)
	{
		if (!(init_screen(&screens[i], i)))
			return (ft_printf("MALLOC A PETE"));
		i++;
	}
	i = 0;
	while (i < 4)
	{
		dprintf(1,"min x : %d max x : %d min y : %d max y : %d width : %d height : %d\n",
			env.screen[i].min_x, env.screen[i].max_x, env.screen[i].min_y, env.screen[i].max_y, env.screen[i].width, env.screen[i].height);
		dprintf(1,"name : %c\n", env.screen[i].fractal->name);
		i++;
	}
	//env.screen[0].fractal->f(&env);
	env.screen[1].fractal->f(&env);
	//mandelbrot(&env);
	//antibuddhabrot(&env);
	//buddhabrot(&env)
	//	julia(&env, &iter);
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	events_listener(&env);
	mlx_loop(env.mlx);
}

/*	while (i < 4)
	{
		c_env[i].zoom = env->screen[nbr].fractal->zoom;
		c_env[i].iteration = env->screen[nbr].fractal->iteration;
		c_env[i].width = env->screen[nbr].width;
		c_env[i].height = env->screen[nbr].height;
		i++;
	}*/

