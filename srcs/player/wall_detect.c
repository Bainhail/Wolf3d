/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/21 14:39:46 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
void		static wall_function(t_print *w, double dist, double x);

double		dist_calc(double xa, double ya, double xb, double yb)
{
	double	dist;
	double	x;
	double	y;

	x = (xb - xa) * (xb - xa);
	y = (yb - ya) * (yb - ya);
	dist = sqrt(x + y);
	return (dist);
}


int		static ft_colision_detection(t_map *m, int tmp_x, int tmp_y)
{
	if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1)
		return (TRUE);
	return (FALSE);
}

void		wall_detect(t_print *w, t_player *p, t_map *m, double alpha, int window_x)
{
	double		dist;
	double		distmax;
	double		x;
	double		y;
	int tmp_x;
	int tmp_y;
	int colision;

	dist = 0;
	colision = FALSE;
	distmax = m->xcase * 2;
	x = 0;
	y = 0;
	while (dist < distmax && colision == FALSE)
	{
		x = cos(conv_deg_to_rad(alpha - 90)) * dist;
		y = sin(conv_deg_to_rad(alpha - 90)) * dist;
		tmp_x = p->pos.x + x;
		tmp_y = p->pos.y + y;
		if ((colision = ft_colision_detection(m, tmp_x, tmp_y)) == FALSE)
		{
			SDL_RenderDrawPoint(w->ren, tmp_x, tmp_y);
			dist++;
		}
		else
		{		
			dist = dist_calc(p->pos.x, p->pos.y, tmp_x, tmp_x);
			if (dist > 0)
				wall_function(w, dist, (double)window_x);
		}
	}
}

void		static wall_function(t_print *w, double dist, double x)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		hmp;// hauteur du mur percu par le joueur.

	hmp = (((double)EYE * (double)WALL) / dist) / 2.0;
	w_up = init_vtex(x, ((double)WINY / 2.0) - hmp, 0);
	w_bot = init_vtex(x, ((double)WINY / 2.0) + hmp, 0);
	SDL_SetRenderDrawColor(w->renderer_3d, 127, 0, 127, 75);
	print_line(w, w_up, w_bot);
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	double	step;
	double	angle;
	double	max;
	int		window_x;

	window_x = 0;
	step = 60.0 / (double)WINX;
	angle = (double)alpha - 30;
	max = angle + 60;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50);
	while (angle < max && window_x < WINX)
	{
		wall_detect(w, p, m, angle, window_x);
		angle += step;
		window_x++;
	}
}
