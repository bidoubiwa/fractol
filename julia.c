/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:33:52 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/09 16:38:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iter_julia(t_iter *iter, int nbr_iter, t_screen *scr, int pixel)
{
	double	x_tmp;
	int		i;

	i = 0;
	while ( (iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		if (i > 0)
		{
			
		//	scr->data_addr[pixel]  = (i <= 255) ? rgb_to_hex(i, i, i) : rgb_to_hex(255, 255 - (i - 255), 
			//		255 - (i - 255)) ; 
			//scr->data_addr[pixel]  = (scr->data_addr[pixel] + (0x020202 * i) > 0xffffff)  ; 
			scr->data_addr[pixel] = scr->palettes[scr->palette][i % 5];
		}
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		i++;
	}
	return (0);
}

void	init_iter(t_iter *iter, t_screen *scr)
{
	iter->o_x = scr->fractal->const_x;
	iter->o_y = scr->fractal->const_y;
}

void	*thread_julia(void	*arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
	init_iter(&iter, scr);
	y = scr->min_y;
	while (y < scr->max_y)
	{
		x = scr->min_x;
		real_y  = 0 - (scr->ratio_y * (((y - scr->min_scr_y) - scr->height / 2.0) / 
			(0.5 * scr->fractal->zoom * scr->height))) + scr->fractal->start_y;
		while (x < scr->max_x)
		{
			iter.y = real_y;
			iter.x = scr->ratio_x * (((x - scr->min_scr_x) - scr->width / 2.0) / (0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
				iter_julia(&iter, scr->fractal->iteration, scr, ((y * WIDTH_SCREEN) + x));
			x++;
		}	
		y++;
	}
	pthread_exit(NULL);
}

int			julia(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'j');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);	
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_julia, (void *)screens[i]) == -1)
		{
			perror("pthread_create");
			return EXIT_FAILURE;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free_screens(screens);
	return (1);
}
