/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segmnt_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:09:53 by naali             #+#    #+#             */
/*   Updated: 2019/03/21 17:41:46 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		init_sgmt(t_sgmt *l, t_vertex start, t_vertex end)
{
	l->dx = end.x - start.x;
	l->dy = fabs(end.y - start.y);
	l->error = l->dx / 2.0f;
	l->ystep = (start.y < end.y) ? 1 : -1;
	l->x = (int)(start.x);
	l->y = (int)(start.y);
	l->maxX = (int)(end.x);
}

static void		change_vertex(int swp, t_vertex *start, t_vertex *end)
{
	double	tmp;

	if (swp >= 0)
	{
		refresh_vtex(start, start->y, start->x, start->z);
		refresh_vtex(end, end->y, end->x, end->z);
	}
	if (start->x > end->x)
	{
		tmp = start->x;
		start->x = end->x;
		end->x = tmp;
		tmp = start->y;
		start->y = end->y;
		end->y = tmp;
	}
}

static void		print_line1(t_print *w, int swp, t_vertex start, t_vertex end)
{
	t_sgmt	l;

	init_sgmt(&l, start, end);
//	SDL_SetRenderDrawColor(w->ren_flg, 255, 0, 0, 100);
	while (++l.x < (l.maxX - 1))
	{
		if (swp >= 0)
			SDL_RenderDrawPoint(w->ren_flg, l.y, l.x);
		else
			SDL_RenderDrawPoint(w->ren_flg, l.x, l.y);
		l.error = l.error - l.dy;
		if (l.error < 0)
		{
			l.y += l.ystep;
			l.error = l.error + l.dx;
		}
	}
}

void			print_line(t_print *w, SDL_Renderer *r, t_vertex start, t_vertex end)
{
	int		swp;

	w->ren_flg = r;
	swp = (int)(fabs(end.y - start.y) - fabs(end.x - start.x));
	change_vertex(swp, &start, &end);
	print_line1(w, swp, start, end);
}
