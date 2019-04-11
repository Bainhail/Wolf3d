/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:27 by naali             #+#    #+#             */
/*   Updated: 2019/04/11 15:22:10 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

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
	float			precision;
	precision = 0.00001;
	init_wall_x(player, map, rc);
	while (rc->colision == FALSE)
	{
		if ((rc->angle < (90.0 + precision) && (rc->angle > (90.0 - precision))) ||
				(rc->angle < (270.0 + precision) && (rc->angle > (270.0 - precision))))
		{
			rc->y = 9999999999;
			rc->x = 9999999999;
		}
		else if ((rc->angle < (0.0 + precision) && (rc->angle > (0.0 - precision))) ||
				(rc->angle < (180.0 + precision) && (rc->angle > (180.0 - precision))))
			rc->y = player->pos.y;
		else
			rc->y = player->wl.a * rc->x + player->wl.b;
		//		if (rc->y > player->wl.ymax)  //comprend pas
		//			player->wl.ymax = rc->y;  //comprend pas
		//		if (rc->y < player->wl.ymin)  //comprend pas
		//			player->wl.ymin = rc->y;  //comprend pas
		rc->colision = ft_colision_detection(&(s_win->m), rc, player->wl.dirx, player->wl.diry);
		if (rc->colision == TRUE)
		{
			rc->dist_col_x = dist_calc(player->pos.x, player->pos.y, rc->x, rc->y);
			rc->wall_X_colision.x = rc->x;
			rc->wall_X_colision.y = rc->y;
			return (rc->dist_col_x);
		}
		if ((int)(rc->angle * 1000) == (90 * 1000) || (int)(rc->angle * 1000) == (270 * 1000))
			rc->x = rc->x;
		else if ((int)(rc->angle * 1000) == 0 || (int)(rc->angle * 1000) == (180 * 1000))
			rc->x = rc->x + (map->xcase * player->wl.dirx);
		else
			rc->x = rc->x + rc->step_cte_x;
	}
	return (rc->dist_col_x);
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
	float			precision;
	precision = 0.00001;
	init_wall_y(player, map, rc);
	while (rc->colision == FALSE)
	{
		if ((rc->angle < (0.0 + precision) && (rc->angle > (0.0 - precision))) ||
				(rc->angle < (180.0 + precision) && (rc->angle > (180.0 - precision))))
		{
			rc->x = 99999999;
			rc->y = 99999999;
		}
		else if ((rc->angle < (90.0 + precision) && (rc->angle > (90.0 - precision))) ||
				(rc->angle < (270.0 + precision) && (rc->angle > (270.0 - precision))))
		{
			rc->x = player->pos.x;
		}
		else
			rc->x = (rc->y - player->wl.b) / player->wl.a;
		if ((rc->colision = ft_colision_detection(&(s_win->m), rc, player->wl.dirx, player->wl.diry)) == TRUE)
		{
			rc->dist_col_y = dist_calc(player->pos.x, player->pos.y, rc->x, rc->y);
			rc->wall_Y_colision.x = rc->x;
			rc->wall_Y_colision.y = rc->y;
			return (rc->dist_col_y);
		}
		if ((int)(rc->angle * 1000) == 0 || (int)(rc->angle * 1000) == (180 * 1000))
			rc->y = rc->y;
		else if ((int)(rc->angle * 1000) == (90 * 1000) || (int)(rc->angle * 1000) == (270 * 1000))
			rc->y = rc->y + (map->ycase * player->wl.diry);
		else
			rc->y = rc->y + rc->step_cte_y;
	}
	return (rc->dist_col_y);
}
