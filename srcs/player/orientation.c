/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:51:54 by naali             #+#    #+#             */
/*   Updated: 2019/03/29 14:53:56 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_get_wall_orientation(double angle, int orientation)
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

void		ft_load_texture_ft_orientation(t_print *w, t_my_raycast *s_raycast)
{
	if (s_raycast->orientation == EAST_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_x_east, \
						&(s_raycast->srcrect), \
						&(s_raycast->dstrect));
	else if (s_raycast->orientation == WEST_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_x_west, \
						&(s_raycast->srcrect), \
						&(s_raycast->dstrect));
	else if (s_raycast->orientation == SOUTH_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_y_south, \
						&(s_raycast->srcrect), \
						&(s_raycast->dstrect));
	else if (s_raycast->orientation == NORTH_WALL)
		SDL_RenderCopy(w->renderer_3d, w->txt_y_north, \
						&(s_raycast->srcrect), \
						&(s_raycast->dstrect));
	else
		SDL_RenderCopy(w->renderer_3d, w->txt, \
						&(s_raycast->srcrect), \
						&(s_raycast->dstrect));
}
