# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgoncalv <cgoncalv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 15:14:55 by cgoncalv          #+#    #+#              #
#    Updated: 2020/02/17 17:07:22 by cgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	#-Wall -Werror -Wextra

MFLAGS		=	-I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

SRC			=	ft_cub3d.c

OBJ 		=	$(SRC:.c=.o)

NAME		=	ft_cub3D

LIB			=	ar rcs

all:		$(NAME)

$(NAME):
			@$(CC) $(CFLAGS) $(MFLAGS) ${SRC}
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
			@$(CC) $(CFLAGS) $(MFLAGS) ft_cub3d.c
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out

pong:		all
			@$(CC) $(CFLAGS) $(MFLAGS) pong.c
			@echo "\033[32m[✓]\033[0m		[$(NAME) and main.c compiled]"
			@echo "\033[32m[✓]\033[0m		[a.out executed]\n"
			@./a.out