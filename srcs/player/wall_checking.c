/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:27 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 12:57:43 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static double	check_colision(t_print *s_win, t_player *player, t_my_raycast *rc)
{
	double		dist;

	dist = -1;
	if ((rc->colision = ft_colision_detection(&(s_win->m), rc, player->wl.dirx, player->wl.diry)) == FALSE)
		SDL_RenderDrawPoint(s_win->renderer[MAP_2D], rc->x, rc->y);
	else
	{
		SDL_SetRenderDrawColor(s_win->renderer[MAP_2D], 255, 0, 255, 50);
		if ((dist = dist_calc(player->pos.x, player->pos.y, rc->x, rc->y)) > 0)
			SDL_RenderDrawPoint(s_win->renderer[MAP_2D], rc->x, rc->y);
	}
	return (dist);
}

static void		init_wall_x(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->x = (int)(player->pos.x / map->xcase);
	rc->x = rc->x * map->xcase + ((player->wl.dirx == 1) ? map->xcase : 0.0);
	rc->step_cte_x = map->xcase * player->wl.dirx;
}

double			wall_x_detect(t_print *s_win, t_player *player, t_map *map, t_my_raycast *rc)
{
	double	dist;

	dist = 0;
	init_wall_x(player, map, rc);
	rc->colision = FALSE;
	SDL_SetRenderDrawColor(s_win->renderer[MAP_2D], 0, 255, 0, 100);
	while (rc->colision == FALSE)
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
		if ((dist = check_colision(s_win, player, rc)) >= 0)
			return (dist);
		rc->x = rc->x + rc->step_cte_x;
	}
	return (dist);
}

static void		init_wall_y(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->y = (player->wl.diry > 0) ? ((int)(player->wl.ymin / map->ycase)) : ((int)(player->wl.ymax / map->ycase));
	rc->y = rc->y * map->ycase + ((player->wl.diry > 0) ? map->ycase : 0);
	rc->step_cte_y = map->ycase * player->wl.diry;
}

double			wall_y_detect(t_print *s_win, t_player *player, t_map *map, t_my_raycast *rc)
{
	double	tmp;
	double	dist;

	dist = -1.0;
	rc->colision = FALSE;
	init_wall_y(player, map, rc);
	SDL_SetRenderDrawColor(s_win->renderer[MAP_2D], 0, 255, 0, 100);
	while (rc->colision == FALSE)
	{
		if (rc->angle == 90 || rc->angle == 270)
			printf("HELLO\n");
		if (rc->angle != 90 && rc->angle != 270)
			rc->x = (rc->y - player->wl.b) / player->wl.a;
		else
			rc->x = (rc->y /* - player->wl.b*/);
		if ((tmp = check_colision(s_win, player, rc)) >= 0)
		{
			if (dist < 0 || (tmp >= 0 && dist > tmp))
				dist = tmp;
			return (dist);
		}
		rc->y = rc->y + rc->step_cte_y;
	}
	return (dist);
}
