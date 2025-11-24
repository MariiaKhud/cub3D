# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tiyang <tiyang@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/30 10:51:21 by tiyang        #+#    #+#                  #
#    Updated: 2025/11/24 10:18:35 by tiyang        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLX_PATH = minilibx/
MLX_LIB = $(MLX_PATH)libmlx.a

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

INCLUDES = -I. -I$(LIBFT_PATH) -I$(MLX_PATH)

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
MLXFLAGS = -lm -lXext -lX11

SRCS = src/main.c \
       src/map/map_parser.c \
       src/map/map_validation.c \
       src/map/flood_fill.c \
	   src/map/utils.c \
       src/game/game_init.c \
       src/game/render.c \
       src/game/input.c \
       src/game/game_close.c

OBJS = $(SRCS:.c=.o)

all: subsystems $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

subsystems:
	@make -C $(MLX_PATH) all
	@make -C $(LIBFT_PATH) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

clean:
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
