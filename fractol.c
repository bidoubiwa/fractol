/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 16:52:29 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_env *env, t_iter *iter)
{
	env->show_menu = 1;
	env->loop = 0;
	env->color = 0;
	env->color_size = 200;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "titre");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	env->data_addr = (unsigned int*)mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->bytes_per_line, &env->endian);
}

void		display_screen_one(t_env *env)
{
	env->screen[0]->fractal->f(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

void		display_fractals(t_env *env)
{
	int	i;

	i = 0;
		
	if (env->show_menu)
	{
		while (i < 4)
		{
			env->screen[i]->fractal->f(env);
			i++;
		}
	}
	else
		env->screen[0]->fractal->f(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

int		main()
{
	t_env		env;
	t_iter		iter;
	t_screen	**screens;
	
	init_mlx(&env, &iter);
	if (!(env.screen = init_screens(screens, env.show_menu)))
		return (ft_printf("Initiation of screens went wrong"));
	display_fractals(&env);
	events_listener(&env);
	mlx_loop(env.mlx);
	free_fractal(screens);
	free_screens(screens);
	return (0);
}


