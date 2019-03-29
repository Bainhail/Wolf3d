/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secteur_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:59:14 by naali             #+#    #+#             */
/*   Updated: 2019/03/29 16:12:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_get_secteur_rayon(int x, int y, t_map *m, t_my_raycast *s_raycast)
{
	if (x == WINX - 1)
	{
		x += 2;
	}
	if (y == WINY - 1)
	{
		y += 3;
	}
	x = (int)(x / m->xcase);
	y = (int)(y / m->ycase);
	if (s_raycast->s_secteur.actuel_x != x \
		|| s_raycast->s_secteur.actuel_y != y)
	{
		s_raycast->s_secteur.precedent_x = s_raycast->s_secteur.actuel_x;
		s_raycast->s_secteur.precedent_y = s_raycast->s_secteur.actuel_y;
		s_raycast->s_secteur.actuel_x = x;
		s_raycast->s_secteur.actuel_y = y;
	}
}

void			ft_init_secteur_rayon(t_player *p, t_map *m, t_my_raycast *rc)
{
	rc->s_secteur.precedent_x = (int)(p->pos.x / m->xcase);
	rc->s_secteur.precedent_y = (int)(p->pos.y / m->ycase);
	rc->s_secteur.actuel_x = (int)(p->pos.x / m->xcase);
	rc->s_secteur.actuel_y = (int)(p->pos.y / m->ycase);
}
