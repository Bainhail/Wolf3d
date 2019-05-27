/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 09:44:41 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 11:19:35 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			ft_init_player_pos(t_print *w, t_player *p, t_map *m)
{
	int		i;
	int		j;
	int		found;

	i = 0;
	found = 0;
	(void)w;
	while (i < m->ymax)
	{
		j = 0;
		while (j < m->xmax)
		{
			if ((int)(m->tab[i][j].z) == PLAYER && found == 0)
			{
				m->tab[i][j].z = 0;
				p->flg_dir = EST;
				calc_player_pos(m, p, j, i);
				found = 1;
			}
			else if ((int)(m->tab[i][j].z) < 0)
				m->tab[i][j].z = 0;
			j++;
		}
		i++;
	}
}
