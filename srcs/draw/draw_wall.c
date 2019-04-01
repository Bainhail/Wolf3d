/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:55:35 by naali             #+#    #+#             */
/*   Updated: 2019/04/01 14:12:34 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_init_texture_wall_position(t_map *m, t_my_raycast *s_raycast)
{
	int le_delta;

	if (s_raycast->orientation == EAST_WALL || s_raycast->orientation == WEST_WALL)
	{
		if (s_raycast->orientation == EAST_WALL)
			le_delta = (int)s_raycast->y % (int)m->ycase;
		else
			le_delta = (int)m->ycase - ((int)s_raycast->y % (int)m->ycase);
	}
	else
	{
		if (s_raycast->orientation == NORTH_WALL)
		le_delta = (int)(s_raycast->x + 1.0) % (int)m->xcase;
		else
		le_delta =(int)m->xcase - ((int)(s_raycast->x + 1.0) % (int)m->xcase);
	}
	s_raycast->srcrect.x = le_delta;
	s_raycast->srcrect.w = 1;//Peut etre une modification ici aussi
	s_raycast->srcrect.y = 0;
	s_raycast->srcrect.h = 54;
	s_raycast->dstrect.x = s_raycast->window_x;
	s_raycast->dstrect.w = 1;//a modifier pour adapter la largeur
	s_raycast->dstrect.h = (int)(s_raycast->hmp * 2);
	s_raycast->dstrect.y = (int)((double)WINY / 2.0) - (s_raycast->hmp/* / 2.0 */);
}

void			ft_draw_wall(t_print *w, t_map *m, t_my_raycast *rc)
{
	t_vertex	w_up;
	t_vertex	w_bot;
	double		distance_ray;

	distance_ray = (rc->dx >= 0 && rc->dx < rc->dy) ? rc->dx : rc->dy;
	distance_ray = recalc_ray_distance(distance_ray, rc->window_x);
	rc->orientation = (rc->dx >= 0 && rc->dx < rc->dy) \
					  ? X_COLISION : Y_COLISION;
	rc->orientation = ft_get_wall_orientation(rc->angle, rc->orientation);
	rc->hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0;
	w_up = init_vtex(rc->window_x, ((double)WINY / 2.0) - rc->hmp, 0);
	w_bot = init_vtex(rc->window_x, ((double)WINY / 2.0) + rc->hmp, 0);
	SDL_SetRenderDrawColor(w->renderer_3d, 50, 50, 200, 75);
	print_line(w, w->renderer_3d, init_vtex(rc->window_x, 0, 0), w_up);
	SDL_SetRenderDrawColor(w->renderer_3d, 200, 200, 200, 75);
	print_line(w, w->renderer_3d, w_bot, init_vtex(rc->window_x, WINY, 0));
	ft_init_texture_wall_position(m, rc);
	ft_load_texture_ft_orientation(w, rc);
}
