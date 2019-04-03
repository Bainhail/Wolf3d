/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:27 by naali             #+#    #+#             */
/*   Updated: 2019/04/03 14:53:47 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
static double	check_colision(t_print *s_win, t_player *player, t_my_raycast *rc);


static void		init_wall_x(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->dist_col_x = 0;
	rc->colision = FALSE;
	rc->x = (int)(player->pos.x / map->xcase);
	rc->x = rc->x * map->xcase + ((player->wl.dirx == 1) ? map->xcase : 0.0);
	rc->step_cte_x = map->xcase * player->wl.dirx;
}

double			wall_x_detect(t_print *s_win, t_player *player, t_map *map, t_my_raycast *rc)
{
	init_wall_x(player, map, rc);
	SDL_SetRenderDrawColor(s_win->renderer[MAP_2D], 0, 255, 0, 100);
	while (rc->colision == FALSE)
	{
		if (rc->angle != 90 && rc->angle != 270)
			rc->y = player->wl.a * rc->x + player->wl.b;
		else
			rc->y = rc->y + map->ycase;



		if (rc->y > player->wl.ymax)  //comprend pas
			player->wl.ymax = rc->y;  //comprend pas
		if (rc->y < player->wl.ymin)  //comprend pas
			player->wl.ymin = rc->y;  //comprend pas


		rc->colision = ft_colision_detection(&(s_win->m), rc, player->wl.dirx, player->wl.diry);
		if(rc->colision == TRUE)
		{
			rc->dist_col_x = dist_calc(player->pos.x, player->pos.y, rc->x, rc->y);
			return (rc->dist_col_x);
		}
		rc->x = rc->x + rc->step_cte_x;
	}
	return (rc->dist_col_x);
}


static double	check_colision(t_print *s_win, t_player *player, t_my_raycast *rc)
{
	double		dist;

	dist = -1;
	if ((rc->colision = ft_colision_detection(&(s_win->m), rc, player->wl.dirx, player->wl.diry)) == FALSE)
		SDL_RenderDrawPoint(s_win->renderer[MAP_2D], rc->x, rc->y);
	else
	{
		if ((dist = dist_calc(player->pos.x, player->pos.y, rc->x, rc->y)) > 0)
			SDL_RenderDrawPoint(s_win->renderer[MAP_2D], rc->x, rc->y);
	}
	return (dist);
}

static void		init_wall_y(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->colision = FALSE;
	rc->dist_col_y = 0;
	rc->y = (player->wl.diry > 0) ? ((int)(player->wl.ymin / map->ycase)) : ((int)(player->wl.ymax / map->ycase));
	rc->y = rc->y * map->ycase + ((player->wl.diry > 0) ? map->ycase : 0);
	rc->step_cte_y = map->ycase * player->wl.diry;
}





double			wall_y_detect(t_print *s_win, t_player *player, t_map *map, t_my_raycast *rc)
{
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
		if ((rc->dist_col_y = check_colision(s_win, player, rc)) >= 0)
		{
			return (rc->dist_col_y);
		}
		rc->y = rc->y + rc->step_cte_y;
	}
	return (rc->dist_col_y);
}
