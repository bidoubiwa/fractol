/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:30:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/15 13:35:53 by pfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*int		antibuddhabrot(t_env *env)
  {
  int		x;
  int		y;
  int		i;
  t_iter	iter;
  double	real_y;
  double	real_x;
  double	x_tmp;
  double	y_tmp;
  double	pixel_x;
  double	pixel_y;


  y = 0;
  real_y = 0;
  while (y < HEIGHT_SCREEN)
  {
  x = 0;
  real_y = (0 - (y - HEIGHT_SCREEN / 2.0) / (0.5 * env->zoom * HEIGHT_SCREEN)) + env->start_y;
  while (x < WIDTH_SCREEN)
  {
  real_x = 1.5 * (x - WIDTH_SCREEN / 2.0) / (0.5 * env->zoom * WIDTH_SCREEN) + env->start_x;
  iter.x = real_x;
  iter.y = real_y;
  if (real_x >= -2 && real_x <= 2 && real_y <= 2 && real_y >= -2)
  {
  i = 0;
  while (((iter.x * iter.x) + (iter.y * iter.y)) < 4 &&  i <= env->iteration)
  {
  if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN && i > 20) 
  {

  env->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] = env->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] + 0x040404;
  }	
  x_tmp = iter.x;
  y_tmp = iter.y;
  iter.x = (x_tmp * x_tmp) - (y_tmp * y_tmp) + real_x;
  iter.y = 2 * (x_tmp * y_tmp) + real_y;

  pixel_x = (((iter.x - env->start_x) * (0.5 * WIDTH_SCREEN * env->zoom)) / 1.5) + (WIDTH_SCREEN * 0.5);
  pixel_y = (HEIGHT_SCREEN * 0.5) - (iter.y - env->start_y) * (0.5 * env->zoom * HEIGHT_SCREEN);

  i++;
  }
  }
  x++;
  }
  y++;
  }	
  return (1);
  }*/

int		iter_anti(t_iter *iter, int nbr_iter, t_screen *scr, int pixel)
{
	double	x_tmp;
	int		i;
  	double	pixel_x;
  	double	pixel_y;

	iter->o_x = iter->x;
	iter->o_y = iter->y;
	pixel_x = 0;
	pixel_y = 0;
	i = 0;
	while ((iter->x * iter->x) + (iter->y * iter->y) <= 4 && i <= nbr_iter)
	{
		if ((int)round(pixel_y) >= 0 && (int)round(pixel_y) < HEIGHT_SCREEN && (int)round(pixel_x) >= 0 && (int)round(pixel_x) < WIDTH_SCREEN && i > 1)
		{
			scr->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] = scr->data_addr[((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x)] + 0x040404;
		}
		x_tmp = iter->x;
		iter->x = (x_tmp * x_tmp) - (iter->y * iter->y) + iter->o_x;
		iter->y = 2 * (x_tmp * iter->y) + iter->o_y; 
  		pixel_x = (((iter->x - scr->fractal->start_x) * (0.5 * scr->width * scr->fractal->zoom)) / scr->ratio) + (scr->width * 0.5) + scr->min_scr_x;
  		pixel_y = (scr->height * 0.5) - (iter->y - scr->fractal->start_y) * (0.5 * scr->fractal->zoom * scr->height) + scr->min_scr_y;
		i++;
	}
	return (0);
}

void	*thread_anti(void *arg)
{
	int			x;
	int			y;
	double		real_y;
	t_iter		iter;
	t_screen	*scr;

	scr = arg;
	printf("min_x : %d max_x : %d  min_y : %d max_y : %d\n  \
height : %d width : %d zoom : %f\n \
start_x : %f start_y : %f const_x : %f const_y : %f\n \
itera : %d min scr x : %d min scr y : %d\n \
----------------------------------------------------\n", 
			scr->min_x, scr->max_x, scr->min_y, scr->max_y, 
			scr->height, scr->width, scr->fractal->zoom,
			scr->fractal->start_x, scr->fractal->start_y, 
			scr->fractal->const_x, scr->fractal->const_y,
			scr->fractal->iteration, scr->min_scr_x, scr->min_scr_y);

	y = scr->min_y;
	while (y < scr->max_y)
	{
		x = scr->min_x;
		real_y  = 0 - (((y - scr->min_scr_y) - scr->height / 2.0) / 
			(0.5 * scr->fractal->zoom * scr->height)) + scr->fractal->start_y;
//		printf("real : %f\n", iter.y);
		while (x < scr->max_x)
		{
			iter.y = real_y;
//			printf("iter : %f\n", iter.y);
			iter.x = scr->ratio * (((x - scr->min_scr_x) - scr->width / 2.0) / (0.5 * scr->fractal->zoom * scr->width)) + scr->fractal->start_x;
			if (iter.x >= -2 && iter.x <= 2 && iter.y <= 2 && iter.y >= -2)
				iter_anti(&iter, scr->fractal->iteration, scr, ((y * WIDTH_SCREEN) + x));
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}


int		antibuddhabrot(t_env *env)
{
	pthread_t	thread[4];
	t_screen	**screens;
	int			i;
	int			nbr_screen;

	nbr_screen = get_screen_by_fractal_name(env, 'a');
	if (!(screens = init_args(screens, nbr_screen, env)))
		return (0);	
	i = 0;
	while (i < 4)
	{
		if	(pthread_create(&thread[i], NULL, &thread_anti, (void *)screens[i]) == -1)
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
