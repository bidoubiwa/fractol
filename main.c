/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:10:02 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/13 19:50:17 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		valid_argument(char *str)
{
	if (ft_strequ(str, "mandelbrot"))
		return (1);
	else if (ft_strequ(str, "julia"))
		return (1);
	else if (ft_strequ(str, "buddhabrot"))
		return (1);
	else if (ft_strequ(str, "anti-buddhabrot"))
		return (1);
	return (0);
}

void			display_screen_one(t_env *env)
{
	clear_zone(1, env);
	if (!env->screen[0]->fractal->f(env))
		safe_exit(env);
	if (env->anti_pixel)
		anti_pixelisation(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->show_info)
		display_info_menu(env);
}


void			display_fractals(t_env *env)
{
	int	i;

	i = 0;
	if (env->show_menu)
	{
		while (i < 4)
		{
			if (!env->screen[i]->fractal->f(env))
				safe_exit(env);
			i++;
		}
	}
	else
		env->screen[0]->fractal->f(env);
	if (env->anti_pixel)
		anti_pixelisation(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->show_info)
		display_info_menu(env);
}

int				main(int ac, char **av)
{
	t_env		env;
	t_screen	**screens;

	screens = NULL;
	if (!(ft_check_arguments("./fractol", ac, 1, 1)))
		return (0);
	if (!(valid_argument(av[1])))
		return (0);
	if (!(init_env(&env, av[1])))
		safe_exit(&env);
	if (!(env.screen = init_screens(screens, env.show_menu, env.param)))
		safe_exit(&env);
	else
	{
		display_fractals(&env);
		events_listener(&env);
		mlx_loop(env.mlx);
		free_fractal(screens);
		free_screens(screens);
	}
	return (0);
}
