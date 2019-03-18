/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/18 18:05:08 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wall_detect(t_print *w, t_player *p, t_map *m)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;

	dist = 0;
	distmax = 20.0;
	x = 0;//p->pos.x;
	y = 0;//p->pos.y;
	SDL_SetRenderDrawColor(w->ren, 0, 0, 255, 100);
	printf("x = %.1f, y = %.1f\n", p->pos.x, p->pos.y);
	while (dist < distmax)
	{
		x = cos(conv_deg_to_rad(p->flg_dir - 90)) * dist;
		y = sin(conv_deg_to_rad(p->flg_dir - 90)) * dist;
		printf("\n\nz = %.1f\n\n", m->tab[(int)(y / m->ycase)][(int)(x / m->xcase)].z);
		if (m->tab[(int)(y / WINY)][(int)(x / WINY)].z >= 1)
			printf("WALL\n");
/* 		printf("\n\nx = %.1f, y = %.1f\n", p->pos.x + x, p->pos.y + y); */
/* 		printf("x = %d, y = %d\n", (int)((p->pos.x + x)/m->xcase), (int)((p->pos.y + y)/m->ycase)); */
		SDL_RenderDrawPoint(w->ren, (p->pos.x + x), (p->pos.y + y));
		dist++;
	}
	int		x1, y1;
	y1 = 0;
	while (y1 < 10)
	{
		x1 = 0;
		while (x1 < 18)
		{
			printf("%.1f\t", m->tab[y1][x1].z);
			x1++;
		}
		printf("\n");
		y1++;
	}
//	print_tab(m->tab);
}
