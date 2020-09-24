# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badrien <badrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 15:14:55 by cgoncalv          #+#    #+#              #
#    Updated: 2020/09/24 11:35:36 by badrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

MFLAGS		=	-I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit #-fsanitize=address

SRC			=	src/ft_capture.c src/ft_cub3d.c src/ft_draw_floor_sky.c src/ft_draw_wall.c src/ft_exit.c \
				src/ft_init.c src/ft_map.c src/ft_movements.c src/ft_movements_rot.c src/ft_parsing.c \
				src/ft_parsing_params.c src/ft_raycasting.c src/ft_sprite.c

OBJ 		=	$(SRC:.c=.o)

NAME		=	ft_cub3D

LIB			=	ar rcs

all:		$(NAME)

$(NAME):	
			@make -C ./libft
			@cp ./libft/libft.a libft.a
			@$(CC) $(CFLAGS) $(MFLAGS) ${SRC} libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

%.o: %.c
			$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f *.o
			@echo "\033[32m\n[✓]\033[0m		[*.o deleted]"

fclean:		clean
			@rm -f $(NAME)
			@rm -f libft/libft.a
			@rm -f libft/*.o
			@rm -f a.out
			@echo "\033[32m[✓]\033[0m		[libft.a deleted]"
			@echo "\033[32m[✓]\033[0m		[libftprintf.a deleted]"

re:			fclean all

exec:		all
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out map.cub

screenshot: all
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out map.cub --save

pong:		all
			@$(CC) $(CFLAGS) $(MFLAGS) pong.c
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out