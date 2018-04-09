# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvermand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/09 14:19:53 by cvermand          #+#    #+#              #
#    Updated: 2018/04/09 19:12:14 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FRACTOL		=	fractol

CC			=	gcc
CFLAGS		=   -Wall -Wextra -Werror -g3

_SRCS		=	main.c mandelbrot.c color.c events_listener.c julia.c \
				color_menu.c buddhabrot.c antibuddhabrot.c \
				struct_fractal.c screens_size.c thread_handling.c \
				init_fractals.c init_screens.c keys.c mouse.c \
				zoom.c clear.c info_menu.c palettes.c init_env.c
_LIBFT		=	libft.a
_MLX		= 	libmlx.a
_HDR		=	fractol.h
SRCS_DIR	=	.
LIB_DIR		=	libft
MLX_DIR		=	minilibx_macos
HDR_DIR		=	includes
SRCS		=	$(addprefix	$(SRCS_DIR)/, $(_SRCS))
LIBFT		=	$(addprefix $(LIB_DIR)/, $(_LIBFT))
MLX			=	$(addprefix $(MLX_DIR)/, $(_MLX))
HDR			=	$(addprefix $(HDR_DIR)/, $(_HDR))

OBJS		=	$(SRCS:.c=.o)

all:	$(FRACTOL)

$(FRACTOL) : $(LIBFT) $(MLX) $(OBJS) $(HDR)
	@$(CC) $(CFLAGS) -o $(FRACTOL) $(OBJS) -framework OpenGL -framework AppKit -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx -lm -D_REENTRANT -lpthread
	@echo "$(FRACTOL) : $(_GREEN)Done$(_END)"

$(LIBFT):
	@make -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR)

%.o : %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@ -I includes/

clean:
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(MLX_DIR)
	@/bin/rm -f $(OBJS)
	@echo "FRACTOL clean : $(_GREEN)Done$(_END)"

fclean: clean
	@/bin/rm -f $(FRACTOL)
	@echo "FRACTOL fclean : $(_GREEN)Done$(_END)"

re:
	@make fclean
	@make

.PHONY: all clean fclean re

