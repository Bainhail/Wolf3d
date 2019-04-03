/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:51:54 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 18:48:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int			ft_get_wall_orientation(double angle, int orientation)
{
	if (orientation == X_COLISION && cos(conv_deg_to_rad(angle)) > 0)
			orientation = EAST_WALL;
	else if (orientation == X_COLISION )
			orientation = WEST_WALL;
	else if (orientation == Y_COLISION && sin(conv_deg_to_rad(angle)) > 0)
			orientation = SOUTH_WALL;
	else if (orientation == Y_COLISION)
			orientation = NORTH_WALL;
	return (orientation);
}

void		ft_load_texture_ft_orientation(t_print *w, t_my_raycast *s_raycast)
{
	if (s_raycast->orientation == EAST_WALL)
		SDL_RenderCopy(w->renderer[MAP_3D], w->texture[EAST_WALL], &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == WEST_WALL)
		SDL_RenderCopy(w->renderer[MAP_3D], w->texture[WEST_WALL], &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == SOUTH_WALL)
		SDL_RenderCopy(w->renderer[MAP_3D], w->texture[SOUTH_WALL], &(s_raycast->srcrect), &(s_raycast->dstrect));
	else if (s_raycast->orientation == NORTH_WALL)
		SDL_RenderCopy(w->renderer[MAP_3D], w->texture[NORTH_WALL], &(s_raycast->srcrect), &(s_raycast->dstrect));
	else
	{
		SDL_RenderCopy(w->renderer[MAP_3D], w->texture[NONE], &(s_raycast->srcrect), &(s_raycast->dstrect));
		printf("XXXXXXXXXXXXXXXXXxx PROBLEME\n");
	}
}
