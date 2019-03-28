/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect_opti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:30:52 by naali             #+#    #+#             */
/*   Updated: 2019/03/28 15:31:20 by naali            ###   ########.fr       */
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

static int		ft_get_colision_type(int x, int y, t_my_raycast *s_raycast)
{
	int		orientation;

	orientation = -1;
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (x == 0)
		orientation = X_COLISION;
	else if (y == 0)
		orientation = Y_COLISION;
	else if (s_raycast->s_secteur.actuel_x == s_raycast->s_secteur.precedent_x && s_raycast->s_secteur.actuel_y == s_raycast->s_secteur.precedent_y)
		printf("NO change ==> probleme\n");
	else if (s_raycast->s_secteur.actuel_x == s_raycast->s_secteur.precedent_x)
		orientation = Y_COLISION;
	else if (s_raycast->s_secteur.actuel_y == s_raycast->s_secteur.precedent_y)
		orientation = X_COLISION;
	else
	{
		printf("%d\n", s_raycast->s_secteur.actuel_x);
		printf("%d\n", s_raycast->s_secteur.actuel_y);
		printf("%d\n", s_raycast->s_secteur.precedent_x);
		printf("%d\n", s_raycast->s_secteur.precedent_y);
		printf("AUCUN ==> probleme\n");
	}
	return (orientation);
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
		le_delta = (int)s_raycast->x % (int)m->xcase;
	s_raycast->srcrect.x = le_delta;
	s_raycast->srcrect.y = 0;
	s_raycast->srcrect.w = 1;
	s_raycast->srcrect.h = 54;
	s_raycast->dstrect.x = s_raycast->window_x;
	s_raycast->dstrect.h = (int)s_raycast->hmp * 2;
	s_raycast->dstrect.y = (int)((double)WINY / 2.0) - (s_raycast->hmp / 2.0);
	s_raycast->dstrect.w = 1;
}

static void		ft_draw_wall(t_print *w, t_map *m, t_player *p, t_my_raycast *s_raycast)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		distance_ray;

//	distance_ray = dist_calc(p->pos.x, p->pos.y, s_raycast->x, s_raycast->y);
	distance_ray = (s_raycast->dx >= 0 && s_raycast->dx < s_raycast->dy) ? s_raycast->dx : s_raycast->dy;
	distance_ray = recalc_ray_distance(distance_ray, s_raycast->window_x);
//	s_raycast->orientation = ft_get_colision_type(s_raycast->x, s_raycast->y, s_raycast);
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

/* static void		ft_draw_wall(t_print *w, double distance_ray, double x_window/\* , t_secteur_rayon s_secteur, int x, int y, t_map *m *\/) */
/* { */
/* 	t_vertex	w_up; */
/* 	t_vertex	w_bot; */
/* 	double		hmp;// hauteur du mur percu par le joueur. */

/* 	hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0; */
/* 	w_up = init_vtex(x_window, ((double)WINY / 2.0) - hmp, 0); */
/* 	w_bot = init_vtex(x_window, ((double)WINY / 2.0) + hmp, 0); */
/* 	if (w->txt == NULL) */
/* 	{ */
/* 		printf("LA TEXTURE ?!\n"); */
/* 		exit(0); */
/* 	} */
/* 	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75); */
/* 	print_line(w, w->renderer_3d, init_vtex(x_window, 0, 0), w_up); */

/* 	SDL_SetRenderDrawColor(w->renderer_3d, 27, 0, 127, 75); */
/* 	print_line(w, w->renderer_3d, w_up, w_bot); */

/* 	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75); */
/* 	print_line(w, w->renderer_3d, w_bot, init_vtex(x_window, WINY, 0)); */
/* } */

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

/* static int		ft_colision_detection(t_map *m, int tmp_x, int tmp_y) */
/* { */
/* 	if (tmp_x <= 0.0 || tmp_x >= (double)(WINX - 1)) */
/* 		return(TRUE); */
/* 	else if (tmp_y <= 0.0 || tmp_y >= (double)(WINY - 1)) */
/* 		return(TRUE); */
/* 	else if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1) */
/* 		return (TRUE); */
/* 	return (FALSE); */
/* } */

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
	//printf("XY =%d =%d\n", x, y);
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
	double	tmp;
	double	dist;
	int		colision = FALSE;


	dist = -1;
	rc->x = (int)(p->pos.x / m->xcase);
	rc->x = rc->x * m->xcase + ((p->wl.dirx == 1) ? m->xcase : 0.0);
	step = m->xcase * p->wl.dirx;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 100);
//	while (rc->x >= 0 && rc->x <= WINX)
	while (colision == FALSE)
	{
		rc->y = p->wl.a * rc->x + p->wl.b;
		if (rc->y > p->wl.ymax)
			p->wl.ymax = rc->y;
		if (rc->y < p->wl.ymin)
			p->wl.ymin = rc->y;
//		if ((colision = ft_colision_detection(m, rc->x + p->wl.dirx, rc->y)) == FALSE)
		if ((colision = ft_colision_detection(m, rc, p->wl.dirx, 0.0)) == FALSE)
			SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
		else
		{
			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50);
			if ((tmp = dist_calc(p->pos.x, p->pos.y, rc->x, rc->y)) > 0)
				SDL_RenderDrawPoint(w->ren, rc->x, rc->y);
			if (dist < 0 || dist > tmp)
				dist = tmp;
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
//	while (rc->y != ymax && (rc->y >= 0 && rc->y <= WINY + 1))
	while (colision == FALSE)
	{
		rc->x = (rc->y - p->wl.b) / p->wl.a;
//		if ((colision = ft_colision_detection(m, rc->x, rc->y + p->wl.diry)) == FALSE)
//		if ((colision = ft_colision_detection(m, rc)) == FALSE)
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
	double			dx;
	double			dy;
	t_my_raycast	s_raycast;

	/* m->xcase = (double)WINX / m->xmax; */
	/* m->ycase = (double)WINY / m->ymax; */


	s_raycast.window_x = 0;
	step = 60.0 / (double)WINX;
	s_raycast.angle = (double)alpha - 30;
	max = s_raycast.angle + 60;
	ft_init_secteur_rayon(p, m, &s_raycast);
	while (s_raycast.angle < max && s_raycast.window_x < WINX)
	{
		init_coef(p->pos, &(p->wl), s_raycast.angle);
		s_raycast.dx = wall_x_detect(w, p, m, &s_raycast);
		s_raycast.dy = wall_y_detect(w, p, m, &s_raycast);
		/* if (dy > 0 && dy < dx) */
		/* { */
		ft_get_secteur_rayon(s_raycast.x, s_raycast.y, m, &s_raycast);
		ft_draw_wall(w, m, p, &s_raycast);
//			ft_draw_wall(w, recalc_ray_distance(dy, s_raycast.window_x), (double)(s_raycast.window_x));
/* 		} */
/* 		else if (dx > 0 && dx < dy) */
/* 		{ */
/* 			ft_draw_wall(w, m, p, &s_raycast); */
/* //			ft_draw_wall(w, recalc_ray_distance(dx, s_raycast.window_x), (double)(s_raycast.window_x)); */
/* 		} */
		s_raycast.angle += step;
		s_raycast.window_x++;
	}
}

/* void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha/\*, SDL_Texture *txt*\/) */
/* { */
/* 	double	step; */
/* 	double	angle; */
/* 	double	max; */
/* 	int		window_x; */
/* 	double	dx; */
/* 	double	dy; */

/* 	m->xcase = (double)WINX / m->xmax; */
/* 	m->ycase = (double)WINY / m->ymax; */


/* 	window_x = 0; */
/* 	step = 60.0 / (double)WINX; */
/* 	angle = (double)alpha - 30; */
/* 	max = angle + 60; */
/* 	while (angle < max && window_x < WINX) */
/* 	{ */
/* 		init_coef(p->pos, &(p->wl), angle); */
/* 		dx = wall_x_detect(w, p, m); */
/* 		dy = wall_y_detect(w, p, m); */
/* 		if (dy > 0 && dy < dx) */
/* 			ft_draw_wall(w, recalc_ray_distance(dy, window_x), (double)window_x); */
/* 		else if (dx > 0 && dx < dy) */
/* 			ft_draw_wall(w, recalc_ray_distance(dx, window_x), (double)window_x); */
/* 		angle += step; */
/* 		window_x++; */
/* 	} */
/* } */
