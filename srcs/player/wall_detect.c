/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/18 18:25:57 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wall_detect(t_print *w, t_player *p, t_map *m)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;


	int tmp_x;
	int tmp_y;

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
		tmp_x = p->pos.x + x;
		tmp_y = p->pos.y + y;
		SDL_RenderDrawPoint(w->ren, tmp_x, tmp_y);
		dist++;
	}
	if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1)
		printf("WALL\n");
	else
		printf("no WALL\n");


	//affichage tab
//	int		x1, y1;
//	y1 = 0;
//	while (y1 < 10)
//	{
//		x1 = 0;
//		while (x1 < 18)
//		{
//			printf("%.1f\t", m->tab[y1][x1].z);
//			x1++;
//		}
//		printf("\n");
//		y1++;
//	}
}
