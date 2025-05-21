# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lemarian <lemarian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 14:41:21 by bvictoir          #+#    #+#              #
#    Updated: 2025/05/21 14:58:45 by lemarian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+= -s

NAME		= cub3D

SRC_PATH	= srcs/
OBJ_PATH	= obj/
INC_PATH	= incs/
LIBFT_PATH	= libft/
MLX			= mlx/


SRC			=	raycast.c		\
				ft_free.c		\
				init.c			\
				render.c		\
				mlx_init.c		\
				movement.c		\
				parsing/parse_file.c			\
				parsing/check_textures.c		\
				parsing/check_map.c				\
				main.c \
				test.c \
				new_render.c
SRCS		= ${addprefix $(SRC_PATH), $(SRC)}

OBJ			= $(SRC:.c=.o)
OBJS		= ${addprefix $(OBJ_PATH), $(OBJ)}

LIBFTLIB	= libft.a
MINILIBX	= $(MLX)libmlx.a
LIB			= $(LIBFTLIB) $(MINILIBX)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

INCLUDES	= -I $(INC_PATH) -I $(MLX)
MLXFLAG		= -L $(MLX) -Imlx_linux -lXext -lX11 -lm -lz
# MLXFLAG	= -L $(MLX) -lmlx -lXext -lX11 -lm -lz

RM			= rm -rfd

RED			:= "\033[0;31m\033[1m"
GREEN		:= "\033[0;32m\033[1m"
BLUE		:= "\033[0;34m\033[1m"
YELLOW		:= "\033[1;33m\033[1m"
PURPLE		:= "\033[0;35m\033[1m"
CYAN		:= "\033[0;36m\033[1m"
WHITE		:= "\033[0;37m\033[1m"
NO_STYLE	:= "\033[0m"


all:		$(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@


$(NAME): $(OBJS)
		make -C $(MLX)
		make -C $(LIBFT_PATH)
		mv $(LIBFT_PATH)$(LIBFTLIB) .
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES) $(LIB) $(MLXFLAG)
		echo $(GREEN)$(NAME) compiled!$(NO_STYLE)

clean:	
		$(RM) $(OBJ_PATH)
		make clean -C $(LIBFT_PATH)
		echo $(YELLOW)object clean! $(NO_STYLE)

fclean: 	
		$(RM) $(OBJ_PATH) $(NAME) $(LIBFTLIB)
		make fclean -C $(LIBFT_PATH)
		echo $(RED)$(NAME) deleted!$(NO_STYLE)

re: fclean all
		echo $(PURPLE)$(NAME) reloaded!$(NO_STYLE)

.PHONY:  all clean fclean re