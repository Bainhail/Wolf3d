/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:27 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 12:01:20 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static double	check_colision(t_print *w, t_player *player, t_my_raycast *r, int *c)
{
	double		dist;

	dist = -1;
	if ((*c = ft_colision_detection(&(w->m), r, player->wl.dirx, player->wl.diry)) == FALSE)
		SDL_RenderDrawPoint(w->renderer[MAP_2D], r->x, r->y);
	else
	{
		SDL_SetRenderDrawColor(w->renderer[MAP_2D], 255, 0, 255, 50);
		if ((dist = dist_calc(player->pos.x, player->pos.y, r->x, r->y)) > 0)
			SDL_RenderDrawPoint(w->renderer[MAP_2D], r->x, r->y);
	}
	return (dist);
}

static void		init_wall_x(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->x = (int)(player->pos.x / map->xcase);
	rc->x = rc->x * map->xcase + ((player->wl.dirx == 1) ? map->xcase : 0.0);
	rc->step_cte_x = map->xcase * player->wl.dirx;
}

double			wall_x_detect(t_print *w, t_player *player, t_map *map, \
												t_my_raycast *rc)
{
	double	dist;
	int		colision;

	dist = 0;
	init_wall_x(player, map, rc);
	colision = FALSE;
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 100);
	while (colision == FALSE)
	{
		if (rc->angle != 90 && rc->angle != 270)
		{
			rc->y = player->wl.a * rc->x + player->wl.b;
		}
		else
		{
			printf("angle 90 x =%.1f\n", player->wl.b);
			rc->y = rc->x /*+ player->wl.b*/;
		}
		if (rc->y > player->wl.ymax)
			player->wl.ymax = rc->y;
		if (rc->y < player->wl.ymin)
			player->wl.ymin = rc->y;
		if ((dist = check_colision(w, player, rc, &colision)) >= 0)
			return (dist);
		rc->x = rc->x + rc->step_cte_x;
	}
	return (dist);
}

static void		init_wall_y(t_player *player, t_map *map, t_my_raycast *rc, double *s)
{
	rc->y = (player->wl.diry > 0) ? ((int)(player->wl.ymin / map->ycase)) : ((int)(player->wl.ymax / map->ycase));
	rc->y = rc->y * map->ycase + ((player->wl.diry > 0) ? map->ycase : 0);
	*s = map->ycase * player->wl.diry;
}

double			wall_y_detect(t_print *w, t_player *player, t_map *map, t_my_raycast *rc)
{
	double	step;
	double	tmp;
	double	dist;
	int		colision;

	dist = -1.0;
	colision = FALSE;
	init_wall_y(player, map, rc, &step);
	SDL_SetRenderDrawColor(w->renderer[MAP_2D], 0, 255, 0, 100);
	while (colision == FALSE)
	{
		if (rc->angle == 90 || rc->angle == 270)
			printf("HELLO\n");
		if (rc->angle != 90 && rc->angle != 270)
			rc->x = (rc->y - player->wl.b) / player->wl.a;
		else
			rc->x = (rc->y /* - player->wl.b*/);
		if ((tmp = check_colision(w, player, rc, &colision)) >= 0)
		{
			if (dist < 0 || (tmp >= 0 && dist > tmp))
				dist = tmp;
			return (dist);
		}
		rc->y = rc->y + step;
	}
	return (dist);
}
