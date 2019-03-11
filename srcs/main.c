/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/11 14:37:56 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct			s_my_rectangle
{
	int					x;
	int					y;
	int					size;
}						t_my_rectangle;


typedef struct			s_my_event
{
	SDL_bool			key[SDL_NUM_SCANCODES];
	SDL_bool			quit;
}						t_my_event;


typedef struct			s_my_player_pos
{
	int					x;
	int					y;
	int					angle;
}						t_my_player_pos;

typedef enum			e_my_move
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	TRIGO,
	ANTITRIGO,
}						t_my_move;

void	ft_clear_window_in_blue(int height, int width, SDL_Renderer *renderer_name);
void	ft_read_the_map(int height, int width, int **map);
int		ft_my_atoi(char c);
int		**ft_init_map(int height, int width);
void	ft_draw_map(int **map, int height, int width, SDL_Renderer *renderer_name);
void	ft_draw_rectangle(t_my_rectangle s_rectangle, SDL_Renderer *renderer_name);
void	ft_update_event_editor(t_my_event *s_event);
void	ft_init_event_editor(t_my_event *s_event);
void			ft_move_player(int move, t_my_player_pos *s_player_pos, SDL_Renderer *name_renderer, t_my_rectangle s_triangle, int height, int width, int **map);
void		ft_draw_triangle(SDL_Renderer *name_renderer, t_my_rectangle s_triangle, t_my_player_pos *s_player_pos);


int			main(void)
{
	SDL_Window		*window_name;
	SDL_Renderer	*renderer_name;
	int				height;
	int				width;
	int				**map;
	t_my_rectangle	s_rectangle;
	t_my_rectangle	s_triangle;
	t_my_event		s_event;
	t_my_player_pos	s_player_pos;

	height = 480;
	width = 640;

	s_player_pos.x = 20;
	s_player_pos.y = 20;
	s_player_pos.angle = 0;
	s_rectangle.x = 0;
	s_rectangle.y = 0;
	s_rectangle.size = 0;
	s_triangle.x = 10;
	s_triangle.y = 10;
	s_triangle.size = 10;


	SDL_Init(SDL_INIT_EVERYTHING);
	window_name = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer_name = SDL_CreateRenderer(window_name, 0, SDL_RENDERER_SOFTWARE);
	ft_clear_window_in_blue(height, width, renderer_name);
	map = ft_init_map(height, width);
	ft_read_the_map(height, width, map);
	ft_draw_map(map, height, width, renderer_name);
	ft_draw_triangle(renderer_name, s_triangle, &s_player_pos);
	SDL_RenderPresent(renderer_name );

	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		ft_init_event_editor(&s_event);
		ft_update_event_editor(&s_event);

		s_event.key[SDL_SCANCODE_ESCAPE] ? s_event.quit = SDL_TRUE : 0 ;
		s_event.key[SDL_SCANCODE_W] ? ft_move_player(UP, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		s_event.key[SDL_SCANCODE_A] ? ft_move_player(LEFT, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		s_event.key[SDL_SCANCODE_D] ? ft_move_player(RIGHT, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		s_event.key[SDL_SCANCODE_S] ? ft_move_player(DOWN, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		s_event.key[SDL_SCANCODE_LEFT] ? ft_move_player(TRIGO, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		s_event.key[SDL_SCANCODE_RIGHT] ? ft_move_player(ANTITRIGO, &s_player_pos, renderer_name, s_triangle, height, width, map) : 0 ;
		SDL_Delay(20);
	}

	SDL_DestroyWindow(window_name);
	SDL_Quit();
	return (0);
}


void			ft_move_player(int move, t_my_player_pos *s_player_pos, SDL_Renderer *name_renderer, t_my_rectangle s_triangle, int height, int width, int **map)
{
	int		x;
	int		y;
	int		angle;

	x = 0;
	y = 0;
	angle = 0;

	move == UP ? printf("je monte\n") : 0 ;
	move == DOWN ? printf("je descend\n") : 0 ;
	move == RIGHT ? printf("je vais a droite\n") : 0 ;
	move == LEFT ? printf("je vais a gauche\n") : 0 ;
	move == TRIGO ? printf("tourne sens trigo\n") : 0 ;
	move == ANTITRIGO ? printf("tourne sens antitrigo\n") : 0 ;

	move == UP ?		y = -5 : 0 ;
	move == DOWN ?		y =  5 : 0 ;
	move == RIGHT ? 	x =  5 : 0 ;
	move == LEFT ?		x = -5 : 0 ;
	move == TRIGO ? 	angle = 5 : 0 ;
	move == ANTITRIGO ?	angle = -5 : 0 ;

	//s_player_pos->x += x;
	//s_player_pos->y += y;
	s_player_pos->angle += angle;

	s_player_pos->x += (x * cos(s_player_pos->angle * M_PI / 180)) + (y * -sin(s_player_pos->angle * M_PI / 180));
	s_player_pos->y += (x * sin(s_player_pos->angle * M_PI / 180)) + (y *  cos(s_player_pos->angle * M_PI / 180));


	ft_clear_window_in_blue(height, width, name_renderer);
	ft_draw_map(map, height, width, name_renderer);
	ft_draw_triangle(name_renderer, s_triangle, s_player_pos);
	SDL_RenderPresent(name_renderer);
	//incrementation player pos
	//incrementation angle

	//clear l'ecran
	//afficher la map
	//afficher la fleche
}

void		ft_draw_triangle(SDL_Renderer *name_renderer, t_my_rectangle s_triangle, t_my_player_pos *s_player_pos)
{
	int		x;
	int		y;
	int		i;
	int		j;

	y = 0;
	i = 0;
	while (i < s_triangle.size)
	{
		x = i;
		j = 0;

		while (j < (2 * i))
		{
			float x_tmp = (x * cos(s_player_pos->angle * M_PI / 180)) + (y * -sin(s_player_pos->angle * M_PI / 180));
			float y_tmp = (x * sin(s_player_pos->angle * M_PI / 180)) + (y *  cos(s_player_pos->angle * M_PI / 180));
			SDL_RenderDrawPoint(name_renderer, (int)(x_tmp + s_player_pos->x), (int)(y_tmp + s_player_pos->y));
			x--;
			j++;
		}
		y++;
		i++;
	}
}

void			ft_update_event_editor(t_my_event *s_event)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			s_event->quit = SDL_TRUE;
		else if (event.type == SDL_KEYDOWN)
			s_event->key[event.key.keysym.scancode] = SDL_TRUE;
	}
}

void			ft_init_event_editor(t_my_event *s_event)
{
	s_event->quit = SDL_FALSE;
	s_event->key[SDL_SCANCODE_ESCAPE] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_W] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_A] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_D] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_S] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_LEFT] = SDL_FALSE;
	s_event->key[SDL_SCANCODE_RIGHT] = SDL_FALSE;
}



void			ft_draw_map(int **map, int height, int width, SDL_Renderer *renderer_name)
{
	int					x;
	int					y;
	t_my_rectangle		s_rectangle;

	y = 0;
	s_rectangle.size = 20;
	while (y < height / 20)
	{
		x = 0;
		while (x < width / 20)
		{
			if (map[y][x] == 1)
			{
				s_rectangle.x = x * 20;
				s_rectangle.y = y * 20;
				ft_draw_rectangle(s_rectangle, renderer_name);
			}
			x++;
		}
		y++;
	}
}

void			ft_draw_rectangle(t_my_rectangle s_rectangle, SDL_Renderer *renderer_name)
{
	int			x;
	int			y;

	SDL_SetRenderDrawColor(renderer_name, 255, 255, 255, 0);
	y = s_rectangle.y;
	while (y < (s_rectangle.y + s_rectangle.size))
	{
		x = s_rectangle.x;
		while (x < s_rectangle.x + s_rectangle.size)
		{
			SDL_RenderDrawPoint(renderer_name, x, y);
			x++;
		}
		y++;
	}
}

void			ft_read_the_map(int height, int width, int **map)
{
	int		y;
	int		x;
	char	*line;
	int		fd;

	fd = open("mapwolf", O_RDWR);
	y = 0;
	while (y < height / 20)
	{
		get_next_line((const int)fd, &line);
		x = 0;
		while (x < width / 20)
		{
			map[y][x] = ft_my_atoi(line[x]);
			x++;
		}
		y++;
	}
	close(fd);
}

int				ft_my_atoi(char c)
{
	int		nb;

	nb = c - '0';
	return (nb);
}


void	ft_clear_window_in_blue(int height, int width, SDL_Renderer *renderer_name)
{
	int		x;
	int		y;

	SDL_SetRenderDrawColor(renderer_name, 0, 0, 255, 0);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			SDL_RenderDrawPoint(renderer_name, x, y);
			x++;
		}
		y++;
	}
}

int				**ft_init_map(int height, int width)
{
	int		**map;
	int		y;
	int		x;

	map = (int**)malloc(sizeof(int*) * (height / 20));
	y = 0;
	while (y < height / 20)
	{
		x = 0;
		map[y] = (int*)malloc(sizeof(int) * (width / 20));
		while (x < width / 20)
		{
			map[y][x] = 0;
			x++;
		}
		y++;
	}
	return (map);
}
