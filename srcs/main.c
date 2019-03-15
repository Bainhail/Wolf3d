/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 12:31:57 by naali             #+#    #+#             */
/*   Updated: 2019/03/15 17:06:40 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct			s_xyz_point
{
	float				a;
	float				b;
}						t_xyz_point;

typedef struct			s_myputtheline
{
	int					above;
	t_xyz_point			un;
	t_xyz_point			deux;
	int					ex;
	int					ey;
	int					dx;
	int					dy;
	int					d_x;
	int					d_y;
	int					i;
	int					j;
	int					x_incr;
	int					y_incr;
	float				ab;
	float				le_z1;
	float				le_z2;
}						t_myputtheline;

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
	int					angle_variable;
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

typedef struct			s_my_rayon
{
	int					view_angle;

}						t_my_rayon;

void	ft_clear_window_in_blue(int height, int width, SDL_Renderer *renderer_name);
void	ft_read_the_map(int height, int width, int **map);
int		ft_my_atoi(char c);
int		**ft_init_map(int height, int width);
void	ft_draw_map(int **map, int height, int width, SDL_Renderer *renderer_name);
void	ft_draw_rectangle(t_my_rectangle s_rectangle, SDL_Renderer *renderer_name);
void	ft_update_event_editor(t_my_event *s_event);
void	ft_init_event_editor(t_my_event *s_event);
void	ft_move_player(int move, t_my_player_pos *s_player_pos, SDL_Renderer *name_renderer, t_my_rectangle s_triangle, int height, int width, int **map, t_my_rayon *s_rayon);
void	ft_draw_triangle(SDL_Renderer *name_renderer, t_my_rectangle s_triangle, t_my_player_pos *s_player_pos, int height, int width, int **map);
void	ft_draw_line(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_case_five(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_case_four(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_case_three(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_case_two(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_case_one(SDL_Renderer *name_renderer, t_myputtheline *s_line);
void	ft_draw_grid(SDL_Renderer *name_renderer, int height, int width);


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
	t_my_rayon		s_rayon;

	height = 480;
	width = 640;

	s_player_pos.x = 20;
	s_player_pos.y = 20;
	s_player_pos.angle = (M_PI / 2) / M_PI * 180;
	s_player_pos.angle_variable = 10;
	s_rectangle.x = 0;
	s_rectangle.y = 0;
	s_rectangle.size = 0;
	s_triangle.x = 10;
	s_triangle.y = 10;
	s_triangle.size = 10;
	s_rayon.view_angle = 60;

	SDL_Init(SDL_INIT_EVERYTHING);
	window_name = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer_name = SDL_CreateRenderer(window_name, 0, SDL_RENDERER_SOFTWARE);
	ft_clear_window_in_blue(height, width, renderer_name);
	map = ft_init_map(height, width);
	ft_read_the_map(height, width, map);
	ft_draw_grid(renderer_name, height, width);
	ft_draw_map(map, height, width, renderer_name);
	ft_draw_triangle(renderer_name, s_triangle, &s_player_pos, height, width, map);
	SDL_RenderPresent(renderer_name );

	s_event.quit = SDL_FALSE;
	while (!s_event.quit)
	{
		ft_init_event_editor(&s_event);
		ft_update_event_editor(&s_event);
		s_event.key[SDL_SCANCODE_ESCAPE] ? s_event.quit = SDL_TRUE : 0 ;
		s_event.key[SDL_SCANCODE_W] ? ft_move_player(UP, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		s_event.key[SDL_SCANCODE_A] ? ft_move_player(LEFT, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		s_event.key[SDL_SCANCODE_D] ? ft_move_player(RIGHT, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		s_event.key[SDL_SCANCODE_S] ? ft_move_player(DOWN, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		s_event.key[SDL_SCANCODE_LEFT] ? ft_move_player(TRIGO, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		s_event.key[SDL_SCANCODE_RIGHT] ? ft_move_player(ANTITRIGO, &s_player_pos, renderer_name, s_triangle, height, width, map, &s_rayon) : 0 ;
		SDL_Delay(2);
	}
	SDL_DestroyWindow(window_name);
	SDL_Quit();
	return (0);
}

void			ft_move_player(int move, t_my_player_pos *s_player_pos, SDL_Renderer *name_renderer, t_my_rectangle s_triangle, int height, int width, int **map, t_my_rayon *s_rayon)
{
	(void)s_rayon;
	int		x;
	int		y;
	int		angle;

	x = 0;
	y = 0;
	angle = 0;

	//	move == UP ? printf("je monte\n") : 0 ;
	//	move == DOWN ? printf("je descend\n") : 0 ;
	//	move == RIGHT ? printf("je vais a droite\n") : 0 ;
	//	move == LEFT ? printf("je vais a gauche\n") : 0 ;
	//	move == TRIGO ? printf("tourne sens trigo\n") : 0 ;
	//	move == ANTITRIGO ? printf("tourne sens antitrigo\n") : 0 ;

	move == UP ?		y = -5 : 0 ;
	move == DOWN ?		y =  5 : 0 ;
	move == RIGHT ? 	x =  5 : 0 ;
	move == LEFT ?		x = -5 : 0 ;
	move == TRIGO ? 	angle = 1 : 0 ;
	move == ANTITRIGO ?	angle = -1 : 0 ;

	//s_player_pos->x += x;
	//s_player_pos->y += y;
	s_player_pos->angle += angle;

	//je sais pas pk les 90 et le -=
	s_player_pos->x -= (x * cos((s_player_pos->angle + 90) * M_PI / 180)) + (y * sin((s_player_pos->angle + 90) * M_PI / 180));
	s_player_pos->y -= (x * -sin((s_player_pos->angle + 90) * M_PI / 180)) + (y *  cos((s_player_pos->angle + 90) * M_PI / 180));

	ft_clear_window_in_blue(height, width, name_renderer);
	ft_draw_grid(name_renderer, height, width);
	ft_draw_map(map, height, width, name_renderer);
	ft_draw_triangle(name_renderer, s_triangle, s_player_pos, height, width, map);
	SDL_RenderPresent(name_renderer);
}

void		ft_draw_triangle(SDL_Renderer *name_renderer, t_my_rectangle s_triangle, t_my_player_pos *s_player_pos, int height, int width, int **map)
{
	int		x;
	int		y;
	int		i;
	int		j;

	x = 0;
	i = 0;
	while (i < s_triangle.size)
	{
		y = i;
		j = 0;

		while (j < (2 * i))
		{
			float x_tmp = (x * cos(s_player_pos->angle * M_PI / 180)) + (y * sin(s_player_pos->angle * M_PI / 180));
			float y_tmp = (x * -sin(s_player_pos->angle * M_PI / 180)) + (y *  cos(s_player_pos->angle * M_PI / 180));
			SDL_RenderDrawPoint(name_renderer, (int)(x_tmp + s_player_pos->x), (int)(y_tmp + s_player_pos->y));
			y--;
			j++;
		}
		x--;
		i++;
	}


	t_myputtheline s_line;

	//ligne droite
	s_line.un.a = s_player_pos->x;
	s_line.un.b = s_player_pos->y;
	s_line.deux.a = (30 * cos(s_player_pos->angle * M_PI / 180)) + (0 * sin(s_player_pos->angle * M_PI / 180)) + s_player_pos->x;
	s_line.deux.b = (30 * -sin(s_player_pos->angle * M_PI / 180)) + (0 *  cos(s_player_pos->angle * M_PI / 180)) + s_player_pos->y;
	ft_draw_line(name_renderer, &s_line);

	//ligne a -30
	s_line.un.a = s_player_pos->x;
	s_line.un.b = s_player_pos->y;
	s_line.deux.a = (30 * cos((s_player_pos->angle - 30)  * M_PI / 180)) + (0 * sin((s_player_pos->angle  - 30)* M_PI / 180)) + s_player_pos->x;
	s_line.deux.b = (30 * -sin((s_player_pos->angle - 30) * M_PI / 180)) + (0 *  cos((s_player_pos->angle  - 30)* M_PI / 180)) + s_player_pos->y;
	ft_draw_line(name_renderer, &s_line);

	//ligne a +30
	s_line.un.a = s_player_pos->x;
	s_line.un.b = s_player_pos->y;
	s_line.deux.a = (30 * cos((s_player_pos->angle + 30)  * M_PI / 180)) + (0 * sin((s_player_pos->angle  + 30)* M_PI / 180)) + s_player_pos->x;
	s_line.deux.b = (30 * -sin((s_player_pos->angle + 30) * M_PI / 180)) + (0 *  cos((s_player_pos->angle  + 30)* M_PI / 180)) + s_player_pos->y;
	ft_draw_line(name_renderer, &s_line);


	SDL_SetRenderDrawColor(name_renderer, 255, 0, 0, 0);
	//angle variable = 10
	s_line.un.a = s_player_pos->x;
	s_line.un.b = s_player_pos->y;



///////////////////////////////////////////////////////////////////////////////////////////////////////
	//DDA AVEC DES VECTEURS
///////////////////////////////////////////////////////////////////////////////////////////////////////

	float	field_of_view = 60;
	float	dir_x = cos(s_player_pos->angle * M_PI / 180);
	float	dir_y = -sin(s_player_pos->angle * M_PI / 180);


	float	screen_x = -dir_y;
	float	screen_y =  dir_x;

	float	tangante_fov = tan(field_of_view / 2.0 * M_PI / 180.0);

	float 	ray_dir_x;
	float 	ray_dir_y;

	float	screen_scale;


	float	colision_array[width + 1];

	x = -1;
	//while (++x < width)
	//{

	x = width / 2 + 1; //

		screen_scale = (float)((2 * x / width) - 1);

		ray_dir_x = dir_x + (screen_x * screen_scale) * tangante_fov;
		ray_dir_y = dir_y + (screen_y * screen_scale) * tangante_fov;
		printf("\nl'angle du joueur =%d\n", s_player_pos->angle);
		printf(" ray_dir_x =%f\n", ray_dir_x);
		printf(" ray_dir_y =%f\n", ray_dir_y);


		float	distance_vertical_in_cell;
		float	distance_btw_vertical_line_x = 1 * 20;
		float	distance_btw_vertical_line_y = ((float)ray_dir_y * (1.0 / (float)ray_dir_x)) * 20;
		float 	distance_btw_vertical =
 		   	sqrt((distance_btw_vertical_line_x ) * (distance_btw_vertical_line_x ) + (distance_btw_vertical_line_y ) * (distance_btw_vertical_line_y));


		printf("La distance entre ligne vertical_x =%f\n", distance_btw_vertical_line_x);
		printf("La distance entre ligne vertical_y =%f\n", distance_btw_vertical_line_y);
		printf("L'hypotenuse =%f\n", distance_btw_vertical);

		float	distance_horizontal_in_cell;
		float	distance_btw_horizontal_line_x = ((float)ray_dir_x * (1.0 / (float)ray_dir_y)) * 20;
		float	distance_btw_horizontal_line_y = 1 * 20;
		float	distance_btw_horizontal
			= sqrt((distance_btw_horizontal_line_x) * (distance_btw_horizontal_line_x) + (distance_btw_horizontal_line_y) * (distance_btw_horizontal_line_y));

		printf("\nLa distance entre ligne horizontal_x =%f\n", distance_btw_horizontal_line_x);
		printf("La distance entre ligne horizontal_y =%f\n", distance_btw_horizontal_line_y);
		printf("L'hypotenuse =%f\n\n", distance_btw_horizontal);



		int	dir_step_x;
		int	dir_step_y;
		if(ray_dir_x > 0)
		{
			distance_vertical_in_cell = (1 - (((float)s_player_pos->x / 20) - (s_player_pos->x / 20))) * distance_btw_vertical; 
			dir_step_x = 1;
		}
		else
		{
			distance_vertical_in_cell = ((((float)s_player_pos->x / 20) - (s_player_pos->x / 20))) * distance_btw_vertical;
			dir_step_x = -1;
		}

		if(ray_dir_y > 0)
		{
			distance_horizontal_in_cell = (1 - (((float)s_player_pos->y / 20) - (s_player_pos->y / 20))) * distance_btw_horizontal; 
			dir_step_y = 1;
		}
		else
		{
			distance_horizontal_in_cell = ((((float)s_player_pos->y / 20) - (s_player_pos->y / 20))) * distance_btw_horizontal;
			dir_step_y = -1;
		}

		int sideHit;
		int colision = 0;;
		float	vertical_distance = distance_vertical_in_cell;
		float	horizontal_distance = distance_horizontal_in_cell;

		printf("La distance vertical in cell =%f\n", distance_vertical_in_cell);
		printf("La distance horizontal in cell =%f\n", distance_horizontal_in_cell);


		int		world_index_x = (int)(s_player_pos->x / 20);
		int		world_index_y = (int)(s_player_pos->y / 20);
		printf("POS JOUEUR = %d %d\n", world_index_x, world_index_y);


		int first_step = 1;
		while (colision == 0)
		{
			if (first_step == 1)
			{
				if(vertical_distance < horizontal_distance)
				{
					world_index_x += dir_step_x;
					sideHit = 0; // north or south
				}
				else
				{
					world_index_y += dir_step_y;
					sideHit = 1; //ouest or east
				}
			}
			else
			{
				if(vertical_distance < horizontal_distance)
				{
					vertical_distance += distance_btw_vertical;
					world_index_x += dir_step_x;
					sideHit = 0; // north or south
				}
				else
				{
					horizontal_distance += distance_btw_horizontal;
					world_index_y += dir_step_y;
					sideHit = 1; //ouest or east
				}
			}
			first_step = 0;
			printf("Les test = %d  %d\n", world_index_x, world_index_y);
			if(world_index_x > width / 20 || world_index_y > height / 20)
				colision = 1;
			else if(world_index_x < 0 || world_index_y < 0)
				colision = 1;
			else if (map[world_index_y][world_index_x] == 1)
				colision = 1;
		}


		if(vertical_distance < horizontal_distance)
			colision_array[x] = vertical_distance;
		else
			colision_array[x] = horizontal_distance;

		printf("=%d distance to colision =%f\n\n\n\n",x ,  colision_array[x]);

//////////////////////////////////////////////////////////////////////////////////////
//tracage du rayon
//





		//}


/*


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// HORIZONTAL
	//angle du rayon lance par rapport au joueur est de +21 degre catching horizontal line de couleur rouge

	s_player_pos->angle %= 360;
	if (s_player_pos->angle < 0)
		s_player_pos->angle += 360;




	//balayage rayon +30 a -30
	float angle_rayon;
	angle_rayon = 30;
	float step = 0.01;
	while (angle_rayon > -30)
	{
		angle_rayon -= step;



		float Ay;
		float angle_alpha = (90 + s_player_pos->angle + angle_rayon);

		//printf("\n\n L'angle alpha =%f\n", angle_alpha);
		//printf("test Horizontal\n");
		//angle_alpha = (int)angle_alpha % 360;
		if (angle_alpha < 0)
			angle_alpha += 360;
		if (angle_alpha < 0)
			angle_alpha += 360;
		if (angle_alpha > 360)
			angle_alpha -= 360;
		if (angle_alpha > 360)
			angle_alpha -= 360;
		if (angle_alpha > 360)
			printf("++\n");
		if (angle_alpha < 0)
			printf("--\n");

		//prblm pour le tan(90) et tan (0)
		if (angle_alpha == 0 || angle_alpha == 90)
			angle_alpha += 0.1;

		//we will find Ya and Xa
		if (angle_alpha  > 180) // the ray is facing down
			Ay = ((s_player_pos->y / 20) * 20) + 20;
		else
			Ay = ((s_player_pos->y / 20) * 20) - 1;
		float Ax = (s_player_pos->y - Ay) / tan(((angle_alpha) * M_PI / 180)) + s_player_pos->x;

		if (Ax < 0)
			Ax = 0;

		//calcul de la constante horizontal
		float const_horizontal_X = 20 / tan(angle_alpha * M_PI / 180);
		float const_horizontal_Y = 20;

		if(const_horizontal_X < 0)
			const_horizontal_X *= -1;

		float X = 0;
		float Y = 0;
		if ( (angle_alpha - 0) >= 0 && (angle_alpha - 0) < 90)
		{
			X = 1;
			Y = -1;
		}
		else if((angle_alpha - 0) >= 90 && (angle_alpha - 0) < 180)
		{
			X = -1;
			Y = -1;
		}
		else if((angle_alpha - 0) >= 180 && (angle_alpha - 0) < 270)
		{
			X = -1;
			Y = 1;
		}
		else if((angle_alpha - 0) >= 270 && (angle_alpha - 0) <= 360)
		{
			X = 1;
			Y = 1;
		}

		float k;
		int colision;

		colision = 0;
		k  = -1;

		while (colision == 0)
		{
			k++;

			s_line.deux.a = Ax + ( X * k * const_horizontal_X);
			s_line.deux.b = Ay + ( Y * k * const_horizontal_Y);
			if (s_line.deux.b < 0)
			{
				//printf("colision bord gauche\n");
				colision = 1;
				s_line.deux.b = 0;
			}
			if (s_line.deux.a < 0)
			{
				colision = 1;
				//printf("colision bord haut\n");
				s_line.deux.a = 0;
			}
			if (s_line.deux.a > (640 - 3))
			{
				colision = 1;
				//printf("colision bord droit\n");
				s_line.deux.a = 639;
			}
			if (s_line.deux.b > (480 - 3))
			{
				colision = 1;
				//printf("colision bord bas\n");
				s_line.deux.b = 479;
			}
			if (colision != 1)
			{
				if (map[(int)((((s_line.deux.b) / 20) + 0))][(int)((((s_line.deux.a) / 20 ) + 0))])
					colision = 1;
			}
			else
			{
				//printf("pas de colison\n");
			}
		}

		//pythagore pour avoir la distance

		float cote_x = s_player_pos->x - s_line.deux.a;
		float cote_y = s_player_pos->x - s_line.deux.b;
		float distance_horizontal = sqrt((( cote_x) *  (cote_x  ))  +  ((cote_y  ) * (cote_y )));
		float save_horizontal_x = s_line.deux.a;
		float save_horizontal_y = s_line.deux.b;

		//ft_draw_line(name_renderer, &s_line);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//VERTICAL
		//angle du rayon lance par rapport au joueur est de +21 degre catching vertical line de couleur rouge


		//printf("\n\ntest vertical\n");
		angle_alpha = (90 + s_player_pos->angle + angle_rayon);

		angle_alpha = (int)angle_alpha % 360;
		if (angle_alpha < 0)
			angle_alpha += 360;


		//prblm pour le tan(90) et tan (0)
		if (angle_alpha == 0 ||  angle_alpha == 90)
			angle_alpha += 1;

		float Bx;
		if (angle_alpha > 90 && angle_alpha < 270) // the ray is going left
			Bx = (s_player_pos->x / 20) * 20 - 1;
		else
			Bx = (s_player_pos->x / 20) * 20 + 20;

		//prblm avec 270 degre
		if(angle_alpha == 270)
			angle_alpha += 1;
		float By = s_player_pos->y - (tan(angle_alpha * M_PI / 180) * (Bx - s_player_pos->x));

		//if (By < 0)
		//By = 0;
		//	s_line.deux.a = Bx;
		//	s_line.deux.b = By;
		//	ft_draw_line(name_renderer, &s_line);


		//calcul de la constante vertical
		float const_vertical_X = 20;
		float const_vertical_Y = 20 * tan(angle_alpha * M_PI / 180);


		if (const_vertical_Y < 0)
			const_vertical_Y *= -1;
		if (const_vertical_X < 0)
			const_vertical_X *= -1;

		if ( (angle_alpha - 0) >= 0 && (angle_alpha - 0) < 90)
		{
			X = 1;
			Y = -1;
		}
		else if((angle_alpha - 0) >= 90 && (angle_alpha - 0) < 180)
		{
			X = -1;
			Y = -1;
		}
		else if((angle_alpha - 0) >= 180 && (angle_alpha - 0) < 270)
		{
			X = -1;
			Y = 1;
		}
		else if((angle_alpha - 0) >= 270 && (angle_alpha - 0) <= 360)
		{
			X = 1;
			Y = 1;
		}


		colision = 0;
		k = -1;

		while (colision == 0)
		{
			k++;

			s_line.deux.a = Bx + (k *  X * const_vertical_X);
			s_line.deux.b = By + (k * Y * const_vertical_Y);

			if (s_line.deux.b < 0)
			{
				//printf("colision bord gauche\n");
				colision = 1;
				s_line.deux.b = 0;
			}
			if (s_line.deux.a < 0)
			{
				colision = 1;
				//printf("colision bord haut\n");
				s_line.deux.a = 0;
			}
			if (s_line.deux.a > 640)
			{
				colision = 1;
				//printf("colision bord droit\n");
				s_line.deux.a = 639;
			}
			if (s_line.deux.b > 480)
			{
				colision = 1;
				//printf("colision bord bas\n");
				s_line.deux.b = 479;
			}

			//printf("le b =%d et le a =%d \n", (int)((s_line.deux.b ) / 20), (int)((s_line.deux.a / 20)));

			if (colision != 1)
			{
				if (map[(int)((s_line.deux.b / 20 ) + 0)][(int)((s_line.deux.a / 20 ) + 0)])
				{
					//printf("colision mur\n");
					colision = 1;
				}
			}
			else
			{
				//printf("pas de colison\n");
			}

		}
		cote_x = s_player_pos->x - s_line.deux.a;
		cote_y = s_player_pos->x - s_line.deux.b;
		float distance_vertical = sqrt((( cote_x) *  (cote_x  ))  +  ((cote_y  ) * (cote_y )));
		float save_vertical_x = s_line.deux.a;
		float save_vertical_y = s_line.deux.b;


		//printf ("la distance vertical = %f \n la distance horizontal = %f \n", distance_vertical, distance_horizontal);


		if (distance_vertical < distance_horizontal)
		{
			ft_draw_line(name_renderer, &s_line);
			//printf ("la distance vertical = %f\n", distance_vertical);
		}
		else
		{
			s_line.deux.a = save_horizontal_x;
			s_line.deux.b = save_horizontal_y;
			ft_draw_line(name_renderer, &s_line);
			//printf ("la distance horizontal = %f\n", distance_horizontal);
		}
	}
*/
}

void			ft_draw_grid(SDL_Renderer *name_renderer, int height, int width)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	t_myputtheline line;

	SDL_SetRenderDrawColor(name_renderer, 255, 255, 0, 0);

	y1 = 0;
	y2 = height;
	x1 = 0;
	x2 = x1;

	while (x1 < width)
	{
		line.un.a = x1;
		line.un.b = y1;
		line.deux.a = x2;
		line.deux.b = y2;
		ft_draw_line(name_renderer, &line);
		x1  += 20;
		x2 = x1;
	}
	y1 = 0;
	y2 = y1;
	x1 = 0;
	x2 = width;

	while (y1 < height)
	{
		line.un.a = x1;
		line.un.b = y1;
		line.deux.a = x2;
		line.deux.b = y2;
		ft_draw_line(name_renderer, &line);
		y1  += 20;
		y2 = y1;
	}

}

void		ft_draw_line(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	s_line->ex = abs((int)s_line->un.a - (int)s_line->deux.a);
	s_line->ey = abs((int)s_line->un.b - (int)s_line->deux.b);
	s_line->dx = 2 * s_line->ex;
	s_line->dy = 2 * s_line->ey;
	s_line->d_x = s_line->ex;
	s_line->d_y = s_line->ey;
	s_line->i = 0;
	s_line->x_incr = 1;
	s_line->y_incr = 1;
	if (s_line->deux.a > s_line->un.a)
		s_line->x_incr = -1;
	if (s_line->deux.b > s_line->un.b)
		s_line->y_incr = -1;
	if (s_line->dy == 0)
		ft_case_one(name_renderer, s_line);
	if (s_line->d_x > s_line->d_y)
		ft_case_two(name_renderer, s_line);
	if (s_line->dx == s_line->dy)
		ft_case_three(name_renderer, s_line);
	if (s_line->d_x < s_line->d_y)
		ft_case_four(name_renderer, s_line);
	if (s_line->dx == 0)
		ft_case_five(name_renderer, s_line);
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

void			ft_case_one(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(name_renderer, (int)s_line->deux.a,
				(int)s_line->deux.b);
		s_line->deux.a += s_line->x_incr;
	}
}

void			ft_case_two(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		SDL_RenderDrawPoint(name_renderer, (int)s_line->deux.a,
				(int)s_line->deux.b);
		(s_line->i)++;
		s_line->deux.a += s_line->x_incr;
		s_line->ex -= s_line->dy;
		if (s_line->ex < 0)
		{
			s_line->deux.b += s_line->y_incr;
			s_line->ex += s_line->dx;
		}
	}
}

void			ft_case_three(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_x)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(name_renderer, (int)s_line->deux.a,
				(int)s_line->deux.b);
		s_line->deux.a += s_line->x_incr;
		s_line->deux.b += s_line->y_incr;
	}
}

void			ft_case_four(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_y)
	{
		SDL_RenderDrawPoint(name_renderer, (int)s_line->deux.a,
				(int)s_line->deux.b);
		(s_line->i)++;
		s_line->deux.b += s_line->y_incr;
		s_line->ey -= s_line->dx;
		if (s_line->ey < 0)
		{
			s_line->deux.a += s_line->x_incr;
			s_line->ey += s_line->dy;
		}
	}
}

void			ft_case_five(SDL_Renderer *name_renderer, t_myputtheline *s_line)
{
	while (s_line->i <= s_line->d_y)
	{
		(s_line->i)++;
		SDL_RenderDrawPoint(name_renderer, (int)s_line->deux.a,
				(int)s_line->deux.b);
		s_line->deux.b += s_line->y_incr;
	}
}
