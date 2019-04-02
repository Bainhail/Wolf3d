/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect_opti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:30:52 by naali             #+#    #+#             */
/*   Updated: 2019/04/02 17:10:28 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_coef(t_vertex *pos_joueur, t_wall *wl, double alpha)
{
	wl->x = (cos(conv_deg_to_rad(alpha)) * 1.0) + pos_joueur->x;
	wl->y = (sin(conv_deg_to_rad(alpha)) * 1.0) + pos_joueur->y;


	if (alpha != 90 && alpha != 270)
	{
		wl->a = (wl->y - pos_joueur->y) / (wl->x - pos_joueur->x);
		wl->b = pos_joueur->y - (pos_joueur->x * wl->a);
	}
	else
	{
		wl->a = (wl->y - pos_joueur->y);
		wl->b = pos_joueur->y - pos_joueur->x;
		printf("XY =%f =%f\n", wl->x, wl->y);
	}


	wl->b = pos_joueur->y - (pos_joueur->x * wl->a);
	wl->dirx = (wl->x < pos_joueur->x) ? -1 : 1;
	wl->diry = (wl->y < pos_joueur->y) ? -1 : 1;
	wl->ymin = wl->y;
	wl->ymax = wl->y;
}

static void	print_view(t_print *w, t_player *p, t_my_raycast *r, t_vertex *wall)
{
	if (r->dist_col_x > r->dist_col_y)
		refresh_vtex(wall, r->x, r->y, 0.0);
	else
	{
		r->x = wall->x;
		r->y = wall->y;
	}


	if ((int)r->dist_col_x == (int)r->dist_col_y)
		SDL_SetRenderDrawColor(w->ren, 255, 0, 0, 50);  //rouge
	else if ((int)r->dist_col_x > (int)r->dist_col_y)
		SDL_SetRenderDrawColor(w->ren, 0, 0, 255, 50);  //bleu
	else
		SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50); //vert



	//SDL_SetRenderDrawColor(w->ren, 0, 255, 0, 50);
	print_line(w, w->ren, p->pos, *wall);
}

void		ft_raycast(t_print *w, t_player *p, t_map *m, int alpha)
{
	double			step;
	double			max;
	t_my_raycast	rc;
	t_vertex		wall;

	rc.window_x = 0;
	step = 60.0 / (double)WINX;
	rc.angle = (double)alpha - 30;
	max = rc.angle + 60;
	ft_init_secteur_rayon(p, m, &rc);
	printf("\n\n");
	while (rc.angle < max && rc.window_x < WINX)
	{
		init_coef(&(p->pos), &(p->wl), rc.angle);
		rc.dist_col_x = wall_x_detect(w, p, m, &rc);
		wall.x = rc.x;
		wall.y = rc.y;
		wall.z = 0.0;
		rc.dist_col_y = wall_y_detect(w, p, m, &rc);
		print_view(w, p, &rc, &wall);
		ft_draw_wall(w, m, &rc);
		ft_get_secteur_rayon(rc.x, rc.y, m, &rc);
		rc.angle += step;
		rc.window_x++;
	}
}
