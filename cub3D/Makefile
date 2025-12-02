# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 10:51:21 by tiyang            #+#    #+#              #
#    Updated: 2025/12/02 10:56:49 by makhudon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME                = cub3D
CC                  = cc
CFLAGS              = -Wall -Wextra -Werror

LIBFT_DIR           = libft
MINILIBX_DIR        = minilibx
OBJDIR              = objs
SRC_DIR             = src

MLX_LIB             = $(MINILIBX_DIR)/libmlx.a
LIBFT               = $(LIBFT_DIR)/libft.a
INCLUDES            = -I$(LIBFT_DIR) -I$(SRC_DIR) -I$(MINILIBX_DIR) -I.

SRCS                = $(SRC_DIR)/main.c \
					  $(SRC_DIR)/lifecycle/game_init.c \
					  $(SRC_DIR)/lifecycle/game_close.c \
					  $(SRC_DIR)/lifecycle/player_init.c \
					  $(SRC_DIR)/lifecycle/player_position.c \
					  $(SRC_DIR)/parsing/parse_info.c \
					  $(SRC_DIR)/parsing/parse_info_rgb.c \
					  $(SRC_DIR)/parsing/parse_info_utils.c \
					  $(SRC_DIR)/parsing/free_utils.c \
					  $(SRC_DIR)/parsing/parse_map.c \
					  $(SRC_DIR)/parsing/parse_map_utils.c \
					  $(SRC_DIR)/parsing/utils.c \
					  $(SRC_DIR)/parsing/validate_map.c \
					  $(SRC_DIR)/input/input.c \
					  $(SRC_DIR)/input/input_helper.c \
					  $(SRC_DIR)/engine/raycast.c \
					  $(SRC_DIR)/engine/render_background.c \
					  $(SRC_DIR)/engine/dda.c \
					  $(SRC_DIR)/engine/render_utils.c \
					  $(SRC_DIR)/bonus/minimap.c \
					  $(SRC_DIR)/bonus/minimap_line.c \
					  $(SRC_DIR)/bonus/minimap_utils.c \
					  $(SRC_DIR)/bonus/mouse.c \
					  $(SRC_DIR)/bonus/collision.c \
					  $(SRC_DIR)/bonus/animation.c

OBJS                = $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

RM                  = rm -f
MKDIR               = mkdir -p
MAKE_LIBFT          = make -C $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) \
	-L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

$(MLX_LIB):
	$(MAKE) -C $(MINILIBX_DIR)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE_LIBFT) clean
	$(RM) -r $(OBJDIR)
	@if [ -d "$(MINILIBX_DIR)" ]; then \
		$(MAKE) -C $(MINILIBX_DIR) clean; \
	fi

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
