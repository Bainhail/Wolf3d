/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:04:19 by naali             #+#    #+#             */
/*   Updated: 2019/05/27 06:31:56 by naali            ###   ########.fr       */
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

void			wall_x_detect_calcul_y(t_player *player, t_my_raycast *rc)
{
	float			precision;

	precision = 0.00001;
	if ((rc->angle < (90.0 + precision) && (rc->angle > (90.0 - precision))) \
		|| (rc->angle < (270.0 + precision) \
		&& (rc->angle > (270.0 - precision))))
	{
		rc->y = 9999999999;
		rc->x = 9999999999;
	}
	else if ((rc->angle < (0.0 + precision) \
				&& (rc->angle > (0.0 - precision))) \
				|| (rc->angle < (180.0 + precision) \
				&& (rc->angle > (180.0 - precision))))
		rc->y = player->pos.y;
	else
		rc->y = player->wl.a * rc->x + player->wl.b;
}

double			wall_x_detect(t_print *s_win, t_player *player, \
								t_map *map, t_my_raycast *rc)
{
	init_wall_x(player, map, rc);
	while (rc->colision == FALSE)
	{
		wall_x_detect_calcul_y(player, rc);
		rc->colision = ft_colision_detection(&(s_win->m), rc, \
											player->wl.dirx, player->wl.diry);
		if (rc->colision == TRUE)
		{
			rc->dist_col_x = dist_calc(player->pos.x, player->pos.y, \
										rc->x, rc->y);
			rc->wall_x_colision.x = rc->x;
			rc->wall_x_colision.y = rc->y;
			return (rc->dist_col_x);
		}
		wall_x_detect_calcul_x(player, map, rc);
	}
	return (rc->dist_col_x);
}

void			wall_x_detect_calcul_x(t_player *player, t_map *map, \
										t_my_raycast *rc)
{
	float			precision;

	(void)map;
	precision = 0.00001;
	if ((rc->angle < (90.0 + precision) && (rc->angle > (90.0 - precision))) \
			|| (rc->angle < (270.0 + precision) \
			&& (rc->angle > (270.0 - precision))))
		rc->x = rc->x;
	else if ((rc->angle < (0.0 + precision) \
				&& (rc->angle > (0.0 - precision))) \
				|| (rc->angle < (180.0 + precision) \
				&& (rc->angle > (180.0 - precision))))
		rc->x = rc->x + (map->xcase * player->wl.dirx);
	else
		rc->x = rc->x + rc->step_cte_x;
}
