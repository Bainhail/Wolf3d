/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_struct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:36:30 by naali             #+#    #+#             */
/*   Updated: 2019/03/14 15:19:48 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STRUCT_H
# define T_STRUCT_H

# include "includes.h"

typedef struct	s_vect
{
	double		x;
	double		y;
}				t_vect;

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vertex;

typedef struct	s_matrice
{
	double		tab[4][4];
}				t_matrice;

/*
** Fichier:
** convert.c
*/
double			conv_deg_to_rad(double degree);
double			conv_rad_to_deg(double radian);

/*
** Fichier:
** t_vect.c
*/
t_vect			init_vect(double p_x, double p_y);
void			refresh_vect(t_vect *vect, double p_x, double p_y);

/*
** Fichier:
** t_vertex.c
*/
t_vertex		init_vtex(double p_x, double p_y, double p_z);
void			refresh_vtex(t_vertex *vect, double p_x,\
							double p_y, double p_z);

/*
** Fichier:
** t_matrice.c
*/
t_matrice		init_matrice();

/*
** Fichier:
** matrice_rot.c
*/
t_matrice		set_x_matrice(double angle_degree);
t_matrice		set_y_matrice(double angle_degree);
t_matrice		set_z_matrice(double angle_degree);
t_vertex		rotate_around_new_center(t_vertex *point, \
										 t_vertex *center, \
										 double degree);

/*
** Fichier:
** matrice_scal.c
*/
t_matrice		set_zoom_matrice(double p_zoom);
t_matrice		set_sca_matrice(double sx, double sy, double sz);

/*
** Fichier:
** matrice_trans.c
*/
t_matrice		set_t_matrice(double t_x, double t_y, double t_z);

/*
** Fichier:
** mult_vtex_by_mat.c
*/
t_vertex		mult_vtex_by_mat(t_matrice mat, t_vertex pvt);

/*
** Fichier:
** mult_matrice.c
*/
t_matrice		mult_matrice(t_matrice m1, t_matrice m2);

#endif
