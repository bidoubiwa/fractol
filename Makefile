# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvermand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/09 14:19:53 by cvermand          #+#    #+#              #
#    Updated: 2018/03/13 14:24:40 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FRACTOL		=	fractol

CC			=	gcc
CFLAGS		=   -Wall -Werror -Wextra -g3

_SRCS		=	fractol.c mandelbrot.c color.c events_listener.c julia.c \
				color_circle.c buddhabrot.c antibuddhabrot.c
_LIBFT		=	libft.a
_MLX		= 	libmlx.a

SRCS_DIR	=	.
LIB_DIR		=	libft
MLX_DIR		=	minilibx_macos
SRCS		=	$(addprefix	$(SRCS_DIR)/, $(_SRCS))
LIBFT		=	$(addprefix $(LIB_DIR)/, $(_LIBFT))
MLX			=	$(addprefix $(MLX_DIR)/, $(_MLX))

OBJS		=	$(SRCS:.c=.o)

all:	$(FRACTOL)

$(FRACTOL) : $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(FRACTOL) $(OBJS) -framework OpenGL -framework AppKit -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx -lm -D_REENTRANT -lpthread
	@echo "$(FRACTOL) : $(_GREEN)Done$(_END)"

$(LIBFT):
	@make -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR)

%.o : %.c
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

