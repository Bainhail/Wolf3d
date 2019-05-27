/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsquare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:39:03 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 10:30:13 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			draw_square(SDL_Renderer *r, t_player *p/* t_map *m */, int x, int y)
{
	int		ytmp;
	int		xct;
	int		yct;
	int		xcase;

	xcase = (WIN2D / 10);
	ytmp = (y * xcase) + (((int)(p->pos.y) % xcase - (xcase / 2)) * -1);
	SDL_SetRenderDrawColor(r, 0, 0, 0, 100);
	x = (x * xcase) + (((int)(p->pos.x) % xcase - (xcase / 2)) * -1);
	y = ytmp;
	xct = x + xcase - 1;
	yct = y + xcase - 1;
	while (x < xct && x < WIN2D)
	{
		y = ytmp;
		while (y < yct && y <= WIN2D)
		{
			SDL_RenderDrawPoint(r, x, y);
			y++;
		}
		x++;
	}
}
