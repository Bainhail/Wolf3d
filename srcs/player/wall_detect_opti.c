/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect_opti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:30:52 by naali             #+#    #+#             */
/*   Updated: 2019/03/29 12:46:12 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double		dist_calc(double xa, double ya, double xb, double yb)
{
	double	dist;
	double	x;
	double	y;

	x = (xb - xa) * (xb - xa);
	y = (yb - ya) * (yb - ya);
	dist = sqrt(x + y);
	return (dist);
}

static double	recalc_ray_distance(double dist, int win_step)
{
	double		dist_cor;
	double		step;

	step = 60.0 / (double)WINX;
	if (win_step <= WINX/2)
	{
		step *= win_step;
		dist_cor = cos(conv_deg_to_rad(30.0 - step)) * dist;
	}
	else
	{
		step *= (win_step - WINX / 2);
		dist_cor = cos(conv_deg_to_rad(step)) * dist;
	}
	return (dist_cor);
}

static int		ft_get_wall_orientation(double angle, int orientation)
{
	if (orientation == X_COLISION)
	{
		if (cos(conv_deg_to_rad(angle - 90)) > 0)
			orientation = EAST_WALL;
		else
			orientation = WEST_WALL;
	}
	else if (orientation == Y_COLISION)
	{
		if (sin(conv_deg_to_rad(angle - 90)) > 0)
			orientation = SOUTH_WALL;
		else
			orientation = NORTH_WALL;
	}
	else
	{
		printf("NO wall orientation\n");
	}
	return (orientation);
}

static void		ft_load_texture_ft_orientation(t_print *w, t_my_raycast *s_raycast)
{
	if (s_raycast->orientation == EAST_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_x_east, &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == WEST_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_x_west, &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == SOUTH_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_y_south, &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == NORTH_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_y_north, &(s_raycast->srcrect), &(s_raycast->dstrect));
	else
		SDL_RenderCopy(w->renderer_3d, w->txt, &(s_raycast->srcrect), &(s_raycast->dstrect));
}

static void		ft_init_texture_wall_position(t_map *m, t_my_raycast *s_raycast)
{
	int le_delta;

	if (s_raycast->orientation == EAST_WALL || s_raycast->orientation == WEST_WALL)
		le_delta = (int)s_raycast->y % (int)m->ycase;
	else
		le_delta = (int)(s_raycast->x + 1.0) % (int)m->xcase;
	s_raycast->srcrect.x = le_delta;
	s_raycast->srcrect.y = 0;
	s_raycast->srcrect.w = 1;
	s_raycast->srcrect.h = 54;
	s_raycast->dstrect.x = s_raycast->window_x;
	s_raycast->dstrect.h = (int)s_raycast->hmp * 2;
	s_raycast->dstrect.y = (int)((double)WINY / 2.0) - (s_raycast->hmp / 2.0);
	s_raycast->dstrect.w = 1;
}

static void		ft_draw_wall(t_print *w, t_map *m, t_my_raycast *s_raycast)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		distance_ray;

	distance_ray = (s_raycast->dx >= 0 && s_raycast->dx < s_raycast->dy) ? s_raycast->dx : s_raycast->dy;
	distance_ray = recalc_ray_distance(distance_ray, s_raycast->window_x);
	s_raycast->orientation = (s_raycast->dx >= 0 && s_raycast->dx < s_raycast->dy) ? X_COLISION : Y_COLISION;
	s_raycast->orientation = ft_get_wall_orientation(s_raycast->angle, s_raycast->orientation);
	s_raycast->hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0;
	w_up = init_vtex(s_raycast->window_x, ((double)WINY / 2.0) - s_raycast->hmp, 0);
	w_bot = init_vtex(s_raycast->window_x, ((double)WINY / 2.0) + s_raycast->hmp, 0);
	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75);
	print_line(w, w->renderer_3d, init_vtex(s_raycast->window_x, 0, 0), w_up);
	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75);
	print_line(w, w->renderer_3d, w_bot, init_vtex(s_raycast->window_x, WINY, 0));
	ft_init_texture_wall_position(m, s_raycast);
	ft_load_texture_ft_orientation(w, s_raycast);
}

static int		ft_colision_detection(t_map *m, t_my_raycast *rc, double corx, double cory)
{
	if (rc->x <= 0 || rc->x > (WINX - 1))
		return (TRUE);
	else if (rc->y <= 0 || rc->y > (WINY - 1))
		return (TRUE);
	else if ((rc->x > 0 && rc->y > 0) && m->tab[(int)((rc->y + cory) / m->ycase)][(int)((rc->x + corx) / m->xcase)].z >= 1)
		return (TRUE);
	return (FALSE);
}

static void		ft_get_secteur_rayon(int x, int y, t_map *m, t_my_raycast *s_raycast)
{

	//effet de bord
	if (x == WINX - 1)
	{
		x+= 2;
	}
	if (y == WINY - 1)
	{
		y+= 3;
	}



	if (s_raycast->s_secteur.actuel_x != (int)(x / m->xcase) || s_raycast->s_secteur.actuel_y != (int)(y / m->ycase))
	{
		s_raycast->s_secteur.precedent_x = s_raycast->s_secteur.actuel_x;
		s_raycast->s_secteur.precedent_y = s_raycast->s_secteur.actuel_y;
		s_raycast->s_secteur.actuel_x = (int)(x / m->xcase);
		s_raycast->s_secteur.actuel_y = (int)(y / m->ycase);
	}
}

static void		ft_init_secteur_rayon(t_player *p, t_map *m, t_my_raycast *s_raycast)
{
	s_raycast->s_secteur.precedent_x = (int)(p->pos.x / m->xcase);
	s_raycast->s_secteur.precedent_y = (int)(p->pos.y / m->ycase);
	s_raycast->s_secteur.actuel_x = (int)(p->pos.x / m->xcase);
	s_raycast->s_secteur.actuel_y = (int)(p->pos.y / m->ycase);
}

static double	wall_x_detect(t_print *w, t_player *p, t_map *m, t_my_raycast *rc)
{
	double	step;
	double	dist;
	int		colision = FALSE;


	dist = -1;
	rc->x = (int)(p->pos.x / m->xcase);
	rc->x = rc->x * m->xcase + ((p->wl.dirx == 1) ? m->xcase : 0.0);
	step = m->xcase * p->wl.dirx;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 100);
	while (colision == FALSE)
	{
		rc->y = p->wl.a * rc->x + p->wl.b;
		if (rc->y > p->wl.ymax)
			p->wl.ymax = rc->y;
		if (rc->y < p->wl.ymin)
			p->wl.ymin = rc->y;
		if ((colision = ft_colision_detection(m, rc, p->wl.dirx, 0.0)) == FALSE)
			SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
		else
		{
			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50);
			if ((dist = dist_calc(p->pos.x, p->pos.y, rc->x, rc->y)) > 0)
				SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
			return (dist);
		}
		rc->x = rc->x + step;
	}
	return (dist);
}

static double	wall_y_detect(t_print *w, t_player *p, t_map *m, t_my_raycast *rc)
{
	double	step;
	double	tmp;
	double	dist;
	int		colision = FALSE;
	double	ymax;


	dist = -1.0;
	rc->y = (p->wl.diry > 0) ? ((int)(p->wl.ymin / m->ycase)) : ((int)(p->wl.ymax / m->ycase));
	rc->y = rc->y * m->ycase + ((p->wl.diry > 0) ? m->ycase : 0);
	step = m->ycase * p->wl.diry;
	ymax = (p->wl.diry > 0) ? p->wl.ymax : p->wl.ymin;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 100);
	while (colision == FALSE)
	{
		rc->x = (rc->y - p->wl.b) / p->wl.a;
		if ((colision = ft_colision_detection(m, rc, 0.0, p->wl.diry)) == FALSE)
			SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
		else
		{
			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50);
			if ((tmp = dist_calc(p->pos.x, p->pos.y, rc->x, rc->y)) > 0)
				SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
			if (dist < 0 || dist > tmp)
				dist = tmp;
		}
		rc->y = rc->y + step;
	}
	return (dist);
}

static void	init_coef(t_vertex j, t_wall *wl, double alpha)
{
	wl->x = (cos(conv_deg_to_rad(alpha - 90)) * 1.0) + j.x;
	wl->y = (sin(conv_deg_to_rad(alpha - 90)) * 1.0) + j.y;
	wl->a = (wl->y - j.y) / (wl->x - j.x);
	wl->b = j.y - (j.x * wl->a);
	wl->dirx = (wl->x < j.x) ? -1 : 1;
	wl->diry = (wl->y < j.y) ? -1 : 1;
	wl->ymin = wl->y;
	wl->ymax = wl->y;
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha/*, SDL_Texture *txt*/)
{
	double			step;
	double			max;
	t_my_raycast	s_raycast;

	t_vertex pos;

	s_raycast.window_x = 0;
	step = 60.0 / (double)WINX;
	s_raycast.angle = (double)alpha - 30;
	max = s_raycast.angle + 60;
	ft_init_secteur_rayon(p, m, &s_raycast);

	pos = init_vtex(p->pos.x, p->pos.y, 0);
	while (s_raycast.angle < max && s_raycast.window_x < WINX)
	{
		t_vertex wall;

		init_coef(p->pos, &(p->wl), s_raycast.angle);
		s_raycast.dx = wall_x_detect(w, p, m, &s_raycast);

		wall.x = s_raycast.x;
		wall.y = s_raycast.y;
		wall.z = 0.0;

		s_raycast.dy = wall_y_detect(w, p, m, &s_raycast);

		if (s_raycast.dx > s_raycast.dy)
			refresh_vtex(&wall, s_raycast.x, s_raycast.y, 0.0);
		else
		{
			s_raycast.x = wall.x;
			s_raycast.y = wall.y;
		}
		SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50);
		print_line(w, w->ren, pos, wall);



		ft_draw_wall(w, m, &s_raycast);
		ft_get_secteur_rayon(s_raycast.x, s_raycast.y, m, &s_raycast);
		s_raycast.angle += step;
		s_raycast.window_x++;
	}
}
