/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 19:11:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/09 20:31:04 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


/*void		clear_image(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->win_width * env->win_height)
	{
		if (env->data_addr[i] != 0)
			env->data_addr[i] = 0;
		i++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}*/

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

int			mouse_hook(int mouse_hook, t_env *env)
{
	(void)env;
	if (mouse_hook)
	{
		printf("%d\n", FocusOut);
	//	mlx_string_put(env->mlx, env->win, 50, 50, 0x00ffffff, ft_itoa(mouse_hook));
	}
	return (0);
}

void		events_listener(t_env *env)
{
	//mlx_key_hook(env->win, key_hook, env);
	mlx_mouse_hook(env->win, mouse_hook, env);
}
