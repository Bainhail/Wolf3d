/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/19 16:01:47 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wall_detect(t_print *w, t_player *p, t_map *m, double alpha)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;
	int tmp_x;
	int tmp_y;

	dist = 0;
	distmax = m->xcase * 2;
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
			printf("alpha = %.1f, WALL\n", alpha - 90);
			return;
		}
	}
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	double	step;
	double	angle;
	double	max;

	step = 60.0 / (double)WINX;
	printf("step = %.1f\n", step);
	angle = (double)alpha - 30;
	max = angle + 60;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50);
	while (angle < max)
	{
		wall_detect(w, p, m, angle);
		angle += step;
	}

}
