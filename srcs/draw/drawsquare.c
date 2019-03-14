/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsquare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:39:03 by naali             #+#    #+#             */
/*   Updated: 2019/03/14 18:22:26 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			draw_square(SDL_Renderer *r, t_map *m, int x, int y)
{
	int		ytmp;
	int		xct;
	int		yct;

	ytmp = y;
	xct = (x + m->xcase > WINX) ? WINX : (x + m->xcase);
	yct = y + m->ycase;
	if (m->tab[(int)(y / m->ycase)][(int)(x / m->xcase)].z > 0)
		SDL_SetRenderDrawColor(r, 0, 0, 0, 100);
	else
		SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
	while (x <= xct && x < WINX)
	{
		y = ytmp;
		while (y <= yct && y <= WINY)
		{
			SDL_RenderDrawPoint(r, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
