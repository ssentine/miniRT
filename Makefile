# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssentine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 11:46:40 by ssentine          #+#    #+#              #
#    Updated: 2021/01/21 11:46:42 by ssentine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS_LIST = 	libft1.c \
		libft2.c \
		libft3.c \
		libft4.c \
		main.c \
		parser_1.c \
		parser_2.c \
		get_next_line.c \
		validator_1.c \
		validator_2.c \
		start_minirt.c \
		free_funcs.c \
		vectors_1.c \
		vectors_2.c \
		vectors_3.c \
		key_hooks.c \
		save_image.c \
		matrices.c \
		render.c \
		utils.c \
		sphere.c \
		plane.c \
		square.c \
		triangle.c \
		cylinder.c

SRCS = $(addprefix srcs/, ${SRCS_LIST})
FLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
HEADER = includes
MLX = minilibx
LIB_MLX = libmlx.dylib -framework OpenGL -framework Appkit

.PHONY: all clean fclean re

all: $(NAME)
	
$(NAME): 	$(OBJS)
			@make -s -C $(MLX)
			@mv $(MLX)/libmlx.dylib .
			gcc $(FLAGS) -I $(HEADER) $(LIB_MLX) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)
	@make clean -C $(MLX)
	

fclean: clean
	rm -f $(NAME)
	rm -f libmlx.dylib
	rm -f image.bmp

re: fclean all
