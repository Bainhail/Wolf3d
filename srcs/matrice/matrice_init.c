/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_matrice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:46:38 by naali             #+#    #+#             */
/*   Updated: 2019/02/06 18:50:12 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

t_matrice	init_matrice(void)
{
	t_matrice	matrice;

	matrice.tab[0][0] = 1;
	matrice.tab[0][1] = 0;
	matrice.tab[0][2] = 0;
	matrice.tab[0][3] = 0;
	matrice.tab[1][0] = 0;
	matrice.tab[1][1] = 1;
	matrice.tab[1][2] = 0;
	matrice.tab[1][3] = 0;
	matrice.tab[2][0] = 0;
	matrice.tab[2][1] = 0;
	matrice.tab[2][2] = 1;
	matrice.tab[2][3] = 0;
	matrice.tab[3][0] = 0;
	matrice.tab[3][1] = 0;
	matrice.tab[3][2] = 0;
	matrice.tab[3][3] = 1;
	return (matrice);
}
