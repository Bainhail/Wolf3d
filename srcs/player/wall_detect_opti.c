/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detect_opti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 15:30:52 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 11:33:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

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
	wl->dirx = (wl->x < pos_joueur->x) ? -1 : 1;
	wl->diry = (wl->y < pos_joueur->y) ? -1 : 1;
	wl->ymin = wl->y; //je c pas ce ke c
	wl->ymax = wl->y; //je c pas ce ke c
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
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 0, 0, 50);  //rouge
	else if ((int)r->dist_col_x > (int)r->dist_col_y)
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 0, 255, 50);  //bleu
	else
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 50); //vert
	//SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 50);
	print_line(w, w->renderer[MAP_2D], p->pos, *wall);
}

void		ft_raycast(t_print *s_win, t_player *s_player, t_map *s_map, int alpha)
{
	double			step;
	double			max;
	t_my_raycast	s_raycast;
	t_vertex		wall;

	s_raycast.window_x = 0;
	step = s_player->fov / (double)WINX;
	s_raycast.angle = (double)alpha - 30;
	max = s_raycast.angle + 60;
	ft_init_secteur_rayon(s_player, s_map, &s_raycast);
	printf("\n\n");
	while (s_raycast.angle < max && s_raycast.window_x < WINX)
	{
		init_coef(&(s_player->pos), &(s_player->wl), s_raycast.angle);
		s_raycast.dist_col_x = wall_x_detect(s_win, s_player, s_map, &s_raycast);
		wall.x = s_raycast.x;
		wall.y = s_raycast.y;
		wall.z = 0.0;
		s_raycast.dist_col_y = wall_y_detect(s_win, s_player, s_map, &s_raycast);
		print_view(s_win, s_player, &s_raycast, &wall);
		ft_draw_wall(s_win, s_map, &s_raycast);
		ft_get_secteur_rayon(s_raycast.x, s_raycast.y, s_map, &s_raycast);
		s_raycast.angle += step;
		s_raycast.window_x++;
	}
}
