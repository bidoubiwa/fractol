/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:11:27 by cvermand          #+#    #+#             */
/*   Updated: 2018/03/09 22:30:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# define WIDTH_SCREEN 2560
# define HEIGHT_SCREEN 1440

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*data_addr;
	char			*title;
	int				bits_per_pixel;
	int				bytes_per_line;
	int				endian;
	int				win_width;
	int				win_height;
	int				iter;
	double			zoom;
}					t_env;

typedef struct		s_lim
{
	int				min_w;
	int				max_w;
	int				min_h;
	int				max_h;
}					t_lim;

typedef struct		s_iter
{
	double		o_x;
	double		o_y;
	double		x;
	double		y;
}					t_iter;

int					mandelbrot(t_env *env, double start_x, double start_y);
void				events_listener(t_env *env);
unsigned int		hsv_calculator(int iter);


double	y_plane_coord(int y, t_lim *lim);
double	x_plane_coord(int x, t_lim *lim);
void	init_plane(t_env *env, t_lim *lim);
#endif
