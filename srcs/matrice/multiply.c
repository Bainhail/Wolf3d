/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:35:57 by naali             #+#    #+#             */
/*   Updated: 2019/02/28 09:11:05 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

t_vertex	mult_vtex_by_mat(t_matrice mat, t_vertex pvt)
{
	double	x;
	double	y;
	double	z;

	x = pvt.x * mat.tab[0][0] + pvt.y * mat.tab[0][1] \
			+ pvt.z * mat.tab[0][2] + mat.tab[0][3];
	y = pvt.x * mat.tab[1][0] + pvt.y * mat.tab[1][1] \
			+ pvt.z * mat.tab[1][2] + mat.tab[1][3];
	z = pvt.x * mat.tab[2][0] + pvt.y * mat.tab[2][1] \
			+ pvt.z * mat.tab[2][2] + mat.tab[2][3];
	return (init_vtex(x, y, z, pvt.color));
}
