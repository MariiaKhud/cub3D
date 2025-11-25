# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tiyang <tiyang@student.42.fr>                +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/30 10:51:21 by tiyang        #+#    #+#                  #
#    Updated: 2025/11/25 15:56:25 by tiyang        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX_PATH = minilibx/
MLX_LIB = $(MLX_PATH)libmlx.a

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

INCLUDES = -I. -I$(LIBFT_PATH) -I$(MLX_PATH)

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
MLXFLAGS = -lm -lXext -lX11

SRCS = src/main.c \
       src/lifecycle/game_init.c \
	   src/lifecycle/game_close.c \
	   src/lifecycle/utils.c \
	   src/parsing/map_parser.c \
	   src/parsing/map_validation.c \
	   src/parsing/flood_fill.c \
	   src/parsing/utils.c \
	   src/engine/raycast.c

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
# NAME                = cub3D
# CC                  = cc
# CFLAGS              = -Wall -Wextra -Werror

# LIBFT_DIR           = libft
# MINILIBX_DIR        = minilibx
# OBJDIR              = objs
# SRC_DIR             = src

# MLX_LIB             = $(MINILIBX_DIR)/libmlx.a
# LIBFT               = $(LIBFT_DIR)/libft.a
# INCLUDES            = -I$(LIBFT_DIR) -I$(SRC_DIR) -I$(MINILIBX_DIR) -I.

# SRCS                = $(SRC_DIR)/main.c \
#                       $(SRC_DIR)/lifecycle/game_init.c \
#                       $(SRC_DIR)/lifecycle/game_close.c \
# 					  $(SRC_DIR)/lifecycle/render_map.c \
#                       $(SRC_DIR)/lifecycle/utils.c \
#                       $(SRC_DIR)/parsing/parse_info.c \
#                       $(SRC_DIR)/parsing/parse_map.c \
#                       $(SRC_DIR)/parsing/utils.c \
#                       $(SRC_DIR)/parsing/validate_map.c \
# 					  $(SRC_DIR)/engine/raycast.c

# OBJS                = $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# RM                  = rm -f
# MKDIR               = mkdir -p
# MAKE_LIBFT          = make -C $(LIBFT_DIR)

# all: $(NAME)

# $(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) \
# 	-L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

# $(LIBFT):
# 	$(MAKE_LIBFT)

# $(MLX_LIB):
# 	$(MAKE) -C $(MINILIBX_DIR)

# $(OBJDIR)/%.o: $(SRC_DIR)/%.c
# 	@$(MKDIR) $(dir $@)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	$(MAKE_LIBFT) clean
# 	$(RM) -r $(OBJDIR)
# 	@if [ -d "$(MINILIBX_DIR)" ]; then \
# 		$(MAKE) -C $(MINILIBX_DIR) clean; \
# 	fi

# fclean: clean
# 	$(MAKE_LIBFT) fclean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re