/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/18 17:26:06 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_vertex		wall_detect(t_print *w, t_player *p)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;
	t_vertex	wall;

	dist = 0;
	distmax = 10.0;
	x = 0;//p->pos.x;
	y = 0;//p->pos.y;
	wall.x = 0;
	wall.y = 0;
	wall.z = 0;
	SDL_SetRenderDrawColor(w->ren, 0, 0, 255, 100);
	while (dist < distmax)
	{
		x = cos(conv_deg_to_rad(p->flg_dir - 90)) * dist;
		y = sin(conv_deg_to_rad(p->flg_dir - 90)) * dist;
		SDL_RenderDrawPoint(w->ren, (p->pos.x + x), (p->pos.y + y));
/* 		if (m->tab[(unsigned int)x][(unsigned int)y].z == 1) */
/* 		{ */
/* 			wall.x = x; */
/* 			wall.y = y; */
/* 			wall.z = 1; */
/* 			return (wall); */
/* 		} */
		dist++;
	}
	return (wall);
}
