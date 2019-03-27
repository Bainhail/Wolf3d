/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect_opti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:30:52 by naali             #+#    #+#             */
/*   Updated: 2019/03/26 15:12:46 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

typedef struct		s_secteur_rayon
{
	int precedent_x;
	int precedent_y;
	int actuel_x;
	int actuel_y;
}					t_secteur_rayon;

static void		ft_draw_wall(t_print *w, double distance_ray, double x_window/* , t_secteur_rayon s_secteur, int x, int y, t_map *m */)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		hmp;// hauteur du mur percu par le joueur.

	hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0;
	w_up = init_vtex(x_window, ((double)WINY / 2.0) - hmp, 0);
	w_bot = init_vtex(x_window, ((double)WINY / 2.0) + hmp, 0);
	if (w->txt == NULL)
	{
		printf("LA TEXTURE ?!\n");
		exit(0);
	}
	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75);
	print_line(w, w->renderer_3d, init_vtex(x_window, 0, 0), w_up);

	SDL_SetRenderDrawColor(w->renderer_3d, 27, 0, 127, 75);
	print_line(w, w->renderer_3d, w_up, w_bot);

	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75);
	print_line(w, w->renderer_3d, w_bot, init_vtex(x_window, WINY, 0));
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

static int		ft_colision_detection(t_map *m, int tmp_x, int tmp_y)
{
	if (tmp_x <= 0.0 || tmp_x >= (double)(WINX - 1))
		return(TRUE);
	else if (tmp_y <= 0.0 || tmp_y >= (double)(WINY - 1))
		return(TRUE);
	else if (m->tab[(int)(tmp_y / m->ycase)][(int)(tmp_x / m->xcase)].z >= 1)
		return (TRUE);
	return (FALSE);
}

static double	wall_x_detect(t_print *w, t_player *p, t_map *m)
{
	double	x;
	double	y;
	double	step;
	double	dist;
	int		colision = FALSE;


	x = (int)(p->pos.x / m->xcase);
	x = x * m->xcase + ((p->wl.dirx == 1) ? m->xcase : 0.0);
	step = m->xcase * p->wl.dirx;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 100);
	while (x >= 0 && x <= WINX)
	{
		y = p->wl.a * x + p->wl.b;
		if (y > p->wl.ymax)
			p->wl.ymax = y;
		if (y < p->wl.ymin)
			p->wl.ymin = y;
		if ((colision = ft_colision_detection(m, x + p->wl.dirx, y)) == FALSE)
			SDL_RenderDrawPoint(w->ren, x, y);
		else
		{
			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50);
			if ((dist = dist_calc(p->pos.x, p->pos.y, x, y)) > 0)
				SDL_RenderDrawPoint(w->ren, x, y);
			return (dist);
		}
		x = x + step;
	}
	return (-1.0);
}

static double	wall_y_detect(t_print *w, t_player *p, t_map *m)
{
	double	x;
	double	y;
	double	step;
	double	tmp;
	double	dist;
	int		colision = FALSE;
	double	ymax;


	dist = -1.0;
	y = (p->wl.diry > 0) ? ((int)(p->wl.ymin / m->ycase)) : ((int)(p->wl.ymax / m->ycase));
	y = y * m->ycase + ((p->wl.diry > 0) ? m->ycase : 0);
	step = m->ycase * p->wl.diry;
	ymax = (p->wl.diry > 0) ? p->wl.ymax : p->wl.ymin;
	SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 100);
	while (y != ymax && (y >= 0 && y <= WINY + 1))
	{
		x = (y - p->wl.b) / p->wl.a;
		if ((colision = ft_colision_detection(m, x, y + p->wl.diry)) == FALSE)
			SDL_RenderDrawPoint(w->ren, x, y);
		else
		{
			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50);
			if ((tmp = dist_calc(p->pos.x, p->pos.y, x, y)) > 0)
				SDL_RenderDrawPoint(w->ren, x, y);
			if (dist < 0 || dist > tmp)
				dist = tmp;
			return (dist);
		}
		printf("COLISION: %d, y = %.1f\n", colision, y);
		y = y + step;
	}
	printf("return dist <<<<<<<<<<<<<<<<< 0: %.1f\n", y);
	return (dist);
}

/* static double		init_y_wall(t_wall *wl, t_map *m) */
/* { */
/* 	double		y; */

/* 	if (wl->diry > 0) */
/* 	{ */
/* 		y = ((int)(wl->ymin / m->ycase)); */
/* 		y = y * m->ycase + m->ycase; */
/* 	} */
/* 	else */
/* 	{ */
/* 		y = ((int)(wl->ymax / m->ycase)); */
/* 		y = y * m->ycase; */
/* 	} */
/* 	return (y); */
/* } */

/* static double	wall_y_detect(t_print *w, t_player *p, t_map *m) */
/* { */
/* 	double	x; */
/* 	double	y; */
/* 	double	step; */
/* 	double	tmp; */
/* 	double	dist; */
/* 	int		colision = FALSE; */

/* 	y = init_y_wall(&(p->wl), m); */
/* 	step = m->ycase * p->wl.diry; */
/* //	ymax = (p->wl.diry > 0) ? p->wl.ymax : p->wl.ymin; */
/* 	if (y < 0) */
/* 		y = 0; */
/* 	/\* while (y != ymax && (y <= WINY + 1 && y >= 0)) *\/ */
/* 	dist = -1.0; */
/* 	SDL_SetRenderDrawColor(w->ren, 0, 0, 255, 100); */
/* 	while (y >= 0 && y <= WINY) */
/* 	{ */
/* 		x = (y - p->wl.b) / p->wl.a; */
/* 		if ((colision = ft_colision_detection(m, x, y)) == FALSE) */
/* 			SDL_RenderDrawPoint(w->ren, x, y); */
/* 		else */
/* 		{ */
/* 			SDL_SetRenderDrawColor(w->ren, 255, 0, 255, 50); */
/* 			if ((tmp = dist_calc(p->pos.x, p->pos.y, x, y) > 0)) */
/* 				SDL_RenderDrawPoint(w->ren, x, y); */
/* 			if (dist < 0 || dist > tmp) */
/* 				dist = tmp; */
/* 		} */
/* 		y = y + step; */
/* 	} */
/* 	return (dist); */
/* } */

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

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha, SDL_Texture *txt)
{
	double	step;
	double	angle;
	double	max;
	int		window_x;
	double	dx;
	double	dy;

	(void)txt;

	m->xcase = (double)WINX / m->xmax;
	m->ycase = (double)WINY / m->ymax;


	window_x = 0;
	step = 60.0 / (double)WINX;
	angle = (double)alpha - 30;
	max = angle + 60;
	while (angle < max && window_x < WINX)
	{
//		printf("%d\n", window_x);
		init_coef(p->pos, &(p->wl), angle);
		dx = wall_x_detect(w, p, m);
		dy = wall_y_detect(w, p, m);
		if (dx < 0)
			dx = dy;
		if (dy > 0 && dx > 0)
			ft_draw_wall(w, recalc_ray_distance(((dx < dy) ? dx : dy), window_x), (double)window_x);
		else if (dy > 0 && dx < 0)
			ft_draw_wall(w, recalc_ray_distance(dy, window_x), (double)window_x);
		else
			ft_draw_wall(w, recalc_ray_distance(dx, window_x), (double)window_x);
		angle += step;
		window_x++;
	}
}
