/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsquare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:39:03 by naali             #+#    #+#             */
/*   Updated: 2019/05/15 17:20:20 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			draw_square(SDL_Renderer *r, t_map *m, int x, int y)
{
	int		ytmp;
	int		xct;
	int		yct;

	ytmp = y * m->ycase;
	if (m->tab[y][x].z >= 1)
		SDL_SetRenderDrawColor(r, 0, 0, 0, 100);
	else
		SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
	x *= m->xcase;
	y *= m->ycase;
	xct = x + (int)(m->xcase - 1);
	yct = y + (int)(m->ycase - 1);
	while (x < xct && x < WINX)
	{
		y = ytmp;
		while (y < yct && y <= WINY)
		{
			SDL_RenderDrawPoint(r, x, y);
			y++;
		}
		x++;
	}
}
