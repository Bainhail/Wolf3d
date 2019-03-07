/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:10:16 by naali             #+#    #+#             */
/*   Updated: 2019/02/06 18:51:14 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_struct.h"

t_vect		init_vect(double p_x, double p_y)
{
	t_vect	vect;

	vect.x = p_x;
	vect.y = p_y;
	return (vect);
}

void		refresh_vect(t_vect *vect, double p_x, double p_y)
{
	vect->x = p_x;
	vect->y = p_y;
}
