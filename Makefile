# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesquier <sesquier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/21 15:26:47 by sesquier          #+#    #+#              #
#    Updated: 2026/05/29 16:19:04 by sesquier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFT_DIR = LIBFT
MINILIBX_DIR = minilibx-linux

S_SRC = main.c init.c parsing.c parsing_utils.c dda_loop.c init_ray.c \
		render.c moves.c moves2.c errors.c dda_loop2.c dda_loop3.c \
		init2.c init3.c init4.c utils.c parsing_utils2.c parsing_utils3.c \
		parsing_utils4.c parsing2.c parsing_utils5.c
D_SRC = srcs/

S_OBJ = $(S_SRC:.c=.o)
D_OBJ = .build/
OBJ = $(addprefix $(D_OBJ), $(S_OBJ))

CC = cc
CFLAGS = -Wall -Wextra -Werror -Wno-cast-function-type \
		-O3 -march=native -funroll-loops -flto

#

LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX = $(MINILIBX_DIR)/libmlx_Linux.a

D_INC = includes/
INC_FLAGS = -I$(D_INC) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)

MLX_FLAGS = -L$(MINILIBX_DIR) -lmlx_Linux -lXext -lX11 -lm

all: $(LIBFT) $(MINILIBX) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $@

$(D_OBJ)%.o: $(D_SRC)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(D_OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re+
