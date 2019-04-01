/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:44:41 by naali             #+#    #+#             */
/*   Updated: 2019/04/01 13:45:46 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
				p->flg_dir = EST;
				calc_player_pos(m, p, j, i);
				print_line(w, w->ren, p->s1, p->s2);
				print_line(w, w->ren, p->s1, p->s3);
				print_line(w, w->ren, p->s3, p->s2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
