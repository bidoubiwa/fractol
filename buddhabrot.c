/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/17 18:48:13 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		first_iter_buddha(t_iter *iter, int nbr_iter, int *i)
{
	double	x_tmp;

	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && *i <= nbr_iter)
	{
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		*i = *i + 1;
	}
}

void		correct_path_iter(t_iter *iter, int nbr_iter, t_screen *scr)
{
	int				i;
	double			pixel_x;
	double			pixel_y;
	double			x_tmp;
	unsigned int	color;
	int				hue;
	int				pos;

	hue = ft_to_degrees(atan2(iter->x, iter->y));
	if (hue < 0)
		hue = hue + 360;
	if (hue > 360 || hue < 0)
		printf("hue : %d\n", hue);	
	color = hsl_calculator((int)round(hue), 1.0, 0.4);
//	ft_printf("color: %#x\n", color);
	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		pos = ((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x);
		if ((int)round(pixel_x) >= scr->min_scr_x && (int)round(pixel_x) <= scr->max_scr_x
				&& (int)round(pixel_y) >= scr->min_scr_y && (int)round(pixel_y) <= scr->max_scr_y && i > 50)
		{
			//printf("i :%d\n", i);
			color = hsl_calculator((int)round(hue), 1.0, (i - 50) * 0.04);
			if (scr->data_addr[pos])
				scr->data_addr[pos] = color;
			else
				scr->data_addr[pos] = merge_two_colors(scr->data_addr[pos], color);
			/*		if (i == 51)
				scr->data_addr[pos] = color;
			else
				scr->data_addr[pos] = hex_to_rgb_to_hsl(scr->data_addr[pos]);*/
			//scr->data_addr[pos] = scr->data_addr[pos] + 0x161616;
//			hex_to_rgb_to_hsl(color);
//			scr->data_addr[pos] = color;
		}
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
		pixel_x = (((iter->x - scr->fractal->start_x) * (0.5 * scr->width * scr->fractal->zoom)) / scr->ratio_x) + (scr->width * 0.5) + scr->min_scr_x;
		pixel_y = (scr->height * 0.5) - (iter->y - scr->fractal->start_y) * ((0.5 * scr->fractal->zoom * scr->height) / scr->ratio_y) + scr->min_scr_y;
		i++;
	}
}

int		iter_buddha(t_iter *iter, int nbr_iter, t_screen *scr)
{
	int		i;
	
	iter->o_x = iter->x;
	iter->o_y = iter->y;
	i = 0;
	first_iter_buddha(iter, nbr_iter, &i);
	if (((iter->x * iter->x) + (iter->y * iter->y)) > 4 && i != scr->fractal->iteration && i > 30)
	{
		iter->x = iter->o_x;
		iter->y = iter->o_y;
		correct_path_iter(iter, nbr_iter, scr);
	}
	return (0);
}

void	*thread_buddha(void *arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
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
				iter_buddha(&iter, scr->fractal->iteration, scr);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

int		buddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	screens = NULL;
	nbr_screen = get_screen_by_fractal_name(env, 'b');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);	
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_buddha, (void *)screens[i]) == -1)
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
