# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/29 11:46:21 by jchardin          #+#    #+#              #
#    Updated: 2019/03/06 13:49:32 by naali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c

OBJ			=	$(SRC:.c=.o)

OBJ_DIR		=	./objs

OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ))

LIBRARIES	=	-Llibraries/sdl2/sdl2/lib -lSDL2 \
				-Llibraries/sdl2_image/sdl2_image/lib -lSDL2_image -framework OpenGL \
				-Llibraries/libft -lft  \
				-Llibraries/sdl2_ttf/sdl2_ttf/lib -lSDL2_ttf

INCLUDE_P	=	includes	\
				libraries/libft

IFLAGS		=	$(addprefix -I./, $(INCLUDE_P))

LDFLAGS		=	-L./libraries/libft

LFLAGS		=	-lft

LDLIBS		= $(LDFLAGS) $(LFLAGS)

vpath %.c ./srcs/:./srcs/getmap

vpath %.h ./includes/:./libraries/libft

$(OBJ_DIR)/%.o:	%.c
				@mkdir $(OBJ_DIR) 2> /dev/null || true
				@echo "Compiling $< ...\c"
				@$(CC) $(CFLAGS) -o $@ -c $^ $(IFLAGS)
				@echo " DONE"

all:			$(NAME)

lib:			libft
# sdl2 sdl2_image freetype sdl2_ttf

$(NAME):		$(OBJS) lib
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(IFLAGS) $(LDLIBS)

libft:
	@mkdir ./libraries 2> /dev/null || true
	@if [ -d ./libraries/libft ]; \
	then \
		if [ -e ./libraries/libft/libft.a ]; \
		then \
			echo "LIBFT EXIST";	\
		else \
			make -C ./libraries/libft; \
		fi; \
	else \
		cp -r ./source_lib/libft ./libraries/ \
		make -C ./libraries/libft; \
	fi

# 		if [ -e ./libraries/libft/libft.a ]; \
# 		then \
# 			echo "LIBFT nothing to be done..."; \
# 		fi

# sdl2:
# 	@mkdir ./libraries 2> /dev/null || true
# 	mkdir ./libraries/sdl2 2> /dev/null || true
# 	tar xzf ./source_lib/SDL2-2.0.9.tar.gz -C ./libraries/sdl2/ 2> /dev/null || true
# 	mv ./libraries/sdl2/SDL2-2.0.9 ./libraries/sdl2/sdl2 2> /dev/null || true
# 	cd  ./libraries/sdl2/sdl2 ; ./configure --prefix=$(shell pwd)/libraries/sdl2/sdl2
# 	make -C ./libraries/sdl2/sdl2
# 	make -C ./libraries/sdl2/sdl2 install


# sdl2_image:
# 	@mkdir ./libraries 2> /dev/null || true
# 	mkdir ./libraries/sdl2_image 2> /dev/null || true
# 	tar xzf ./source_lib/SDL2_image-2.0.4.tar.gz -C ./libraries/sdl2_image/
# 	mv ./libraries/sdl2_image/SDL2_image-2.0.4 ./libraries/sdl2_image/sdl2_image
# 	cd ./libraries/sdl2_image/sdl2_image/ ; ./configure --prefix=$(shell pwd)/libraries/sdl2_image/sdl2_image --with-sdl-prefix=$(shell pwd)/libraries/sdl2/sdl2
# 	make -C ./libraries/sdl2_image/sdl2_image
# 	make -C ./libraries/sdl2_image/sdl2_image install

# freetype:
# 	@mkdir ./libraries 2> /dev/null || true
# 	mkdir ./libraries/freetype 2> /dev/null || true
# 	tar xzf ./source_lib/freetype-2.4.11.tar.gz -C ./libraries/freetype/
# 	mv ./libraries/freetype/freetype-2.4.11 ./libraries/freetype/freetype
# 	cd ./libraries/freetype/freetype ; ./configure --prefix=$(shell pwd)/libraries/freetype/freetype
# 	make -C ./libraries/freetype/freetype/
# 	make -C ./libraries/freetype/freetype/ install

# sdl2_ttf:
# 	@mkdir ./libraries 2> /dev/null || true
# 	mkdir ./libraries/sdl2_ttf 2> /dev/null || true
# 	tar xzf ./source_lib/SDL2_ttf-2.0.15.tar.gz -C ./libraries/sdl2_ttf
# 	mv ./libraries/sdl2_ttf/SDL2_ttf-2.0.15/ ./libraries/sdl2_ttf/sdl2_ttf
# 	cd ./libraries/sdl2_ttf/sdl2_ttf ;  ./configure --prefix=$(shell pwd)/libraries/sdl2_ttf/sdl2_ttf --with-sdl-prefix=$(shell pwd)/libraries/sdl2/sdl2
# 	make -C libraries/sdl2_ttf/sdl2_ttf/
# 	make -C libraries/sdl2_ttf/sdl2_ttf/ install

clean:
		make fclean -C ./libraries/libft
		rm -rf $(OBJ_Dir)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all

norme:	clear
		@echo "La norme\n";
		norminette $(SRC_Dir)

exe:
	./$(NAME)

.PHONY: all clean fclean re

