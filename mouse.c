/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:45:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 18:58:54 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			check_zone(int x, int y, t_env *env)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (x > env->screen[i]->min_x && x < env->screen[i]->max_x && y > env->screen[i]->min_y && y < env->screen[i]->max_y)
			return (env->screen[i]->order);
		i++;
	}
	return (0);
}

int			mouse_hook(int button, int x, int y, t_env *env)
{
	int		zone;

	zone = check_zone(x, y, env);
	if (zone == 1)
		zoom(button, x, y, env);
	return (0);
}

