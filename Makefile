# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/29 11:46:21 by jchardin          #+#    #+#              #
#    Updated: 2019/03/07 15:48:58 by naali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c						\
				ft_pushback_str_to_tab.c	\
				mapfunc.c					\
				t_vertex.c

OBJ			=	$(SRC:.c=.o)

OBJ_DIR		=	./objs

# LIBRARIES	=

INCLUDE_P	=	includes				\
				libraries/libft			\
				libraries/SDL2-2.0.9/include

IFLAGS		=	$(addprefix -I./, $(INCLUDE_P))

OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ))

LDFLAGS		=	-L./libraries/libft					\
				-Llibraries/SDL2-2.0.9/lib			\
				-Llibraries/SDL2_image-2.0.4/lib	\
				-Llibraries/sdl2_ttf-2.0.15/lib

LFLAGS		=	-lft				\
				-lSDL2				\
				-lSDL2_image		\
				-framework OpenGL	\
				-lSDL2_ttf

LDLIBS		=	$(LDFLAGS) $(LFLAGS)

vpath %.c ./srcs/:./srcs/getmap:./srcs/matrice

vpath %.h ./includes/:./libraries/libft:./libraries/SDL2-2.0.9/include:./libraries/SDL2_image-2.0.4/include:SDL2_ttf-2.0.15/include

$(OBJ_DIR)/%.o:	%.c
				@mkdir $(OBJ_DIR) 2> /dev/null || true
				@echo "Compiling $< ...\c"
				$(CC) $(CFLAGS) -o $@ -c $^ $(IFLAGS)
				@echo " DONE"

all:			$(NAME)

lib:			libft sdl2 sdl2_image sdl2_ttf

$(NAME):		$(OBJS) lib
				@echo "Compiling Wolf3D... \c"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(IFLAGS) $(LDLIBS)
				@echo "DONE"

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
		&& make -C ./libraries/libft; \
	fi

sdl2:
	@echo "Lib SDL2... \c"
	@mkdir ./libraries 2> /dev/null || true
	@if [ -e ./libraries/SDL2-2.0.9/lib/libSDL2.la ]; then	\
		echo "Nothing to be done.";	\
	else	\
		rm -rf ./libraries/SDL2-2.0.9	\
		&& tar xzf ./source_lib/SDL2-2.0.9.tar.gz -C ./libraries/	\
		&& cd ./libraries/SDL2-2.0.9 ; ./configure	--prefix=$(shell pwd)/libraries/SDL2-2.0.9 \
		&& $(MAKE)	\
		&& $(MAKE) install;	\
		echo "DONE";	\
	fi;

sdl2_image:
	@echo "Lib SDL2_image... \c"
	@mkdir ./libraries 2> /dev/null || true
	@if [ -e ./libraries/SDL2_image-2.0.4/lib/libSDL2_image.la ]; then	\
		echo "Nothing to be done.";	\
	else	\
		rm -rf ./libraries/SDL2_image-2.0.4	\
		&& tar xzf ./source_lib/SDL2_image-2.0.4.tar.gz -C ./libraries/ \
		&& cd ./libraries/SDL2_image-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries/SDL2_image-2.0.4 --with-sdl-prefix=$(shell pwd)/libraries/SDL2-2.0.9 \
		&& $(MAKE) \
		&& $(MAKE) install; \
	fi;

# freetype:
# 	@echo "Lib freetype... \c"
# 	@mkdir ./libraries 2> /dev/null || true
# 	@if [ -e ./libraries/freetype-2.4.11 ]; then	\
# 		echo "Nothing to be done.";	\
# 	else	\
# 		rm -rf ./libraries/freetype-2.4.11	\
# 		tar xzf ./source_lib/freetype-2.4.11.tar.gz -C ./libraries/ \
# 		&& cd ./libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries/freetype-2.4.11 \
# 		&& $(MAKE) \
# 		&& $(MAKE) install; \
# 	fi;

sdl2_ttf:
	@echo "Lib sdl2_ttf... \c"
	@mkdir ./libraries 2> /dev/null || true
	@if [ -e ./libraries/SDL2_ttf-2.0.15 ]; then	\
		echo "Nothing to be done.";	\
	else	\
		rm -rf ./libraries/SDL2_ttf-2.0.15	\
		&& tar xzf ./source_lib/SDL2_ttf-2.0.15.tar.gz -C ./libraries/ \
		&& cd ./libraries/SDL2_ttf-2.0.15 ;  ./configure --prefix=$(shell pwd)/libraries/SDL2_ttf-2.0.15 --with-sdl-prefix=$(shell pwd)/libraries/SDL2-2.0.9 \
		&& $(MAKE) \
		&& $(MAKE) install; \
	fi;

clean:
		make clean -C ./libraries/libft
		make clean -C ./libraries/SDL2-2.0.9
		make clean -C ./libraries/SDL2_image-2.0.4
		make clean -C ./libraries/freetype-2.4.11
		make clean -C ./libraries/SDL2_ttf-2.0.15
		rm -rf $(OBJ_Dir)

fclean:	clean
		make fclean -C ./libraries/libft
		rm -rf $(NAME)

fclnsdl:
		rm -rf ./libraries/SDL2-2.0.9/lib/libSDL2.la
		rm -rf ./libraries/SDL2_image-2.0.4/lib/libSDL2_image.la
		rm -rf ./libraries/freetype-2.4.11
		rm -rf ./libraries/SDL2_ttf-2.0.15

re:		fclean all

resdl:	fclean fclnsdl all

norme:	clear
		@echo "La norme\n";
		norminette $(SRC_Dir)

exe:
	./$(NAME)

.PHONY: all clean fclean fclnsdl re resdl

