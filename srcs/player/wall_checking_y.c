/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checking_y.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:07:18 by naali             #+#    #+#             */
/*   Updated: 2019/05/09 15:26:03 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void		init_wall_y(t_player *player, t_map *map, t_my_raycast *rc)
{
	rc->colision = FALSE;
	rc->dist_col_y = 0;
	if (player->wl.diry > 0)
		rc->y = ((int)(player->wl.ymin / map->ycase));
	else
		rc->y = ((int)(player->wl.ymax / map->ycase));
	rc->y = rc->y * map->ycase + ((player->wl.diry > 0) ? map->ycase : 0);
	rc->step_cte_y = map->ycase * player->wl.diry;
}

void			ft_wall_y_detect_calucl_x(t_player *player, t_my_raycast *rc)
{
	float			precision;

	precision = 0.00001;
	if ((rc->angle < (0.0 + precision) \
			&& (rc->angle > (0.0 - precision))) \
			|| (rc->angle < (180.0 + precision) \
			&& (rc->angle > (180.0 - precision))))
	{
		rc->x = 99999999;
		rc->y = 99999999;
	}
	else if ((rc->angle < (90.0 + precision) \
				&& (rc->angle > (90.0 - precision))) \
				|| (rc->angle < (270.0 + precision) \
				&& (rc->angle > (270.0 - precision))))
		rc->x = player->pos.x;
	else
		rc->x = (rc->y - player->wl.b) / player->wl.a;
}

void			ft_wall_y_detect_y_calcul(t_player *player, t_map *map, \
											t_my_raycast *rc)
{
	float			precision;

	precision = 0.00001;
	if ((rc->angle < (0.0 + precision) \
			&& (rc->angle > (0.0 - precision))) \
			|| (rc->angle < (180.0 + precision) \
			&& (rc->angle > (180.0 - precision))))
		rc->y = rc->y;
	else if ((rc->angle < (90.0 + precision) \
				&& (rc->angle > (90.0 - precision))) \
				|| (rc->angle < (270.0 + precision) \
				&& (rc->angle > (270.0 - precision))))
		rc->y = rc->y + (map->ycase * player->wl.diry);
	else
		rc->y = rc->y + rc->step_cte_y;
}

double			wall_y_detect(t_print *s_win, t_player *player, \
								t_map *map, t_my_raycast *rc)
{
	init_wall_y(player, map, rc);
	while (rc->colision == FALSE)
	{
		ft_wall_y_detect_calucl_x(player, rc);
		if ((rc->colision = ft_colision_detection(&(s_win->m), rc,
			player->wl.dirx, player->wl.diry)) == TRUE)
		{
			rc->dist_col_y = dist_calc(player->pos.x, \
										player->pos.y, rc->x, rc->y);
			rc->wall_y_colision.x = rc->x;
			rc->wall_y_colision.y = rc->y;
			return (rc->dist_col_y);
		}
		ft_wall_y_detect_y_calcul(player, map, rc);
	}
	return (rc->dist_col_y);
}
