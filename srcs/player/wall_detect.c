/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:31:21 by naali             #+#    #+#             */
/*   Updated: 2019/03/27 17:04:49 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static double	ft_calcul_distance(double xa, double ya, double xb, double yb)
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
	if (win_step <= WINX / 2)
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
		printf("AUCUN ==> probleme\n");
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

	distance_ray = ft_calcul_distance(p->pos.x, p->pos.y, s_raycast->x, s_raycast->y);
	distance_ray = recalc_ray_distance(distance_ray, s_raycast->window_x);
	s_raycast->orientation = ft_get_colision_type(s_raycast->x, s_raycast->y, s_raycast);
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

static int		ft_colision_detection(t_map *m, t_my_raycast *s_raycast)
{
	if (s_raycast->x < 0 || s_raycast->x > (WINX - 1))
		return (TRUE);
	else if (s_raycast->y < 0 || s_raycast->y > (WINY - 1))
		return (TRUE);
	else if (m->tab[(int)((int)(s_raycast->y) / m->ycase)][(int)((int)(s_raycast->x) / m->xcase)].z >= 1)
		return (TRUE);
	return (FALSE);
}

static void		ft_get_secteur_rayon(int x, int y, t_map *m, t_my_raycast *s_raycast)
{
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

static void		wall_detect(t_print *w, t_player *p, t_map *m, t_my_raycast *s_raycast)
{
	int					colision;
	double				ray_distance;

	ft_init_secteur_rayon(p, m, s_raycast);
	colision = FALSE;
	ray_distance = 0;
	while (colision == FALSE)
	{
		s_raycast->x = (cos(conv_deg_to_rad(s_raycast->angle - 90)) * ray_distance) + p->pos.x;
		s_raycast->y = (sin(conv_deg_to_rad(s_raycast->angle - 90)) * ray_distance) + p->pos.y;
		ft_get_secteur_rayon(s_raycast->x, s_raycast->y, m, s_raycast);
		if ((colision = ft_colision_detection(m, s_raycast)) == FALSE)
			SDL_RenderDrawPoint(w->ren, s_raycast->x, s_raycast->y);
		else
			ft_draw_wall(w, m, p, s_raycast);
		ray_distance++;
	}
}

void			ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	double			step;
	double			max;
	t_my_raycast	s_raycast;

	s_raycast.window_x = 0;
	step = 60.0 / (double)WINX;
	s_raycast.angle = (double)alpha - 30;
	max = s_raycast.angle + 60;
	while (s_raycast.angle < max && s_raycast.window_x < WINX)
	{
		wall_detect(w, p, m, &s_raycast);
		s_raycast.angle += step;
		s_raycast.window_x++;
	}
}
