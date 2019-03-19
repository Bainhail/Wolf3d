/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/19 15:40:57 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wall_detect(t_print *w, t_player *p, t_map *m, int alpha)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;
	int tmp_x;
	int tmp_y;

	dist = 0;
	distmax = 40.0;
	x = 0;
	y = 0;
	while (dist < distmax)
	{
		x = cos(conv_deg_to_rad(alpha - 90)) * dist;
		y = sin(conv_deg_to_rad(alpha - 90)) * dist;
		tmp_x = p->pos.x + x;
		tmp_y = p->pos.y + y;
		SDL_RenderDrawPoint(w->ren, tmp_x, tmp_y);
		dist++;
		if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1)
		{
			printf("alpha = %d, WALL\n", alpha - 90);
			return;
		}
	}
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	SDL_SetRenderDrawColor(w->ren, 255, 0, 0, 100);
	wall_detect(w, p, m, alpha);
	SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 100);
	wall_detect(w, p, m, alpha - 30);
	SDL_SetRenderDrawColor(w->ren, 0, 0, 255, 100);
	wall_detect(w, p, m, alpha + 30);
}
