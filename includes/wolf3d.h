/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:15:38 by naali             #+#    #+#             */
/*   Updated: 2019/03/12 14:37:41 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF3D_H
# define	WOLF3D_H

# define WINX 800
# define WINY 600

# include "includes.h"
# include "t_struct.h"

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
	float			posx;// Position dans le tableau a traduire en position fenetre
	float			posy;// Position dans le tableau a traduire en position fenetre
	t_vertex		dir;//  (Nord:0:-1:0) (Sud=0:1:0) (Est=1:0:0) (Ouest=-1:0:0) (Le Z de la direction permettra d'orienter le regard dur personnage vers le HAUT ou le BAS par la suite).
	int				fov;//  (30° de chaque cote de la mediane)
}					t_player;

typedef struct		s_print
{
	t_vertex		player;// sera remplacer par la structure player
	t_map			m;//      (Voir s_map)
	SDL_Window		*w;//     Pointeur de la fenetre
	SDL_Renderer	*ren;//   Pointeur du renderer sauvegarder de la carte
}					t_print;

int			file_to_tab(char *path, t_map *m);
void		print_line1(t_win *w, t_vect start, t_vect end);

#endif
