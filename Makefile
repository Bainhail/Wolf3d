#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naali <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/08 14:49:52 by naali             #+#    #+#              #
#    Updated: 2019/05/09 15:06:33 by naali            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#SDL
SDL_MAIN_DOWNLOAD = https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
SDL_IMAGE_DOWNLOAD = https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz

NAME		=	wolf3d
CC			=	gcc

SRC			=	main.c						\
				ft_pushback_str_to_tab.c	\
				mapfunc.c					\
				drawsquare.c				\
				playerposition.c			\
				calc_player_form.c			\
				wall_detect_opti.c			\
				segmnt_creation.c			\
				convert.c					\
				matrice_init.c				\
				matrice_rot.c				\
				matrice_scal.c				\
				matrice_trans.c				\
				multiply.c					\
				mult_matrice.c				\
				t_vertex.c					\
				file_event_loop.c			\
				file_3d_map.c 				\
				file_ft_quit.c 				\
				file_ft_get_the_map.c		\
				calcul_distance.c			\
				wall_checking_x.c			\
				wall_checking_y.c			\
				colision.c					\
				orientation.c				\
				draw_wall.c					\
				secteur_func.c				\
				file_bmp_texture.c

OBJ			=	$(SRC:.c=.o)
CFLAG		=	-Wall -Wextra -Werror
INCLUDE		=	-I ./includes/
INCLUDE		+=	-I ./sdl_image/SDL2_image-2.0.3/include/
INCLUDE		+=	-I ./sdl_main/SDL2-2.0.8/include/
INCLUDE		+=	-I ./libft/
DSRC		=	./srcs
DOBJ		=	./objs
OBJS		=	$(addprefix $(DOBJ)/, $(OBJ))
SRCS		=	$(addprefix $(DSRC), $(SRC))
LFLAG		=	-L sdl_main/SDL2-2.0.8/lib  -lSDL2
LFLAG		+=	-L ./sdl_image/SDL2_image-2.0.3/lib -lSDL2_image
LFLAG		+=	-L ./libft/ -lft -lm
.PHONY: all clean fclean re lib sdl_main sdl_image libft debug

all:$(NAME)

debug:CC += -g
debug:clean
debug:all

vpath %.c ./srcs/:./srcs/getmap:./srcs/matrice:./srcs/draw:./srcs/player:./srcs/event:./srcs/files

$(DOBJ)/%.o:%.c
	@mkdir $(DOBJ) 2> /dev/null || true
	$(CC) -c $< -o $@ $(INCLUDE) $(CFLAG)


$(NAME):lib $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAG) $(LFLAG)

clean:
	rm -rf $(DOBJ)
	make clean -C ./libft

fclean:clean
	rm -rf $(NAME)
	rm -rf ./sdl_main/
	rm -rf ./sdl_image/

re:fclean $(NAME)

lib:libft sdl_main sdl_image

libft:
	@echo "Libft ==> Compilation"
	@make -C ./libft
	@echo "Libft ==> Done"

sdl_main:
	@if [ -d "./sdl_main/" ]; then \
		echo "SDL (main) ==> Nothing to be done"; \
		else \
		mkdir sdl_main && \
		echo "SDL (main) ==> Downloading SDL" && \
		cd ./sdl_main && \
		curl -s $(SDL_MAIN_DOWNLOAD) -O && \
		echo "SDL (main) ==> Compilation SDL main" && \
		tar xzf SDL2-2.0.8.tar.gz && \
		cd SDL2-2.0.8 && \
		./configure --prefix=$(shell pwd)/sdl_main/SDL2-2.0.8 > /dev/null 2>&1 && \
		$(MAKE) > /dev/null 2>&1 &&  \
		$(MAKE) install > /dev/null 2>&1 && \
		echo "SDL (main) ==> DONE"; \
		fi

sdl_image:
	@if [ -d "./sdl_image/" ]; then \
		echo "SDL (image) ==> Nothing to be done"; \
		else \
		mkdir sdl_image && \
		echo "SDL (image) ==> Downloading SDL image" && \
		cd ./sdl_image && \
		curl -s $(SDL_IMAGE_DOWNLOAD) -O && \
		echo "SDL (image) ==> Compilation SDL image" && \
		tar xzf SDL2_image-2.0.3.tar.gz && \
		cd SDL2_image-2.0.3 && \
		./configure --prefix=$(shell pwd)/sdl_image/SDL2_image-2.0.3 --with-sdl-prefix=$(shell pwd)/sdl_main/SDL2-2.0.8  > /dev/null 2>&1 && \
		$(MAKE)  > /dev/null 2>&1  &&  \
		$(MAKE) install > /dev/null 2>&1  && \
		echo "SDL (image) ==> DONE"; \
		fi

clear:
	clear

line:clear
	find ./srcs -name '*.c' | xargs wc -l

tag:
	ctags -R .
