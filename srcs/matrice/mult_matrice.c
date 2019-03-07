/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_matrice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 10:17:25 by naali             #+#    #+#             */
/*   Updated: 2019/01/29 17:09:36 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

static void		mult_part1(t_matrice *ret, t_matrice m1, t_matrice m2)
{
	ret->tab[0][0] = m1.tab[0][0] * m2.tab[0][0] + m1.tab[0][1] * m2.tab[0][1]\
		+ m1.tab[0][2] * m2.tab[0][2] + m1.tab[0][3] * m2.tab[0][3];
	ret->tab[0][1] = m1.tab[0][0] * m2.tab[1][0] + m1.tab[0][1] * m2.tab[1][1]\
		+ m1.tab[0][2] * m2.tab[1][2] + m1.tab[0][3] * m2.tab[1][3];
	ret->tab[0][2] = m1.tab[0][0] * m2.tab[2][0] + m1.tab[0][1] * m2.tab[2][1]\
		+ m1.tab[0][2] * m2.tab[2][2] + m1.tab[0][3] * m2.tab[2][3];
	ret->tab[0][3] = m1.tab[0][0] * m2.tab[3][0] + m1.tab[0][1] * m2.tab[3][1]\
		+ m1.tab[0][2] * m2.tab[3][2] + m1.tab[0][3] * m2.tab[3][3];
}

static void		mult_part2(t_matrice *ret, t_matrice m1, t_matrice m2)
{
	ret->tab[1][0] = m1.tab[1][0] * m2.tab[0][0] + m1.tab[1][1] * m2.tab[0][1]\
		+ m1.tab[1][2] * m2.tab[0][2] + m1.tab[1][3] * m2.tab[0][3];
	ret->tab[1][1] = m1.tab[1][0] * m2.tab[1][0] + m1.tab[1][1] * m2.tab[1][1]\
		+ m1.tab[1][2] * m2.tab[1][2] + m1.tab[1][3] * m2.tab[1][3];
	ret->tab[1][2] = m1.tab[1][0] * m2.tab[2][0] + m1.tab[1][1] * m2.tab[2][1]\
		+ m1.tab[1][2] * m2.tab[2][2] + m1.tab[1][3] * m2.tab[2][3];
	ret->tab[1][3] = m1.tab[1][0] * m2.tab[3][0] + m1.tab[1][1] * m2.tab[3][1]\
		+ m1.tab[1][2] * m2.tab[3][2] + m1.tab[1][3] * m2.tab[3][3];
}

static void		mult_part3(t_matrice *ret, t_matrice m1, t_matrice m2)
{
	ret->tab[2][0] = m1.tab[2][0] * m2.tab[0][0] + m1.tab[2][1] * m2.tab[0][1]\
		+ m1.tab[2][2] * m2.tab[0][2] + m1.tab[2][3] * m2.tab[0][3];
	ret->tab[2][1] = m1.tab[2][0] * m2.tab[1][0] + m1.tab[2][1] * m2.tab[1][1]\
		+ m1.tab[2][2] * m2.tab[1][2] + m1.tab[2][3] * m2.tab[1][3];
	ret->tab[2][2] = m1.tab[2][0] * m2.tab[2][0] + m1.tab[2][1] * m2.tab[2][1]\
		+ m1.tab[2][2] * m2.tab[2][2] + m1.tab[2][3] * m2.tab[2][3];
	ret->tab[2][3] = m1.tab[2][0] * m2.tab[3][0] + m1.tab[2][1] * m2.tab[3][1]\
		+ m1.tab[2][2] * m2.tab[3][2] + m1.tab[2][3] * m2.tab[3][3];
}

static void		mult_part4(t_matrice *ret, t_matrice m1, t_matrice m2)
{
	ret->tab[3][0] = m1.tab[3][0] * m2.tab[0][0] + m1.tab[3][1] * m2.tab[0][1]\
		+ m1.tab[3][2] * m2.tab[0][2] + m1.tab[3][3] * m2.tab[0][3];
	ret->tab[3][1] = m1.tab[3][0] * m2.tab[1][0] + m1.tab[3][1] * m2.tab[1][1]\
		+ m1.tab[3][2] * m2.tab[1][2] + m1.tab[3][3] * m2.tab[1][3];
	ret->tab[3][2] = m1.tab[3][0] * m2.tab[2][0] + m1.tab[3][1] * m2.tab[2][1]\
		+ m1.tab[3][2] * m2.tab[2][2] + m1.tab[3][3] * m2.tab[2][3];
	ret->tab[3][3] = m1.tab[3][0] * m2.tab[3][0] + m1.tab[3][1] * m2.tab[3][1]\
		+ m1.tab[3][2] * m2.tab[3][2] + m1.tab[3][3] * m2.tab[3][3];
}

t_matrice		mult_matrice(t_matrice m1, t_matrice m2)
{
	t_matrice	ret;

	mult_part1(&ret, m1, m2);
	mult_part2(&ret, m1, m2);
	mult_part3(&ret, m1, m2);
	mult_part4(&ret, m1, m2);
	return (ret);
}
