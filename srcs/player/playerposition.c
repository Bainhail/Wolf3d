/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:44:41 by naali             #+#    #+#             */
/*   Updated: 2019/03/18 15:22:50 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		init_player_dir(t_player *p)
{
	p->flg_dir = EST;// flag d'orientation
	p->dir.x = 1;
	p->dir.y = 0;
	p->dir.z = 0;
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
				m->tab[i][j].z = 0;
				init_player_dir(p);
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
