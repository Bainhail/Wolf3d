/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:44:41 by naali             #+#    #+#             */
/*   Updated: 2019/03/14 18:43:34 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*Calc s1 s2 s3 a mettre en 1 fonction*/

t_vertex	calc_s1(t_map *m, t_vertex *pos, double flg)
{
	t_vertex	s1;

	s1.x = pos->x;
	s1.y = pos->y - ((double)m->ycase / 3);
	s1.z = pos->z;
	s1 = rotate_around_new_center(&s1, pos, flg);
	return (s1);
}

t_vertex	calc_s2(t_map *m, t_vertex *pos, double flg)
{
	t_vertex	s2;

	s2.x = pos->x - ((double)m->xcase / 3);
	s2.y = pos->y + ((double)m->ycase / 3);
	s2.z = pos->z;
	s2 = rotate_around_new_center(&s2, pos, flg);
	return (s2);
}

t_vertex	calc_s3(t_map *m, t_vertex *pos, double flg)
{
	t_vertex	s3;

	s3.x = pos->x + ((double)m->xcase / 3);
	s3.y = pos->y + ((double)m->ycase / 3);
	s3.z = pos->z;
	s3 = rotate_around_new_center(&s3, pos, flg);
	return (s3);
}

void		calc_player_pos(t_map *m, t_player *p, int x, int y)
{
	p->x = x;
	p->y = y;
	p->pos.x = ((double)x * (double)(m->xcase)) + ((double)(m->xcase) / 2);// Calcul du centre
	p->pos.y = ((double)y * (double)(m->ycase)) + ((double)(m->ycase) / 2);// de la case player
	p->pos.z = 0;
	p->flg_dir = NORD;// flag d'orientation
	p->s1 = calc_s1(m, &(p->pos), p->flg_dir);// Calcul du 1er sommet
	p->s2 = calc_s2(m, &(p->pos), p->flg_dir);// Calcul du 2eme sommet
	p->s3 = calc_s3(m, &(p->pos), p->flg_dir);// Calcul du 3eme sommet
}

int			get_player_pos(t_print *w, t_player *p, t_map *m)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->ymax)
	{
		j = 0;
		while (j < m->xmax)
		{
			if (m->tab[i][j].z == PLAYER)
			{
				calc_player_pos(m, p, j, i);
				print_line(w, p->s1, p->s2);
				print_line(w, p->s1, p->s3);
				print_line(w, p->s3, p->s2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
