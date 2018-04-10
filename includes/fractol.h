/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:11:27 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/10 17:22:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <fcntl.h>

# include <pthread.h>
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include "mlx_keys_macos.h"
# include "X.h"
# define WIDTH_SCREEN 1500
# define HEIGHT_SCREEN 700

# define MOUSE_ZOOM_IN 5
# define MOUSE_ZOOM_OUT 4
# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78
# define KEY_ESC 53
# define KEY_MOUSE_STOP 49
# define KEY_PSYCHEDELIC 19
# define KEY_AUTO_ZOOM 18
# define KEY_DEEP_ADD 116
# define KEY_DEEP_SUB 121
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_RESET 15
# define WIDTH 600
# define HEIGHT 400
# define MOTION_NOTIFY 6
# define KEY_PRESS 2
# define PTR_MOTION_MASK (1L<<6)
# define KEY_PRESS_MASK	(1L<<0)

typedef struct		s_iter
{
	double		o_x;
	double		o_y;
	double		x;
	double		y;
}					t_iter;

struct		s_screen;

typedef struct			s_env
{
	char				*param;
	void				*mlx;
	void				*win;
	void				*img;
	unsigned int		*data_addr;
	char				*title;
	int					bits_per_pixel;
	int					bytes_per_line;
	int					endian;
	int					win_width;
	int					win_height;
	int					iteration;
	int					color;
	int					color_size;
	char				julia_loop;
	char				show_menu;
	char				zoom_enable;
	char				show_info;
	unsigned int		**palettes;
	int					palette;
	struct s_screen		**screen;
}						t_env;

typedef struct			s_fractal
{
	double			zoom;
	char			name;
	int				(*f)(t_env*);
	int				iteration;
	double			start_x;
	double			start_y;
	double			const_x;
	double			const_y;
	unsigned int	hex;
}						t_fractal;

typedef	struct			s_screen
{
	double				ratio_x;
	double				ratio_y;
	int					order;
	t_fractal			*fractal;
	int					min_scr_x;
	int					min_scr_y;
	int					max_scr_x;
	int					max_scr_y;
	int					min_x;
	int					max_x;
	int					min_y;
	int					max_y;
	int					width;
	int					height;
	int					palette;
	unsigned int		**palettes;
	unsigned int		*data_addr;
}						t_screen;


int					mandelbrot(t_env *env);
int					buddhabrot(t_env *env);
int					antibuddhabrot(t_env *env);
int					julia(t_env *env);
int					init_env(t_env *env, char *av);
void				init_mandelbrot(t_fractal *fractal);
void				init_buddhabrot(t_fractal *fractal);
void				init_antibuddhabrot(t_fractal *fractal);
void				init_julia(t_fractal *fractal);
t_screen			**init_screens(t_screen **screen, char menu_on, char *param);
void				free_fractal(t_screen **screens);
void				free_screens(t_screen **screens);
void				events_listener(t_env *env);
unsigned int		hsv_calculator(int hue, double saturation);
unsigned int		hsl_calculator(int hue, double saturation, double light);
unsigned int		hex_to_rgb_to_hsl(unsigned int hex, int iter);
unsigned int		merge_two_colors(unsigned int color1, unsigned int color2);
unsigned int		palette(int	iter);
void				draw_circle(t_env *env);
void				get_screen_ratio(double width, double height, t_screen *screen);
int					get_x_min(int order);
int					get_x_max(int order, char menu_on);
int					get_y_min(int order);
int					get_y_max(int order);
t_fractal			*get_fractal(int order);
int					get_screen_by_fractal_name(t_env *env, char c);
t_screen			*get_screen_ptr_by_fractal_name(t_env *env, char c);
t_screen			**init_args(t_screen **screens, int nbr_screen, t_env *env);
void				init_arg_limits(int min_x, int min_y, t_screen *screen);
int					key_hook(int keycode, t_env *env);
int					loop_hook(int x, int y, t_env *env);
int					julia_loop(int x, int y, t_env *env);
int					mouse_hook(int button, int x, int y, t_env *env);
int					zoom(int button, int x, int y, t_env *env);
void				clear_image(t_env *env);
void				color_menu(t_env *env);
void				display_fractals(t_env *env);
void				display_screen_one(t_env *env);
void				clear_and_redraw(t_env *env);
void				clear_zone(int zone, t_env *env);
void				display_info_menu(t_env *env);
void				toggle_info_menu(t_env *env);
int					set_palettes(t_env *env);
void				set_menu(t_env *env);
int					move_mouse(int button, int x, int y, t_env *env);
int					move_keys(int button, t_env *env);
#endif
