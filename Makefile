# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 23:12:18 by otaraki           #+#    #+#              #
#    Updated: 2024/02/05 02:15:01 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := cub3D

ARCH := libft/libft.a

MLX := MLX42/build/libmlx42.a

MLX_FLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit

CC := cc
 
CFLAGS := -g -Wall -Wextra -Werror -Ofast
# -fsanitize=address

I = -I /Users/${USER}/.brew/Cellar/glfw/3.3.9/include/GLFW
L = -L /Users/${USER}/.brew/Cellar/glfw/3.3.9/lib

HEADERS := incs/cub3d.h incs/defines.h

FILES := srcs/cub3d \
		 srcs/texture_utils \
		 srcs/parse1_utils \
		 srcs/parse2_utils \
		 srcs/parse3_utils \
		 srcs/parse4_utils \
		 srcs/raycasting \
		 srcs/keyhandle \
		 srcs/init \
		 srcs/raycasting_utils \
		 srcs/keyhandle_utils \
		 srcs/rendering_utils \

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library :
	make -C libft

$(EXE) : $(OBJ) | library 
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(ARCH) $(MLX) $(L) $(I) -o $(EXE) 

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ $(I)

clean :
	make clean -C libft
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft
	$(RM) $(EXE)

re : fclean all

run:
	make all;
	./cub3D maps/map.cub

git :
	git add .
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
