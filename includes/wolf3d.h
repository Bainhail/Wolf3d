/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:58:06 by jchardin          #+#    #+#             */
/*   Updated: 2019/03/27 13:37:19 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef		WOLF3D_H
# define	WOLF3D_H

# define WINX 800
# define WINY 600
# define PLAYER -42
# define NORD 90
# define SUD -90
# define EST 0
# define OUEST 180
# define WALL 100
# define EYE 300

# include "includes.h"
# include "t_struct.h"


typedef enum		e_renderer
{
	MAP_2D,
	MAP_3D,
}					t_renderer;

typedef enum		e_bool
{
	FALSE = 0,
	TRUE = 1,
}					t_bool;

typedef struct		s_secteur_rayon
{
	int				precedent_x;
	int 			precedent_y;
	int				actuel_x;
	int				actuel_y;
}					t_secteur_rayon;

typedef struct			s_my_event
{
	SDL_bool			key[SDL_NUM_SCANCODES];
	SDL_bool			quit;
}						t_my_event;

typedef enum e_move_player
{
	UP,
	DOWN,
	TRIGO,
	ANTI
}			s_move_player;

typedef struct		s_file
{
	int			fd;//       File Descriptor
	int			nbl;//      Nombre de ligne
	char		*line;//    Ligne renvoyer par GNL
	char		**tbline;// Tableau des lignes mis bout a bout
}					t_file;

typedef struct		s_sgmt
{
	float			dx;
	float			dy;
	float			error;
	int				ystep;
	int				x;
	int				y;
	int				maxX;
}					t_sgmt;

typedef struct		s_map
{
	t_file		f;//     Path du fichier
	int			xmax;//  X max de la carte
	int			ymax;//  Y max de la carte
	int			zmax;//  Z max de la carte
	float		xcase;// Largeur d'une case
	float		ycase;// Hauteur d'une case
	t_vertex	**tab;// Tableau contenant toute les coordonnees de la carte
}					t_map;

typedef struct		s_player
{
	int				x;
	int				y;
	t_vertex		pos;//  Remplace posX posY eye (Centre du personnage)
	int				fov;//  (30° de chaque cote de la mediane)
	int				flg_dir;//Flag de Direction (NORD SUD EST OUEST)
	t_vertex		dir;//  (Nord:[0:-1:0]) (Sud=[0:1:0]) (Est=[1:0:0]) (Ouest=[-1:0:0])
	t_vertex		s1;//   Sommet 1 triangle personnage
	t_vertex		s2;//   Sommet 2 triangle personnage
	t_vertex		s3;//   Sommet 3 triangle personnage
	double			dist;// Distance de vu max du joueur
}					t_player;

typedef struct		s_print
{
	t_player		pl;//     (Voir s_player)
	t_map			m;//      (Voir s_map)
	SDL_Window		*w;//     Pointeur de la fenetre
	SDL_Renderer	*ren;//   Pointeur du renderer sauvegarder de la carte
	SDL_Window		*window_3d;
	SDL_Renderer	*renderer_3d;
	SDL_Renderer	*ren_flg;
	SDL_Texture		*txt;
	SDL_Texture		*txt_x_west;
	SDL_Texture		*txt_x_east;
	SDL_Texture		*txt_y_north;
	SDL_Texture		*txt_y_south;
	SDL_Texture		*txt_y;
}					t_print;

int					file_to_tab(char *path, t_map *m);
int					draw_square(SDL_Renderer *r, t_map *m, int x, int y);
int					get_player_pos(t_print *w, t_player *p, t_map *m);
void				print_line(t_print *w, SDL_Renderer *r, t_vertex start, t_vertex end);
void				ft_event_loop(t_print *w);
int					init_renderer(SDL_Renderer *r, t_map *m);
void				calc_player_pos(t_map *m, t_player *p, int x, int y);
void				refresh_player_pos(t_map *m, t_player *p);
void				refresh_screen(t_print *w);
SDL_Texture			*loadBMP(SDL_Renderer *tmp_renderer, char *path);


void				ft_quit(t_print *p);
int					ft_get_the_map(char **av, t_print *p);
void				ft_raycast(t_print *w, t_player *p, t_map *m, int alpha);



#endif
