/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 17:44:57 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/14 18:00:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_screen	**create_tmp_screens(t_screen **screens)
{
	int		i;
	
	if (!(screens = ft_memalloc(sizeof(t_screen *) * 4)))
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!(screens[i] = malloc(sizeof(t_screen))))
				return (0);
		i++;
	}
	return (screens);
}

t_screen	**init_tmp_screens_info(t_screen **screens, t_env *env, int nbr_scr)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		screens[i]->fractal = env->screen[nbr_scr]->fractal;
		screens[i]->width = env->screen[nbr_scr]->width;
		screens[i]->height = env->screen[nbr_scr]->height;
		screens[i]->data_addr = env->data_addr;
		screens[i]->min_scr_x = env->screen[nbr_scr]->min_x;
		screens[i]->min_scr_y = env->screen[nbr_scr]->min_y;	
		screens[i]->ratio = env->screen[nbr_scr]->ratio;	
		i++;
	}
	return (screens);
}

t_screen	**init_args(t_screen **screens, int nbr_scr, t_env *env)
{
	int		i;
	
	if (!(screens = create_tmp_screens(screens)))
		return (NULL);	
	screens = init_tmp_screens_info(screens, env, nbr_scr);		
	init_arg_limits(env->screen[nbr_scr]->min_x , 
			env->screen[nbr_scr]->min_y, screens[0], env);
	init_arg_limits(env->screen[nbr_scr]->min_x + env->screen[nbr_scr]->width / 2, 
			env->screen[nbr_scr]->min_y , screens[1], env);
	init_arg_limits(env->screen[nbr_scr]->min_x, 
			env->screen[nbr_scr]->min_y + env->screen[nbr_scr]->height / 2, 
			screens[2], env);	
	init_arg_limits(env->screen[nbr_scr]->min_x + env->screen[nbr_scr]->width / 2, 
			env->screen[nbr_scr]->min_y + env->screen[nbr_scr]->height / 2, 
			screens[3], env);
	return (screens);
}


void	init_arg_limits(int min_x, int min_y, t_screen *screen, t_env *env)
{
	screen->min_x = min_x;
	screen->max_x = screen->min_x + screen->width / 2;
	screen->min_y = min_y;
	screen->max_y = screen->min_y + screen->height / 2;
}

