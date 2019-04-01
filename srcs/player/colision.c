/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:48:48 by naali             #+#    #+#             */
/*   Updated: 2019/04/01 14:07:02 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_colision_detection(t_map *m, t_my_raycast *rc, \
							  double corx, double cory)
{
	int		x;
	int		y;

	x = (int)((rc->x + ((corx < 0) ? corx : 0.0)) / m->xcase);
	y = (int)((rc->y + ((cory < 0) ? cory : 0.0)) / m->ycase);
	if (rc->x <= 0 || rc->x > (WINX - 1))
		return (TRUE);
	else if (rc->y <= 0 || rc->y > (WINY - 1))
		return (TRUE);
	else if ((rc->x > 0 && rc->y > 0) && m->tab[y][x].z >= 1)
		return (TRUE);
	return (FALSE);
}
