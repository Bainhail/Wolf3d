/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:58:06 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/24 14:53:23 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WINX 800
# define WINY 600
# define PLAYER -42
# define NORD 90
# define SUD -90
# define EST 0
# define OUEST 180
# define WALL 100
# define EYE 300
# define XCASE 50
# define YCASE 50
# define TRUE 1
# define FALSE 0

# include "includes.h"
# include "t_struct.h"

typedef struct		s_secteur_rayon
{
	int				precedent_x;
	int				precedent_y;
	int				actuel_x;
	int				actuel_y;
}					t_secteur_rayon;

typedef struct		s_my_event
{
	SDL_bool		key[SDL_NUM_SCANCODES];
	SDL_bool		quit;
}					t_my_event;

typedef enum		e_move_player
{
	UP,
	DOWN,
	TRIGO,
	ANTI
}					t_move_player;

/*
** a = coefficient directeur dans y = ax + b
** b = pas dans l'equation y = ax + b
** x = coordonnee x du 1er point
** y = coordonnee y du 1er point
** dirx = indication de la direction de la droite selon x
** diry = indication de la direction de la droite selon y
** ymin = permet de connaitre le debut
** ymax = et la fin des calculs de x selon y
** dans l'equation x = (y - b) / a
*/
typedef struct		s_wall
{
	double			a;
	double			b;
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			ymin;
	double			ymax;
}					t_wall;

typedef struct		s_my_raycast
{
	double			window_x;
	double			angle;
	double			x;
	double			y;
	int				orientation;
	double			hmp;
	SDL_Rect		srcrect;
	SDL_Rect		dstrect;
	t_secteur_rayon	s_secteur;
	double			dist_col_x;
	double			dist_col_y;
	double			step_cte_x;
	double			step_cte_y;
	int				colision;
	t_wall			wall_x_colision;
	t_wall			wall_y_colision;
}					t_my_raycast;

/*
** fd => FileDescriptor
** nbl => Nombre de ligne lu
** line => ligne renvoye par GNL
** tbline => tableau des lignes lu
*/
typedef struct		s_file
{
	int				fd;
	int				nbl;
	char			*line;
	char			**tbline;
}					t_file;

typedef struct		s_sgmt
{
	float			dx;
	float			dy;
	float			error;
	int				ystep;
	int				x;
	int				y;
	int				maxx;
}					t_sgmt;

/*
** f => Chemin du fichier
** x => x maximum de la carte
** y => y maximum de la carte
** z => z maximum de la carte
** xcase => Largeur X d'une case
** ycase => Hauteur Y d'une case
** tab => Tableau contenant toutes les coordonnees de la carte
*/
typedef struct		s_map
{
	t_file			f;
	int				xmax;
	int				ymax;
	int				zmax;
	float			xcase;
	float			ycase;
	t_vertex		**tab;
	int				debug;
}					t_map;

/*
** x et y => Case actuelle du joueur
** pos => position de l'oeil du personnage
** fov => cone de vu du personnage en degre
** flg_dir => orientation
** dir => orientation en vecteur
** s1, s2 et s3 sommet du triangle du personnage sur la carte
** dist => distance de vu maximum du personnage
** wl => correspond au mur vu
*/
typedef struct		s_player
{
	int				x;
	int				y;
	t_vertex		pos;
	int				fov;
	int				flg_dir;
	t_vertex		dir;
	t_vertex		s1;
	t_vertex		s2;
	t_vertex		s3;
	double			dist;
	t_wall			wl;
}					t_player;

typedef enum		e_renderer
{
	MAP_2D,
	MAP_3D,
}					t_renderer;

typedef enum		e_orientation_wall
{
	Y_COLISION,
	X_COLISION,
	NORTH_WALL,
	SOUTH_WALL,
	EAST_WALL,
	WEST_WALL,
	NONE,
}					t_orientation_wall;

typedef struct		s_print
{
	t_player		player;
	t_map			m;
	SDL_Renderer	*renderer[10];
	SDL_Texture		*texture[10];
	SDL_Window		*window[10];
	SDL_Renderer	*ren_flg;
	int				show;
}					t_print;

int					file_to_tab(char *path, t_map *m);
int					ft_get_the_map(char **av, t_print *p);

void				draw_square(SDL_Renderer *r, t_map *m, int x, int y);
void				print_line(t_print *w, SDL_Renderer *r, \
								t_vertex start, t_vertex end);

void				ft_event_loop(t_print *w);
void				calc_player_pos(t_map *m, t_player *p, int x, int y);
void				refresh_player_pos(t_map *m, t_player *p);
void				refresh_screen(t_print *w);

void				init_renderer(SDL_Renderer *r, t_map *m);
SDL_Texture			*loadbmp(SDL_Renderer *tmp_renderer, char *path);
void				ft_quit(char *str, t_print *s_win);
void				ft_raycast(t_print *w, t_player *p, t_map *m, int alpha);
double				dist_calc(double xa, double ya, double xb, double yb);
double				recalc_ray_distance(double dist, int win_step);
int					ft_colision_detection(t_map *m, t_my_raycast *rc, \
											double corx, double cory);
double				wall_y_detect(t_print *w, t_player *p, \
									t_map *m, t_my_raycast *rc);
double				wall_x_detect(t_print *w, t_player *p, \
									t_map *m, t_my_raycast *rc);
int					ft_get_wall_orientation(t_my_raycast *rc);
void				ft_load_texture_ft_orientation(t_print *w, \
													t_my_raycast *s_raycast);
void				ft_init_texture_wall_position(t_map *m, \
													t_my_raycast *s_raycast);
void				ft_draw_wall(t_print *w, t_map *m, t_my_raycast *rc);
void				ft_get_secteur_rayon(int x, int y, \
										t_map *m, t_my_raycast *s_raycast);
void				ft_init_secteur_rayon(t_player *p, t_map *m, \
											t_my_raycast *rc);
void				ft_load_bmp(t_print *p);
void				ft_init_player_pos(t_print *w, t_player *p, t_map *m);
void				wall_x_detect_calcul_x(t_player *player, t_map *map, \
											t_my_raycast *rc);
void				wall_x_detect_calcul_y(t_player *player, t_my_raycast *rc);

void				ft_enable_mouse_motion(int boolean, int *mouse);
void				ft_map_trigger(t_print *w, int boolean);

int					ft_correction_pos(double x, double y, t_print *w);
int					ft_correction_pos_front(double x, double y, t_print *w);
int					ft_correction_pos_back(double x, double y, t_print *w);
void				ft_apply_correction(t_print *w, double x, double y);

void				ft_mouse_move(int rot, t_print *w);
void				ft_move_leftright(int move, t_print *w);
void				ft_move(int move, t_print *w);
int					ft_check_if_player(t_map m);
int					ft_check_line_and_push(t_map *m);
int					check_line(char **l, int *fd);

#endif
