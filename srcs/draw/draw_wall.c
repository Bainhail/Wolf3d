/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:55:35 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 11:16:59 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int			ft_calcule_delta_texture(t_map *m, t_my_raycast *s_raycast)
{
	int		le_delta;

	if (s_raycast->orientation == EAST_WALL \
		|| s_raycast->orientation == WEST_WALL)
	{
		if (s_raycast->orientation == EAST_WALL)
			le_delta = (int)s_raycast->y % (int)(m->ycase > 0 ? m->ycase : 1);
		else
			le_delta = (int)m->ycase - ((int)s_raycast->y % (int)(m->ycase > 0 ? m->ycase : 1));
		s_raycast->dstrect.w = m->ycase;
	}
	else
	{
		if (s_raycast->orientation == NORTH_WALL)
			le_delta = (int)(s_raycast->x + 1.0) % (int)(m->xcase > 1 ? m->xcase : 1);
		else
			le_delta = (int)m->xcase - ((int)(s_raycast->x + 1.0) %
			(int)(m->xcase + 1.0 > 1 ? m->xcase + 1.0 : 1));
		s_raycast->dstrect.w = m->xcase;
	}
	return (le_delta);
}

void		ft_init_texture_wall_position(t_map *m, t_my_raycast *s_raycast)
{
	int le_delta;

	le_delta = ft_calcule_delta_texture(m, s_raycast);
	s_raycast->srcrect.x = le_delta / 2;
	s_raycast->srcrect.w = 1;
	s_raycast->srcrect.y = 0;
	s_raycast->srcrect.h = 54;
	s_raycast->dstrect.x = s_raycast->window_x;
	s_raycast->dstrect.w = 1;
	s_raycast->dstrect.h = (int)(s_raycast->hmp * 2);
	s_raycast->dstrect.y = (int)((double)WINY / 2.0) - (s_raycast->hmp);
}

double		ft_calc_hmp(double distance_ray)
{
	double	hmp;

	hmp = (((double)EYE * (double)WALL) / distance_ray) / 2.0;
	if (hmp > 600.0)
		return (600.0);
	return (hmp);
}

void		ft_draw_wall(t_print *w, t_map *m, t_my_raycast *rc)
{
	double		distance_ray;
	float		precision;

	precision = 0.1;
	if ((rc->dist_col_x + precision) > rc->dist_col_y &&
			(rc->dist_col_x - precision) < rc->dist_col_y)
		;
	else
		rc->orientation = ft_get_wall_orientation(rc);
	if (rc->dist_col_x < rc->dist_col_y)
		distance_ray = (rc->dist_col_x / m->ycase) * m->ycase;
	else
		distance_ray = (rc->dist_col_y / m->ycase) * m->xcase;
	distance_ray = recalc_ray_distance(distance_ray, rc->window_x);
	rc->hmp = ft_calc_hmp(distance_ray);
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 50, 50, 200, 75);
	SDL_SetRenderDrawColor(w->renderer[MAP_3D], 200, 200, 200, 75);
	ft_init_texture_wall_position(m, rc);
	ft_load_texture_ft_orientation(w, rc);
}
