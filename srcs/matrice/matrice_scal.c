/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_scal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:55:29 by naali             #+#    #+#             */
/*   Updated: 2019/02/06 18:50:53 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

t_matrice	set_zoom_matrice(double p_zoom)
{
	t_matrice matrice;

	matrice.tab[0][0] = p_zoom;
	matrice.tab[0][1] = 0;
	matrice.tab[0][2] = 0;
	matrice.tab[0][3] = 0;
	matrice.tab[1][0] = 0;
	matrice.tab[1][1] = p_zoom;
	matrice.tab[1][2] = 0;
	matrice.tab[1][3] = 0;
	matrice.tab[2][0] = 0;
	matrice.tab[2][1] = 0;
	matrice.tab[2][2] = p_zoom;
	matrice.tab[2][3] = 0;
	matrice.tab[3][0] = 0;
	matrice.tab[3][1] = 0;
	matrice.tab[3][2] = 0;
	matrice.tab[3][3] = 1;
	return (matrice);
}

t_matrice	set_sca_matrice(double s_x, double s_y, double s_z)
{
	t_matrice matrice;

	matrice.tab[0][0] = s_x;
	matrice.tab[0][1] = 0;
	matrice.tab[0][2] = 0;
	matrice.tab[0][3] = 0;
	matrice.tab[1][0] = 0;
	matrice.tab[1][1] = s_y;
	matrice.tab[1][2] = 0;
	matrice.tab[1][3] = 0;
	matrice.tab[2][0] = 0;
	matrice.tab[2][1] = 0;
	matrice.tab[2][2] = s_z;
	matrice.tab[2][3] = 0;
	matrice.tab[3][0] = 0;
	matrice.tab[3][1] = 0;
	matrice.tab[3][2] = 0;
	matrice.tab[3][3] = 1;
	return (matrice);
}
