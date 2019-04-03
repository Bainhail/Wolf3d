/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:27 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 09:59:52 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static double	check_colision(t_print *w, t_player *p, t_my_raycast *r, int *c)
{
	double		dist;

	dist = -1;
	if ((*c = ft_colision_detection(&(w->m), r, p->wl.dirx, p->wl.diry)) == FALSE)
		SDL_RenderDrawPoint(w->renderer[MAP_2D], r->x, r->y);
	else
	{
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 0, 255, 50);
		if ((dist = dist_calc(p->pos.x, p->pos.y, r->x, r->y)) > 0)
			SDL_RenderDrawPoint(w->renderer[MAP_2D], r->x, r->y);
	}
	return (dist);
}

static void		init_wall_x(t_player *p, t_map *m, t_my_raycast *rc, double *s)
{
	rc->x = (int)(p->pos.x / m->xcase);
	rc->x = rc->x * m->xcase + ((p->wl.dirx == 1) ? m->xcase : 0.0);
	*s = m->xcase * p->wl.dirx;
}

double			wall_x_detect(t_print *w, t_player *p, t_map *m, \
												t_my_raycast *rc)
{
	double	step;
	double	dist;
	int		colision;

	dist = 0;
	init_wall_x(p, m, rc, &step);
	colision = FALSE;
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 100);
	while (colision == FALSE)
	{
		if (rc->angle != 90 && rc->angle != 270)
		{
			rc->y = p->wl.a * rc->x + p->wl.b;
		}
		else
		{
			printf("angle 90 x =%.1f\n", p->wl.b);
			rc->y = rc->x /*+ p->wl.b*/;
		}
		if (rc->y > p->wl.ymax)
			p->wl.ymax = rc->y;
		if (rc->y < p->wl.ymin)
			p->wl.ymin = rc->y;
		if ((dist = check_colision(w, p, rc, &colision)) >= 0)
			return (dist);
		rc->x = rc->x + step;
	}
	return (dist);
}

static void		init_wall_y(t_player *p, t_map *m, t_my_raycast *rc, double *s)
{
	rc->y = (p->wl.diry > 0) ? ((int)(p->wl.ymin / m->ycase)) : ((int)(p->wl.ymax / m->ycase));
	rc->y = rc->y * m->ycase + ((p->wl.diry > 0) ? m->ycase : 0);
	*s = m->ycase * p->wl.diry;
}

double			wall_y_detect(t_print *w, t_player *p, t_map *m, t_my_raycast *rc)
{
	double	step;
	double	tmp;
	double	dist;
	int		colision;

	dist = -1.0;
	colision = FALSE;
	init_wall_y(p, m, rc, &step);
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 100);
	while (colision == FALSE)
	{
		if (rc->angle == 90 || rc->angle == 270)
			printf("HELLO\n");
		if (rc->angle != 90 && rc->angle != 270)
			rc->x = (rc->y - p->wl.b) / p->wl.a;
		else
			rc->x = (rc->y /* - p->wl.b*/);
		if ((tmp = check_colision(w, p, rc, &colision)) >= 0)
		{
			if (dist < 0 || (tmp >= 0 && dist > tmp))
				dist = tmp;
			return (dist);
		}
		rc->y = rc->y + step;
	}
	return (dist);
}
